#!coding=utf8
import sys
import re
import json

reload(sys)
sys.setdefaultencoding('utf-8')

def parse_showinfo(module):
    show_info = json.loads(module.strip())
    show_ids = []
    for v in show_info:
        cate = int(v.get("cate", -1))
        if cate in [31, 113, 10117, 10118, 26]:
            for k in v["info"]:
                mid, stat_list = k.get("mid", "0"), k.get("stat", [-1, -1, -1])
                if mid == "0" or stat_list == [-1, -1, -1] or type(stat_list) != list:
                    continue
                stat_list.append(0)
                show_ids.append( (mid, stat_list) )
    return show_ids

def getInverseIds(show_ids, click_ids):
    for k in show_ids:
        if k[0] in click_ids:
            k[1][3] += click_ids[k[0]]

    show_ids.reverse()
    flag, valid_click_ids = False, []
    for k in show_ids:
        if flag == True:
            if k[1][3] == 0:
                k[1][3] = -1
            valid_click_ids.append(k)
            continue

        if k[1][3] != 0:
            flag = True
            valid_click_ids.append(k)
    return valid_click_ids

def preprose():
        index, click_ids, show_ids = "", {}, [] 
        for line in sys.stdin:
            #try:
            if 1:
                seq_uid, module, action, mid = [e.strip() for e in line.strip().split("\t")]
                tmp_show_ids = parse_showinfo(module)
                if tmp_show_ids == []:
                    continue
                
                if index != seq_uid:
                    if index != "":
                        valid_click_ids = getInverseIds(show_ids, click_ids)
                        if valid_click_ids != []:
                            for k in valid_click_ids:
                                print k[0] + "\t" + "\t".join([str(v) for v in k[1]])

                    index, show_ids = seq_uid, tmp_show_ids 
                    click_ids = {}
                    click_ids[mid] = 1 + click_ids.get(mid, 0)
                else:
                    click_ids[mid] = 1 + click_ids.get(mid, 0)

preprose()

