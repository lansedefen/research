from log_init import create_loger

logger = create_loger()

logger.info('test main logger')
logger.info('start import module \'mod\'...')
logger.debug('let\'s test mod.testLogger()')

import mod
mod.testLogger()
 
