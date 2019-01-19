import logging
import logging.config

logging.config.fileConfig('./conf/logging.ini')

def create_loger(name = "root"):
    return logging.getLogger(name)
