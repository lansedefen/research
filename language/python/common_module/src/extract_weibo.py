#encoding=utf8
import sys
import json
import time
import os
reload(sys)
sys.setdefaultencoding('utf-8')

from create_logger import logger 

def parse_weibo(text):
    if text is None:
        return

    weibo = json.loads(text)
    content = weibo.get("CONTENT", "0")
    pattern = weibo.get("PATTERN_RECOG_CONTENT", "0")
    quality_score = weibo.get("QUALITY_SCORE", "0")

    q_score = "0"
    #if quality_score != "0":
    #    quality_json = json.loads(quality_score)
    #    q_score = quality_json.get("q_score", "0")

    qi = weibo.get("QI","0")
    time = weibo.get("TIME","0")
    uid = weibo.get("UID","0")
    url = weibo.get("URL","0")
    logger.info(url + "\t" +  content)
    #print "aaa" + url
    return url, pattern, qi, uid, time, content, q_score

if __name__ == "__main__":
    parse_weibo(text)
