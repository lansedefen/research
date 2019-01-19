#!/usr/bin/env python
# -*- coding: utf-8 -*-
 
import os
import logging
from cloghandler import ConcurrentRotatingFileHandler

LOG_PATH = "./"
LOG_FILENAME, LOG_MAX_BYTES = "test_log", 1000000000

def create_logger(log_path=os.getcwd(),  # 存放日志的目录
                  level=logging.DEBUG,
                  formatter=logging.BASIC_FORMAT,  # 日志输出格式
                  logger_name="",  # 可以使用logging.getlogger(logger_name)使用此logger
                  mode='a', 
                  delay=0,
                  debug=True,
                  log_filename=LOG_FILENAME,  # 保存日志的文件名（备份出的文件会以此名+.1、 .2命名）
                  encoding=None,
                  maxBytes=LOG_MAX_BYTES,  # 每个日志文件的最大容量
                  backupCount=3 ):
    # 判断存放日志的文件夹是否存在 如果不存在新建
    if not os.path.exists(log_path):
        os.mkdir(log_path)
    # 存放log的文件名
    log_filename = os.path.join(log_path, log_filename)
 
    # 创建一个logger
    logger = logging.getLogger(logger_name)
    # 设置日志等级
    logger.setLevel(level)
    # 创建一个滚动日志处理器
    crfh = ConcurrentRotatingFileHandler(log_filename, mode=mode, maxBytes=maxBytes, backupCount=backupCount, delay=delay, debug=debug, encoding=encoding)
    # 定义handler的输出格式
    # 设定日志输出格式
    crfh.setFormatter(formatter)
    # 添加日志处理器
    logger.addHandler(crfh)
    # 返回logger对象
    return logger
 
# 日志格式
formatter_log = logging.Formatter('%(asctime)s - %(filename)s [line: %(lineno)d] 【%(levelname)s】 ----- %(message)s')
# 生成一个logger
logger = create_logger(log_path=LOG_PATH, logger_name="mylogger", formatter=formatter_log)
#logger.error("error msg") 
