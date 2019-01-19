from log_init import create_loger  
 
#logger = logging.getLogger('root.mod')
logger = create_loger()
logger.info('logger of mod say something...')
 
#logger = logging.getLogger('root.mod.submod')
logger.info('logger of submod say something...')
 
def tst():
	logger.info('this is submod.tst()...')
