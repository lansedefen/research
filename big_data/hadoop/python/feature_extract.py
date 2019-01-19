# -*- coding: utf-8 -*-
#!/usr/bin/env python
import sys
import json
import re
reload(sys)
sys.setdefaultencoding('utf-8')
sys.path.append("./util")
sys.path.append("./mr_pack/")
sys.path.append("./mr_pack/mr_pack")

from weibo_stream_parser import WSParser
from seg import *
from weibo_preprocess import *

stop_words = getStopDict("./stop_words")

def getBasicContentFeas(content):
     bqarr = re.findall(r"\[.*?\]", content)
     face_num = len(bqarr)
     bqarr = re.findall(r"@.*? ", content)
     nick_num = len(bqarr)
     bqarr = re.findall(r"#.*?#", content)
     topic_num = len(bqarr)
     return face_num, nick_num, topic_num
   
def get_content_feas(field_map):
    # a:基础文本特征
    global stop_words
    CONTENT = field_map.get("CONTENT", "")  # 原始文本长度
    content_len = len(CONTENT)
    PROCONTENT = weiboPrepare(CONTENT)
    pro_content_len = len(PROCONTENT) # 去除断链昵称等
    face_num, nick_num, topic_num = getBasicContentFeas(CONTENT)
    valid_content_rate = pro_content_len / (content_len + 1.0) #有效文本百分比

    #seg_list = [ele[0] for ele in word_cut(PROCONTENT, 2, "conf/tokenizer_test.conf")]
    seg_list = [ele[0] for ele in word_cut(PROCONTENT, 2, "conf/tokenizer.conf")]

    seg_list_filter = deleteStopwords(seg_list, stop_words)
    seg_string = ",".join(seg_list_filter)
    words_num = len(seg_list_filter) # 有效文本切词数
    is_long = field_map.get("ISLONG","0")

    QUALITY_SCORE = field_map.get("QUALITY_SCORE")
    quality_score = json.loads(QUALITY_SCORE)
    s_content = quality_score.get("s_content", 0.0)
    s_weighted = quality_score.get("s_weighted", 0.0)
    s_blog = quality_score.get("s_blog", 0.0)
    s_weiborank = quality_score.get("s_weiborank", 0.0)
    s_segment = quality_score.get("s_segment", 0.0)

    # b:类型
    PATTERN_RECOG_CONTENT = field_map.get("PATTERN_RECOG_CONTENT", "0")
    pattern = int(PATTERN_RECOG_CONTENT)
    is_advert = (pattern & 1<<0) >> 0 
    is_porn = (pattern & 1<<1) >> 1
    is_porn_uncertain = (pattern & 1<<2) >> 2
    is_active = (pattern & 1<<3) >> 3
    is_template = (pattern & 1<<5) >> 5
    is_poll = (pattern & 1<<6) >> 6
    ADV = field_map.get("ADV","0")

    # c:lda特征 todo
    content_feas = [content_len, pro_content_len, face_num, nick_num, topic_num, valid_content_rate, words_num, 
                    is_long, s_content, s_weighted, s_blog, s_weiborank, s_segment, 
                    is_advert, is_porn, is_porn_uncertain, is_active, is_template, is_poll, ADV]
    return ",".join([str(e) for e in content_feas]), seg_string

def get_user_feas(field_map):
    level = field_map.get("LEVEL", "0") # 用户等级, 1:普通用户,2:VIP用户,3:世博志愿者,4:尚未填写认证资料的企业微博注册用户,5:填写了认证资料的企业微博注册用户,6:通过审核的初级达人(只显示达人icon，不显示小红星), 7:通过审核的中级以上达人(既显示达人icon,也显示小红星),10:微女郎
    verified = field_map.get("VERIFIED", "0") # 微博作者是否为认证用户(0:非认证用户, 1:认证用户)
    verified_type = field_map.get("VERIFIEDTYPE", "-1") # 微博作者认证类型 当verified为1时, 0：名人, 1：政府, 2：企业, 3：媒体, 4：校园, 5：网站, 6：应用,7：团体, 其中0是黄V,1～7是蓝V 当verified为0时, -1：普通用户,8：待审企业,200：初级达人,220：通过审核的达人,400：已故认证用户,专页无此属性即为-1
    fans_level = field_map.get("VALID_FANS_LEVEL","0") # 有效粉丝等级
    INNER_USER_INFO = field_map.get("INNER_USER_INFO")
    user_info = json.loads(INNER_USER_INFO)["users"][0]
    valid_fans = user_info.get("valid_fans", "0")  #有效粉丝数量
    bi_follows = user_info.get("bi_follows", "0") #互粉数
    follows = user_info.get("follows", "0") #粉丝数量
    vtype = user_info.get("vtype", "0" ) # 认证用户类型
    statuses_count = user_info.get("statuses_count", "0" ) # 微博数
    del_statuses_count = user_info.get("del_statuses_count", "0" ) # 删除微博数
    create_time = user_info.get("create_at","0") #创建时间
    user_level = user_info.get("user_level", "0" ) # 用户级别
    utype =  int(user_info.get("utype", "0" )) # 用户类型
    if (utype & 2<<3 == 2<<3) or (utype & 2<<4 == 2<<4) or (utype & 2<<12 == 2<<12) or (utype & 2<<14 == 2<<14):
        return # black\作弊用户\话题养号用户\最终黑名单

    #昵称简介广告用户\昵称简介联系方式\内容广告用户\收益广告用
    is_adv_user = ((utype & 2<<1) >>1) or ((utype & 2<<5) >>5) or ((utype & 2<<6) >>6) or ((utype & 2<<13) >>13) 
    is_sell_user = (utype & 2<<7) >>7 #营销用户    
    is_fans_user = (utype & 2<<9) >>9  #粉丝用户
    
    user_feas = [level, verified , verified_type, fans_level, user_level, valid_fans, bi_follows, 
                follows, vtype, statuses_count, del_statuses_count, is_adv_user, is_sell_user, is_fans_user] 
    return ",".join([str(e) for e in user_feas])

def get_source_feas(field_map):
    try:
        pic_num = len( field_map.get("PIC", "").split() ) #图片个数0-9
        dp_num = len( field_map.get("DPICNUM","").split() ) # 动图个数
        sp_num = len( field_map.get("SPICNUM", "").split() ) # 静态图片个数
        link_num = len( field_map.get("LURLS","").split(" ") )
        filter = int(field_map.get("FILTER", "0"))  
        is_link = (filter & 1<<1) >> 1 # 是否含链接0-1
        is_vedio = (filter & 1<<4) >> 4 # 是否含视频0-1
        is_music = (filter & 1<<5) >> 5 # 是否含音乐0-1
        #is_weizhang # 是否含文章0-1
        #is_black_link # 短链黑名单0-1
        #is_adv_link # 广告域名0-1
        source_feas = [pic_num, dp_num, sp_num, is_link, link_num, is_vedio, is_music]
        return ",".join([str(e) for e in source_feas])
    except:
        return

class Mapper(WSParser.ProcessHandler):
    def __init__(self):
        self.parser = WSParser(self)
        self.filter_in = []

    def setFilterFields(self, filter_list):
        self.filter_in = filter_list

    def processOneRecord(self, field_map):
        pass

    def map(self, line):
        self.parser.offerLine(line)

class FilterMapper(Mapper):
    def processOneRecord(self, field_map):
        if not field_map:
            return

        if self.filter_in:
            for field in self.filter_in:
                if field in ["PATTERN_RECOG_CONTENT", "QI","VALIDFWNM","VERIFIED","VERIFIEDTYPE","WHITELIKENUM","ADV","LURLS"]:
                    continue
                if field not in field_map:
                    return

        if ( int(field_map.get('FILTER', "4") ) & 4 == 4): 
            return 

        ID = field_map.get('ID',"0")
        URL = field_map.get('URL',"0")
        QUALITY_SCORE = field_map.get('QUALITY_SCORE',"0")
        if ID == "0" or URL == "0" or QUALITY_SCORE == "0":
            return 

        CONTENT = field_map.get('CONTENT',"0")
        quality_score = json.loads(QUALITY_SCORE)
        q_score = quality_score.get("q_score", "0.0")
        
        # 1 文本特征
        content_feas, seg_string = get_content_feas(field_map)
        if content_feas is None:    
            return
        # 2 用户特征
        user_feas = get_user_feas(field_map)
        if user_feas is None:       
            return

        # 3 资源特征
        source_feas = get_source_feas(field_map)
        if source_feas is None:     
            return
        # 4 
        action_feas, word_feas = "0", "0"
        # 特征合并输出
        print  ID + "\t" + URL + "\t"+  content_feas + "\t" + user_feas + "\t" + source_feas + "\t" + word_feas + "\t" + action_feas + "\t" + CONTENT + "\t" + seg_string + "\t" + str(int(q_score)/63.0) 

if __name__ == '__main__':
    mapper = FilterMapper()
    #mapper.setFilterFields(['ID', "URL"])
    mapper.setFilterFields(['ID', "URL", 'QUALITY_SCORE',"FILTER", "QI", "ADV", "SOURCE" , "USER_TYPE", "LEVEL", "STATUS", "LURLS", "PIC", "ISLONG", 'CONTENT', 'PATTERN_RECOG_CONTENT',"INNER_USER_INFO", "VERIFIED", "VERIFIEDTYPE", "VALIDFWNM", "WHITELIKENUM", "VALID_FANS_LEVEL","DPICNUM","SPICNUM"])
    for line in sys.stdin:
        mapper.map(line.strip())
