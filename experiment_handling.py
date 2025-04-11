import multiprocessing

from neuron import h

from model_selector import verbose

h.load_file("stdrun.hoc")
h.load_file("nrngui.hoc")
h.load_file("parcom.hoc")

cores = multiprocessing.cpu_count()
p = h.ParallelComputeTool()
p.change_nthread(cores, 1)


def initialise():
    """Begin NEURON simulation with multiprocessing."""
    
    p.multisplit(1)
    
    Fixed_step = h.CVode()
    Fixed_step.active(0)
    
    h.finitialize(h.v_init)
    h.run()
    p.multisplit(0)


def set_conditions(dur, v_init, oC, dt = 0.025, verbose_level = 0):
    """
    Set NEURON simulation parameters and begin simulation.

    Parameters
    ----------
    dur : float
        Simulation duration (ms).
    v_init : float
        NEURON simulation initial membrane potential (mV).
    oC : float
        NEURON simulation temperature (oC).
    dt : float, optional
        NEURON simulation timestep (ms). The default is 0.025ms.
    verbose_level : int, optional
        Output mode:
        0 = No output, 1 = print only, 2 = log only, 3 = print and log.
        Default is 0.

    """
        
    h.dt = dt
    h.celsius = oC
    h.tstop = dur
    h.v_init = v_init
    
    verbose(f'Running simulation for : {dur} with initial conditions v_init: {v_init}mV temperature: {oC}oC with fixed timestep: {dt}ms',
            20,
            verbose_level)
    initialise()
    

def get_traces(traces):
    """
    Sets up NEURON vectors to record variables according to given variable references.

    Parameters
    ----------
    traces : list
        NEURON variable references to be recorded in the simulation.

    Returns
    -------
    t : neuron.h.vector
        Vector recording the time variable in the simulation
    out_traces : list
        List of NEURON vectors recording the variables input in traces.

    """
    
    t = h.Vector().record(h._ref_t)
    out_traces = list()
    for trace in traces:
        out_traces.append(h.Vector().record(trace))
        
    return t, out_traces


def current_clamp(Iinj, dur, delay, v_init, oC, loc, traces, verbose_level = 0):
    """
    Inserts a current clamp point process into a NEURON model.

    Parameters
    ----------
    Iinj : float
        Injected current amplitude for current clamp (nA).
    dur : float
        Simulation duration (ms).
    delay : float
        Current clamp delay time before current injection (ms).
    v_init : float
        NEURON simulation initial membrane potential (mV).
    oC : float
        NEURON simulation temperature (oC).
    loc : neuron.h.Section
        Section reference to insert current clamp instance.
    traces : list
        NEURON variable references to be recorded in the simulation.
    verbose_level : int, optional
        Output mode:
        0 = No output, 1 = print only, 2 = log only, 3 = print and log.
        Default is 0.

    Returns
    -------
    ic : neuron.h.IClamp
        Reference to create current clamp point process.
    """
    
    ic = h.IClamp(loc)
    ic.dur = dur
    ic.amp = Iinj
    ic.delay = delay
    
    verbose(f'Adding current clamp to section: {loc} with duration: {dur}ms and amplitude: {Iinj}nA after delay: {delay}ms',
            20,
            verbose_level)
    
    return ic