import numpy as np

from neuron import h

from file_handling import verbose

def del_secs(verbose_level = 0):
    """Deletes all currently defined sections within NEURON's namespace."""
    for sec in h.allsec():
        h.delete_section(sec=sec)
    verbose('All neuron sections deleted', verbose_level)

def change_channels(target, new, verbose_level = 0):
    """
    All or nothing section-wise channel mechanism replacement.
    
    Multiplicative property value change based on original value.
    All the properties in the replacement channels must be in the target channel.
    
    Parameters
    ----------
    target : str
        Name of NEURON mechanism intended to be replace
    new : list
        List of [mechanism_name, {property: multiplier}] lists, to insert in the target
        Properties must exist in target.
    verbose_level : int, optional
        Output mode:
        0 = No output, 1 = print only, 2 = log only, 3 = print and log.
        Default is 0.

    """
    
    propNames = set(np.concatenate([list(k.keys()) for k in np.array(new, dtype=object)[:,1]]))
    
    for sec in h.allsec():
        
        if hasattr(sec(0.5), target):
            # Save previous property values
            sec_ref = getattr(sec(0.5), target)
            prev_prop = {name : getattr(sec_ref, name) for name in propNames}
            
            sec.uninsert(target)
            for mech, properties in new:
                sec.insert(mech)
                for seg in sec:
                    for prop_name in properties.keys():
                        mech_ref = getattr(seg, mech)
                        setattr(mech_ref, prop_name, prev_prop[prop_name] * properties[prop_name])

def variant_selector(model, modelArgs, variant = 'WT', verbose_level = 0):
    """
    Scales the maximum potassium conductance of Kv3.4 channels in a NEURON model.
    
    Parameters
    ----------
    model : cls
        Class reference containing NEURON sections.
    modelArgs :  tuple
        Variable number of positional arguments for the NEURON model.
    variant : str, optional
        'WT' = Unmodified model, '50GBAR' = 50% gkbar, '0GBAR' = 50% gkbar
        The default is 'WT'.
    verbose_level : int, optional
        Output mode:
        0 = No output, 1 = print only, 2 = log only, 3 = print and log.
        Default is 0.

    Returns
    -------
    m : NEURON model class
        Class instance containing NEURON sections.

    """
    
    del_secs(verbose)
    m = model(*modelArgs)
    verbose('Created WT model', 20, verbose_level)
    
    if variant == '50GBAR':
        change_channels('Kv3_4', 
                    [['Kv3_4', {'gkbar':0.5}]
                     ],
                    verbose)
        verbose('Changed model to variant: 50GBAR.', 20, verbose_level)
        
    if variant == '0GBAR':
        change_channels('Kv3_4', 
                    [['Kv3_4', {'gkbar':0}]
                     ],
                    verbose)
        verbose('Changed model to variant: 0GBAR.', 20, verbose_level)
    
    return m


def remove_dendrites(model, verbose_level = 0):
    """
    Remove sections referenced in list of dendritic sections

    Parameters
    ----------
    model : NEURON model class
        Instance of class containing NEURON sections.
        Must contain a list of sections, dend.
    verbose_level : int, optional
        Output mode:
        0 = No output, 1 = print only, 2 = log only, 3 = print and log.
        Default is 0.

    """
    for dend in model.dend:
        h.delete_section(sec=dend)
