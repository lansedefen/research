#import logging
import submod
from log_init import create_loger  
 
#logger = logging.getLogger('root.mod')
logger = create_loger()
logger.info('logger of mod say something...')
 
def testLogger():
	logger.debug('this is mod.testLogger...')
	submod.tst()
