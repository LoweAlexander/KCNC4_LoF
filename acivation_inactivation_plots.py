"""
Voltage-clamp Boltzmann analysis.

Loads one CSV per variant (columns = experiments, rows = voltage steps),
fits Boltzmann curves under two interpretations of the raw values
(G/Gmax directly, or I/Imax converted to G/Gmax), and plots results.

Two interpretations are kept side by side deliberately: without knowing
which quantity was actually recorded, picking one would be an assumption,
not a finding.
"""

from dataclasses import dataclass, field
from functools import partial
from pathlib import Path
import re

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

from scipy.optimize import curve_fit

VOLTAGES = [-80, -50, -30, -10, 10, 30, 40]
COLOR = "#3B6EA5"          # default trace colour for a variant
WT_COLOR = "#444444"       # colour used when overlaying WT for comparison
DATA_ALPHA = 0.25
FIT_ALPHA = 0.25
MEAN_LW = 2.0             # line width for the mean/overlay (WT) curves


# ============================================================
# Boltzmann equations
# ============================================================

def boltzmann(V, V_half, k, direction="activation", plateau=0.0):
    """Normalised Boltzmann curve. direction='activation' rises with V,
    'inactivation' falls with V. `plateau` sets the floor the curve
    settles to at its far end (0 for the standard two-state form) - a
    non-inactivating/non-activating residual fraction, common for
    N-type-inactivating channels like Kv3.4 that don't fully close."""
    sign = -1 if direction == "activation" else 1
    core = 1.0 / (1.0 + np.exp(sign * (V - V_half) / k))
    return plateau + (1.0 - plateau) * core


# ============================================================
# Fit result
# ============================================================

@dataclass
class BoltzmannFit:
    V_half: float
    V_half_err: float
    k: float
    k_err: float
    r_squared: float
    rmse: float
    n_points: int
    V: np.ndarray
    values: np.ndarray
    error: str = None
    plateau: float = 0.0
    plateau_err: float = 0.0

    @property
    def ok(self):
        return self.error is None

    def curve(self, direction="activation", n=300, pad=5):
        V_smooth = np.linspace(self.V.min() - pad, self.V.max() + pad, n)
        return V_smooth, boltzmann(V_smooth, self.V_half, self.k, direction, self.plateau)

    @classmethod
    def failed(cls, V, values, message):
        return cls(np.nan, np.nan, np.nan, np.nan, np.nan, np.nan,
                    len(V), np.asarray(V), np.asarray(values), error=message)


def fit_boltzmann(voltages, values, direction="activation",
                   fit_min=None, fit_max=None, plateau=False):
    """Fit a single Boltzmann curve to one experiment's normalised data.
    `plateau=True` fits a third parameter for a non-zero floor instead
    of assuming the curve reaches 0 (or 1) - see `boltzmann()`."""
    V = np.asarray(voltages, dtype=float)
    y = np.asarray(values, dtype=float)

    keep = np.isfinite(V) & np.isfinite(y)
    if fit_min is not None:
        keep &= V >= fit_min
    if fit_max is not None:
        keep &= V <= fit_max
    V, y = V[keep], y[keep]

    n_params = 3 if plateau else 2
    if len(V) < n_params + 1:
        return BoltzmannFit.failed(V, y, f"fewer than {n_params + 1} valid points")

    half = np.nanmax(y) / 2
    v_half_guess = V[np.argmin(np.abs(y - half))] if np.nanmax(y) > 0 else np.median(V)
    k_guess = 10.0

    if plateau:
        plateau_guess = float(np.clip(np.nanmin(y), 0.0, 0.9))
        p0 = [v_half_guess, k_guess, plateau_guess]
        bounds = ([V.min() - 100, 0.1, 0.0], [V.max() + 100, 200, 0.95])
        fit_func = lambda v, vh, k, c: boltzmann(v, vh, k, direction, c)
    else:
        p0 = [v_half_guess, k_guess]
        bounds = ([V.min() - 100, 0.1], [V.max() + 100, 200])
        fit_func = lambda v, vh, k: boltzmann(v, vh, k, direction)

    try:
        popt, pcov = curve_fit(fit_func, V, y, p0=p0, bounds=bounds, maxfev=10000)
    except RuntimeError as exc:
        return BoltzmannFit.failed(V, y, str(exc))

    err = np.sqrt(np.diag(pcov))
    if plateau:
        V_half, k, c = popt
        V_half_err, k_err, c_err = err
    else:
        V_half, k = popt
        V_half_err, k_err = err
        c, c_err = 0.0, 0.0

    fitted = boltzmann(V, V_half, k, direction, c)
    residuals = y - fitted
    ss_tot = np.sum((y - y.mean()) ** 2)
    r2 = 1 - np.sum(residuals ** 2) / ss_tot if ss_tot > 0 else np.nan

    return BoltzmannFit(
        V_half=V_half, V_half_err=V_half_err, k=k, k_err=k_err,
        r_squared=r2, rmse=np.sqrt(np.mean(residuals ** 2)),
        n_points=len(V), V=V, values=y, plateau=c, plateau_err=c_err,
    )


# ============================================================
# Loading + cleaning one variant's CSV
# ============================================================

def _parse_filename(stem):
    """'KCNC4 Activations(R516Pfs7)' -> ('KCNC4 Activations', 'R516Pfs7').
    Falls back to trailing '_'-separated token, e.g. 'KCNC4_Activations_WT_'."""
    m = re.match(r"^(.*?)\((.*?)\)", stem)
    if m:
        return m.group(1).strip(" _"), m.group(2).strip()
    trimmed = stem.rstrip("_")
    if "_" in trimmed:
        name, variant = trimmed.rsplit("_", 1)
        return name.replace("_", " ").strip(), variant
    return trimmed, None


@dataclass
class Recording:
    """One variant's raw + cleaned voltage-clamp data."""
    name: str
    variant: str
    path: Path
    data: dict            # experiment -> Series, as loaded
    clean: dict           # experiment -> Series, passed QC
    rejected: dict        # experiment -> reason

    @classmethod
    def from_csv(cls, path, normalisation_voltage, voltages=None,
                  name=None, variant=None):
        path = Path(path)
        voltages = voltages or VOLTAGES

        if normalisation_voltage not in voltages:
            raise ValueError(
                f"normalisation_voltage {normalisation_voltage} not in "
                f"voltage protocol {voltages}"
            )

        parsed_name, parsed_variant = _parse_filename(path.stem)
        name = name or parsed_name
        variant = variant or parsed_variant

        df = pd.read_csv(path, header=None)
        if len(df) > len(voltages):
            raise ValueError(
                f"{path.name} has {len(df)} rows but only "
                f"{len(voltages)} voltages are defined"
            )
        df.index = voltages[:len(df)]
        df.columns = [f"exp{i + 1}" for i in range(len(df.columns))]

        data = {col: df[col] for col in df.columns}
        clean, rejected = {}, {}

        for exp, values in data.items():
            if not values.isna().any():
                clean[exp] = values
                continue
            if normalisation_voltage not in values.index or pd.isna(
                values.loc[normalisation_voltage]
            ):
                rejected[exp] = "NaN present and normalisation point missing"
                continue
            norm_val = values.loc[normalisation_voltage]
            if not np.isclose(norm_val, 1.0):
                rejected[exp] = (
                    f"NaN present and normalisation value is "
                    f"{norm_val:.4g}, expected ~1"
                )
                continue
            clean[exp] = values

        return cls(name, variant, path, data, clean, rejected)


# ============================================================
# Converting I/Imax -> G/Gmax
# ============================================================

def current_to_conductance(values, reversal_potential, zero_within_mv=1.0, zero_at_erev=True):
    """G(V) = I(V) / (V - Erev), normalised to its own max.

    At V == Erev the driving force is ~0, so I/driving-force is
    mathematically undefined there (0/0). What that point *should* be
    set to depends on the protocol:

    - Activation (`zero_at_erev=True`, the default): V is the actual
      test-pulse voltage, so V == Erev means no net current is expected
      there regardless - G is set explicitly to 0 rather than dropping
      a real voltage step from every fit.
    - Inactivation (`zero_at_erev=False`): V is the swept *prepulse*,
      and Erev = -80 mV here typically coincides with full availability
      (the channel's peak current), not zero - forcing it to 0 would
      clamp the curve's maximum down to its minimum. The point is
      excluded (NaN) instead of guessing a value for it.
    """
    V = values.index.to_numpy(dtype=float)
    I = values.to_numpy(dtype=float)
    driving_force = V - reversal_potential

    with np.errstate(divide="ignore", invalid="ignore"):
        G = I / driving_force

    near_erev = np.abs(driving_force) < zero_within_mv
    if zero_at_erev:
        G[near_erev & np.isfinite(I)] = 0.0
    else:
        G[near_erev] = np.nan

    G_max = np.nanmax(G)
    if not np.isfinite(G_max) or G_max == 0:
        raise ValueError("no valid maximum conductance could be determined")

    return pd.Series(G / G_max, index=values.index, name=values.name)


# ============================================================
# Analysis: both interpretations for one Recording
# ============================================================

class Analysis:
    """Fits every experiment in a Recording under both interpretations."""

    def __init__(self, recording, reversal_potential, direction="activation",
                 fit_min=None, fit_max=None, label=None, plateau=False):
        self.recording = recording
        self.reversal_potential = reversal_potential
        self.direction = direction
        self.label = label or recording.variant or recording.name
        self.plateau = plateau
        self.fit_min = fit_min
        self.fit_max = fit_max

        self.g_direct = {
            exp: fit_boltzmann(v.index, v.values, direction, fit_min, fit_max, plateau)
            for exp, v in recording.clean.items()
        }

        self.i_converted_data = {}
        self.i_to_g = {}
        for exp, v in recording.clean.items():
            try:
                g = current_to_conductance(v, reversal_potential,
                                            zero_at_erev=(direction == "activation"))
                self.i_converted_data[exp] = g
                self.i_to_g[exp] = fit_boltzmann(
                    g.index, g.values, direction, fit_min, fit_max, plateau
                )
            except ValueError as exc:
                self.i_to_g[exp] = BoltzmannFit.failed(v.index, v.values, str(exc))

    def results_table(self, interpretation="G/Gmax"):
        fits = self.g_direct if interpretation == "G/Gmax" else self.i_to_g
        rows = [
            {
                "name": self.recording.name,
                "variant": self.label,
                "experiment": exp,
                "interpretation": interpretation,
                "V_half_mV": fit.V_half,
                "V_half_SE_mV": fit.V_half_err,
                "slope_k_mV": fit.k,
                "slope_SE_mV": fit.k_err,
                "plateau": fit.plateau,
                "plateau_SE": fit.plateau_err,
                "R2": fit.r_squared,
                "RMSE": fit.rmse,
                "n_points": fit.n_points,
                "error": fit.error,
            }
            for exp, fit in fits.items()
        ]
        return pd.DataFrame(rows)

    def summary(self, interpretation="G/Gmax"):
        df = self.results_table(interpretation).dropna(subset=["V_half_mV", "slope_k_mV"])
        if df.empty:
            return pd.DataFrame()
        n = len(df)
        return pd.DataFrame({
            "n": [n],
            "V_half_mean_mV": [df["V_half_mV"].mean()],
            "V_half_SEM_mV": [df["V_half_mV"].std(ddof=1) / np.sqrt(n)],
            "slope_mean_mV": [df["slope_k_mV"].mean()],
            "slope_SEM_mV": [df["slope_k_mV"].std(ddof=1) / np.sqrt(n)],
        })

    def mean_curve(self, interpretation="G/Gmax"):
        """Fit a Boltzmann curve to the across-experiment mean +/- SEM at
        each voltage (rather than averaging fitted V_half/k values)."""
        raw = self.recording.clean if interpretation == "G/Gmax" else self.i_converted_data
        table = pd.concat(raw.values(), axis=1)
        mean, sem = table.mean(axis=1), table.sem(axis=1)
        fit = fit_boltzmann(mean.index, mean.values, self.direction,
                             self.fit_min, self.fit_max, self.plateau)
        return mean, sem, fit


# ============================================================
# Plotting
# ============================================================

def _style_voltage_axis(ax, axis_style="left"):
    """axis_style='left' (default): a conventional axis, spine on the
    left, with a 'G/Gmax' label. axis_style='zero': the y-axis moves to
    sit at V=0 mV instead, using plain default tick marks/labels (no
    custom offsetting - that was fiddly and still overlapped the data
    for whichever tick landed near the curves), and no axis label
    (explained elsewhere, since a floating label there didn't read well).
    The redundant 0 tick is dropped either way, since the x-axis already
    marks zero.
    """
    ax.spines["top"].set_visible(False)
    ax.spines["right"].set_visible(False)
    ax.set_ylim(bottom=0)
    ax.grid(False)

    if axis_style == "zero":
        ax.spines["left"].set_position(("data", 0))
        ax.set_ylabel("")
    else:
        ax.set_ylabel("G/Gmax")

    ticks = [t for t in ax.get_yticks() if 0 < t <= ax.get_ylim()[1] + 1e-9]
    ax.set_yticks(ticks)


def _draw_axis_break(ax, at):
    """A small diagonal slash across the y-spine (matplotlib's standard
    broken-axis mark) showing the axis has been cut, instead of a text
    note. `at` is 'top' or 'bottom' - whichever edge sits next to the
    omitted range down to 0."""
    d = 0.5  # slash tilt
    ax.plot([0], [1.0 if at == "top" else 0.0], transform=ax.transAxes,
            marker=[(-1, -d), (1, d)], markersize=14, linestyle="none",
            color="black", mec="black", mew=1.2, clip_on=False)


def _style_bar_axis(ax):
    """Conventional axis for the categorical V½ bar chart. The spine
    must stay at its normal left-edge position here rather than being
    moved to data-x=0 - on a category axis that's just wherever the
    first bar happens to land (e.g. WT), which put the axis line
    straight through it."""
    ax.spines["top"].set_visible(False)
    ax.spines["right"].set_visible(False)
    ax.grid(False)


FIGURE_DIR = Path("Figures")

# Filesystem-friendly stand-ins for the interpretation names, used when
# building output filenames (a literal "/" or "->" isn't a valid path).
INTERPRETATION_SUFFIX = {"G/Gmax": "G_Gmax", "I/Imax -> G/Gmax": "I_to_G"}


_INVALID_FILENAME_CHARS = re.compile(r'[\\/:*?"<>|]')


def save_fig(fig, name, directory=FIGURE_DIR):
    """Save one figure as directory/name.png, creating the directory if
    needed. Used to collect every figure a script produces in one place
    with names that say what's in them, rather than leaving them to
    whatever the last-shown-window default would be. Characters invalid
    in a Windows filename (e.g. the '*' in a label like "R516Pfs*7") are
    stripped from `name` first - that's a display label, not a path, so
    this is the one place it needs to change, not the label itself."""
    directory = Path(directory)
    directory.mkdir(parents=True, exist_ok=True)
    safe_name = _INVALID_FILENAME_CHARS.sub("", name)
    fig.savefig(directory / f"{safe_name}.png", dpi=fig.dpi, bbox_inches="tight")


def _resolve_loc(legend_loc, label):
    """legend_loc may be one matplotlib location for every panel, or a
    {label: location} dict overriding individual ones; anything not in
    the dict falls back to 'upper left'."""
    if isinstance(legend_loc, dict):
        return legend_loc.get(label, "upper left")
    return legend_loc


def plot_variant(analysis, interpretation="G/Gmax", ax=None, color=COLOR,
                  overlay=None, overlay_label="WT", overlay_color=WT_COLOR,
                  axis_style="left", show_title=True, legend_loc="upper left"):
    """One clean plot: every experiment's fit + raw points in low-alpha
    `color`, the across-experiment mean bold on top. `overlay` is another
    Analysis (e.g. WT) drawn the same way for comparison. `axis_style`
    is passed straight to `_style_voltage_axis` ('left' or 'zero').
    `show_title=False` skips the title (e.g. in a multi-panel summary,
    where the legend already names the variant). `legend_loc` is any
    matplotlib legend location string - useful when the default
    'upper left' lands on top of a steep curve.
    """
    fits = analysis.g_direct if interpretation == "G/Gmax" else analysis.i_to_g
    if ax is None:
        _, ax = plt.subplots(figsize=(6, 5))

    for fit in fits.values():
        if not fit.ok:
            continue
        ax.scatter(fit.V, fit.values, s=25, color=color, alpha=DATA_ALPHA, linewidths=0)
        V_smooth, y_smooth = fit.curve(analysis.direction)
        ax.plot(V_smooth, y_smooth, color=color, alpha=FIT_ALPHA, linewidth=1)

    mean, sem, mean_fit = analysis.mean_curve(interpretation)
    if mean_fit.ok:
        ax.errorbar(mean.index, mean.values, yerr=sem, fmt="o", color=color,
                     markersize=5, capsize=2, zorder=5)
        V_smooth, y_smooth = mean_fit.curve(analysis.direction)
        ax.plot(V_smooth, y_smooth, color=color, linewidth=MEAN_LW,
                label=analysis.label, zorder=5)

    if overlay is not None:
        _, _, overlay_fit = overlay.mean_curve(interpretation)
        if overlay_fit.ok:
            V_smooth, y_smooth = overlay_fit.curve(overlay.direction)
            ax.plot(V_smooth, y_smooth, color=overlay_color, linewidth=MEAN_LW,
                     linestyle="--", label=overlay_label, zorder=4)

    ax.set_xlabel("Voltage (mV)")
    if show_title:
        ax.set_title(f"{analysis.recording.name} ({analysis.label}) — {interpretation}", pad=20)
    ax.legend(frameon=False, loc=legend_loc)
    _style_voltage_axis(ax, axis_style)
    return ax


# ============================================================
# Cohort: many variants analysed and plotted together
# ============================================================

class Cohort:
    """Holds one Analysis per variant so new variants (or a second protocol,
    e.g. inactivation) just mean adding another `add()` call rather than
    duplicating the load/fit/plot block."""

    def __init__(self, reversal_potential, direction="activation", plateau=False):
        self.reversal_potential = reversal_potential
        self.direction = direction
        self.plateau = plateau
        self.analyses = {}   # variant label -> Analysis

        cmap = plt.get_cmap("tab10")
        self._palette = [cmap(i) for i in range(cmap.N)]
        self.colors = {}

    def add(self, path, normalisation_voltage, label=None, voltages=None,
            fit_min=None, fit_max=None):
        recording = Recording.from_csv(path, normalisation_voltage, voltages)
        label = label or recording.variant or recording.name
        analysis = Analysis(recording, self.reversal_potential, self.direction,
                             fit_min, fit_max, label=label, plateau=self.plateau)
        self.analyses[label] = analysis
        self.colors[label] = self._palette[len(self.colors) % len(self._palette)]
        return analysis

    def results_table(self, interpretation="G/Gmax"):
        return pd.concat(
            [a.results_table(interpretation) for a in self.analyses.values()],
            ignore_index=True,
        )

    def plot_all(self, interpretation="G/Gmax", reference_label=None,
                 axis_style="left", dpi=100, legend_loc="upper left", show_title=False):
        """One figure per variant (not subplots), each in its own colour,
        with `reference_label` (e.g. 'WT') overlaid on every non-reference
        plot for comparison."""
        reference = self.analyses.get(reference_label)
        figs = {}
        for label, analysis in self.analyses.items():
            fig, ax = plt.subplots(figsize=(6, 5), dpi=dpi)
            overlay = reference if (reference is not None and label != reference_label) else None
            plot_variant(analysis, interpretation, ax=ax, color=self.colors[label],
                         overlay=overlay, overlay_label=reference_label,
                         axis_style=axis_style, legend_loc=_resolve_loc(legend_loc, label),
                         show_title=show_title)
            figs[label] = fig
        return figs

    def plot_vhalf_comparison(self, interpretation="G/Gmax", ax=None, title=False,
                               dpi=100, start_at_zero=True):
        summaries = []
        for label, analysis in self.analyses.items():
            s = analysis.summary(interpretation)
            if not s.empty:
                s.insert(0, "label", label)
                summaries.append(s)
        table = pd.concat(summaries, ignore_index=True)

        fig = ax.figure if ax is not None else plt.subplots(figsize=(6, 6), dpi=dpi)[0]
        ax = ax if ax is not None else fig.axes[0]
        ax.bar(table["label"], table["V_half_mean_mV"], width=0.5,
               yerr=table["V_half_SEM_mV"], capsize=4,
               color=[self.colors[l] for l in table["label"]])
        ax.set_ylabel("V½ (mV)")
        if title:
            ax.set_title(f"Activation V½ across variants — {interpretation}")
        ax.tick_params(axis="x", rotation=30)
        for tick in ax.get_xticklabels():
            tick.set_ha("right")
        ax.set_box_aspect(1)  # square panel, whatever height it's given
        _style_bar_axis(ax)

        if start_at_zero:
            ax.set_ylim(bottom=min(0, table["V_half_mean_mV"].min() - 2))
        else:
            # Zoomed in on the bar tops rather than from 0, so differences
            # between similarly-sized variants are actually visible - but
            # that means bar height alone is no longer proportional to the
            # value, so the cut is marked on the axis itself rather than
            # left to be noticed (or missed).
            lo = (table["V_half_mean_mV"] - table["V_half_SEM_mV"]).min()
            hi = (table["V_half_mean_mV"] + table["V_half_SEM_mV"]).max()
            pad = 0.15 * (hi - lo) if hi > lo else 1.0
            ax.set_ylim(lo - pad, hi + pad)
            _draw_axis_break(ax, at="top" if 0 > hi else "bottom")
        return fig, ax

    def plot_summary(self, interpretation="G/Gmax", reference_label=None,
                      axis_style="left", ncols=3, figsize=None, dpi=100,
                      legend_loc="upper left", bar_start_at_zero=True):
        """One importable figure: every variant's curve laid out in a
        `ncols`-wide grid (default 2 rows x 3 columns), a part-filled
        last row centred rather than left-hung, with the V½ comparison
        bar chart alongside it (separated by a blank spacer column so
        it doesn't crowd the curves), spanning the full grid height. No
        panel carries a title - the legend inside each already names it.
        `dpi` only needs raising for a final export; keep it low while
        you're still iterating on the layout. `legend_loc` is a single
        matplotlib location applied to every panel, or a
        {label: location} dict to override individual ones (e.g. a
        steep curve that the default 'upper left' legend sits on top of).
        `bar_start_at_zero=False` zooms the bar chart in on the data
        instead of from 0 - see `plot_vhalf_comparison`.
        Layout uses matplotlib's constrained-layout engine, which sizes
        the gaps from the actual tick/axis-label extents rather than a
        fixed fraction, so labels shouldn't need manual spacing at all."""
        labels = list(self.analyses.keys())
        nrows = -(-len(labels) // ncols)  # ceil division
        figsize = figsize or (3.6 * ncols + 5, 3.2 * nrows)
        fig = plt.figure(figsize=figsize, dpi=dpi, layout="constrained")

        fine = ncols * 2      # 2 sub-columns per panel so a part-filled row
        spacer = 1            # blank column of padding before the bar chart
        bar_cols = 4          # bigger than a single curve panel (2 sub-cols)
        gs = fig.add_gridspec(nrows=nrows, ncols=fine + spacer + bar_cols,
                               width_ratios=[1] * fine + [0.4] + [1] * bar_cols)

        reference = self.analyses.get(reference_label)
        for row_start in range(0, len(labels), ncols):
            row_labels = labels[row_start:row_start + ncols]
            row = row_start // ncols
            offset = (fine - len(row_labels) * 2) // 2
            for j, label in enumerate(row_labels):
                col = offset + j * 2
                ax = fig.add_subplot(gs[row, col:col + 2])
                overlay = reference if (reference is not None and label != reference_label) else None
                plot_variant(self.analyses[label], interpretation, ax=ax,
                             color=self.colors[label], overlay=overlay,
                             overlay_label=reference_label, axis_style=axis_style,
                             show_title=False, legend_loc=_resolve_loc(legend_loc, label))

        ax_bar = fig.add_subplot(gs[:, fine + spacer:])
        self.plot_vhalf_comparison(interpretation, ax=ax_bar, title=False,
                                    start_at_zero=bar_start_at_zero)
        return fig


# ============================================================
# Example usage
# ============================================================

if __name__ == "__main__":
    # Everything below is read from, and saved next to, this one folder -
    # change this path and both the input files and the Figures output
    # folder move with it.
    DATA_DIR = Path(r"D:\alex1\Documents\tracked_repos\KCNC4_LoF\patch_data")
    FIGURES = partial(save_fig, directory=DATA_DIR.parent / "Figures")

    cohort = Cohort(reversal_potential=-80, direction="activation")

    cohort.add(DATA_DIR / "KCNC4 Activations(WT).csv", normalisation_voltage=40, label="WT")
    cohort.add(DATA_DIR / "KCNC4 Activations(S268G).csv", normalisation_voltage=30, label="S268G")
    cohort.add(DATA_DIR / "KCNC4 Activations(R404H).csv", normalisation_voltage=40, label="R404H")
    cohort.add(DATA_DIR / "KCNC4 Activations(P324L).csv", normalisation_voltage=40, label="P324L")
    # filename can't hold the '*', so the display label is set explicitly here
    cohort.add(DATA_DIR / "KCNC4 Activations(R516Pfs7).csv",
               normalisation_voltage=40, label="R516Pfs*7")

    # P324L's curve rises steeply enough that the default upper-left
    # legend sits on top of it; used for both the per-variant figures
    # and the summary grid below.
    legend_loc = {"P324L": "lower right"}

    for interpretation in ("G/Gmax", "I/Imax -> G/Gmax"):
        suffix = INTERPRETATION_SUFFIX[interpretation]
        for label, fig in cohort.plot_all(interpretation, reference_label="WT",
                                           legend_loc=legend_loc).items():
            FIGURES(fig, f"activation_{label}_{suffix}")
        fig, _ = cohort.plot_vhalf_comparison(interpretation)
        FIGURES(fig, f"activation_vhalf_{suffix}")

    fig = cohort.plot_summary("G/Gmax", reference_label="WT", legend_loc=legend_loc)
    FIGURES(fig, "activation_summary_G_Gmax")
    fig = cohort.plot_summary("I/Imax -> G/Gmax", reference_label="WT", legend_loc=legend_loc)
    FIGURES(fig, "activation_summary_I_to_G")

    # --------------------------------------------------------
    # Inactivation: identical setup, direction="inactivation".
    #
    # NOTE on "I/Imax -> G/Gmax" here: that conversion (G = I / (V-Erev))
    # only makes physical sense when V is the actual voltage the current
    # was recorded at. That's true for an activation protocol (V IS the
    # test pulse), but a standard inactivation protocol records current
    # at one fixed test pulse while V is the swept *prepulse* voltage -
    # so this conversion uses the wrong voltage and the result isn't
    # physically meaningful. On the WT inactivation data this shows up
    # empirically, not just in theory: R² collapses to ~0.05-0.13 and
    # every V_half/k pins against its fit bound. Left available below
    # for completeness, but "G/Gmax" is the interpretation to use for
    # inactivation unless your protocol actually measures current at
    # the swept voltage itself.
    #
    # NOTE on plateau=True: Kv3.4's fast N-type inactivation is
    # frequently incomplete, and the WT data backs that up - the mean
    # curve settles near 0.55-0.6, not 0, so a standard 0-to-1 Boltzmann
    # structurally can't reach it. Adding a fitted floor (plateau=True)
    # took the mean-curve fit from R²=0.78 to R²=0.90 on this WT data,
    # and shifted V_half from +37 mV to -10 mV - the +37 mV figure was
    # an artefact of the old model straining to reach zero, not a real
    # shift in gating. Worth checking this holds once the other variants'
    # inactivation data is in, rather than assuming it carries over.
    #
    # There's also a "hook" at -80/-50 mV (values rise above 1 before
    # falling) - likely residual activation contaminating the earliest,
    # least-inactivated sweeps, not part of the equilibrium inactivation
    # curve itself. Excluding it (fit_min=-45) took R² to 0.97 on WT
    # without moving V_half or the plateau, which supports that reading.
    # Add fit_min=-45 to the .add() calls below if the same hook shows
    # up in the other variants.
    # --------------------------------------------------------
    inactivation = Cohort(reversal_potential=-80, direction="inactivation", plateau=True)

    inactivation.add(DATA_DIR / "KCNC4 Inactivation(WT).csv",
                      normalisation_voltage=-80, label="WT")
    inactivation.add(DATA_DIR / "KCNC4 Inactivation(S268G).csv",
                      normalisation_voltage=-80, label="S268G")
    inactivation.add(DATA_DIR / "KCNC4 Inactivation(R404H).csv",
                      normalisation_voltage=-80, label="R404H")
    inactivation.add(DATA_DIR / "KCNC4 Inactivation(P324L).csv",
                      normalisation_voltage=-80, label="P324L")
    inactivation.add(DATA_DIR / "KCNC4 Inactivation(R516Pfs7).csv",
                      normalisation_voltage=-80, label="R516Pfs*7")

    # Inactivation curves fall rather than rise, which leaves "lower
    # left" and "upper right" both genuinely empty of data - the
    # opposite would overlap the curve on an activation-style (rising)
    # plot, which is why this isn't applied to the cohort above.
    inactivation_legend_loc = {"G/Gmax": "lower left", "I/Imax -> G/Gmax": "upper right"}

    # The I/Imax -> G/Gmax V½ values sit in a narrow band (~-30 to -33 mV)
    # far from 0, so a from-zero bar chart is nearly all bar and barely
    # shows the differences between variants; zoomed in instead, with an
    # on-plot note since bar height is no longer proportional to value.
    bar_start_at_zero = {"G/Gmax": True, "I/Imax -> G/Gmax": False}

    for interpretation in ("G/Gmax", "I/Imax -> G/Gmax"):
        suffix = INTERPRETATION_SUFFIX[interpretation]
        figs = inactivation.plot_all(interpretation, reference_label="WT",
                                      legend_loc=inactivation_legend_loc[interpretation])
        for label, fig in figs.items():
            FIGURES(fig, f"inactivation_{label}_{suffix}")
        fig, _ = inactivation.plot_vhalf_comparison(
            interpretation, start_at_zero=bar_start_at_zero[interpretation])
        FIGURES(fig, f"inactivation_vhalf_{suffix}")

    fig = inactivation.plot_summary("G/Gmax", reference_label="WT",
                                     legend_loc=inactivation_legend_loc["G/Gmax"],
                                     bar_start_at_zero=bar_start_at_zero["G/Gmax"])
    FIGURES(fig, "inactivation_summary_G_Gmax")
    fig = inactivation.plot_summary("I/Imax -> G/Gmax", reference_label="WT",
                                     legend_loc=inactivation_legend_loc["I/Imax -> G/Gmax"],
                                     bar_start_at_zero=bar_start_at_zero["I/Imax -> G/Gmax"])
    FIGURES(fig, "inactivation_summary_I_to_G")

    print(f"Saved all figures to {(DATA_DIR.parent / 'Figures').resolve()}")
    plt.show()