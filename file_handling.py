import os
import sys
import logging
import gc
from datetime import datetime
from IPython import get_ipython

def logger_setup(file_name, logger_name):
    """
    Create and setup a logging instance that outputs to a log file in /logs.

    Parameters
    ----------
    file_name : str
        Name of the log file to be created inside the 'logs' directory.

    Returns
    -------
    _logger : logging._logger
        Configured logging instance.
        
    """

    main_script_path = os.path.dirname(os.path.abspath(sys.argv[0]))
    directory = os.path.join(main_script_path, 'logs')
    os.makedirs(directory, exist_ok=True)
    
    _logger = logging.getLogger(logger_name)
    if _logger.hasHandlers():
        _logger.handlers.clear()
    _logger.setLevel(logging.DEBUG)
    
    log_path = os.path.join(directory, file_name)

    root, ext = os.path.splitext(log_path)
    if ext != '.log': log_path = root + '.log'
    
    file_handler = logging.FileHandler(log_path)
    file_handler.setLevel(logging.DEBUG)
    _logger.addHandler(file_handler)
    
    log_format = '%(asctime)s - %(name)s - %(levelname)s - %(message)s'
    formatter = logging.Formatter(log_format)
    file_handler.setFormatter(formatter)
    
    return _logger


def close_log_handlers():
    """Close logging instance and removes log file if not written to."""
    
    global logger
    global logger_name
    
    del_path = None
    for handler in logger.handlers:
        if isinstance(handler, logging.FileHandler):
            if os.path.getsize(handler.baseFilename) == 0:
                del_path = handler.baseFilename
        handler.close()
        logger.removeHandler(handler)
    logging.shutdown()
    if not del_path == None: os.remove(del_path)
    
    #Necessary for use in interactive enviromnemts
    del logger
    gc.collect()
    ipython.events.unregister('post_run_cell', close_log_handlers)


def verbose(message, logging_level = 10, verbose_level = 0):
    """
    Output text information either as a print statement, a log entry, or both.

    Parameters
    ----------
    message : str
        Message to be printed or logged.
    
    logging_level : int, optional
        Logging severity level:
        10 = DEBUG, 20 = INFO, 30 = WARNING, 40 = ERROR, 50 = CRITICAL.
        Default is 10 (DEBUG).
    
    verbose_level : int, optional
        Output mode:
        0 = No output, 1 = print only, 2 = log only, 3 = print and log.
        Default is 0.
        
    """
    
    if logging_level not in [10,20,30,40,50]:
        raise ValueError(f'Unknown verbose level: {logging_level} not in [10,20,30,40,50]')
    
    if verbose_level not in [0,1,2,3]:
        raise ValueError(f'Unknown verbose level: {verbose_level} not in [0,1,2]')
    
    if verbose_level in [1, 3]:
        print(message, flush = True)
    
    if verbose_level >= 2:
        logger.log(logging_level, message)


def directory_create(directory, verbose_level = 0):
    """
    Create target directory if non-existent, with logging or print capability.

    Parameters
    ----------
    directory : str
        Directory to be created.
    verbose_level : int, optional
        Output mode:
        0 = No output, 1 = print only, 2 = log only, 3 = print and log.
        Default is 0.

    """
    if not os.path.exists(directory):
        os.makedirs(directory, exist_ok=True)
        verbose(f"Created new directory: {directory}",
              logging_level = 20,
              verbose_level = verbose_level)
    else:
        verbose(f"Directory already exists: {directory}",
                      logging_level = 20,
                      verbose_level = verbose_level)


#Set up logger on module import
logger_name = 'logger'
log_file = f'{logger_name}_{datetime.now().strftime("%Y-%m-%d_%H-%M-%S")}.log'
if logger_name not in globals():
    logger = logger_setup(log_file, logger_name)

try:
    ipython = get_ipython()
    ipython.events.register('post_run_cell', close_log_handlers)
except:
    pass

if __name__ == '__main__':
    verbose('file_handling.py functions correctly', 10, 3)
    