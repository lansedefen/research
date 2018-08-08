#coding=utf8
import sys
#from nltk.tokenize import RegexpTokenizer
#from stop_words import get_stop_words
#from nltk.stem.porter import PorterStemmer
reload(sys)
sys.setdefaultencoding('utf-8')
import numpy as np
import scipy.sparse as sp
from gensim import corpora, models
import gensim
import time
import datetime
#tokenizer = RegexpTokenizer(r'\w+')
#en_stop = get_stop_words('en')
#p_stemmer = PorterStemmer()

least_num = 5
texts = []
obj = open(sys.argv[1])
for ele in obj:
	line = ele.strip()
	words = line.split("\t")[8].split(",")
	texts.append([item.decode("utf8") for item in words])

dictionary = corpora.Dictionary(texts)
tokenid =  dictionary.token2id
corpus = [dictionary.doc2bow(text) for text in texts]
row = len(corpus)
col = len(tokenid)
m = sp.lil_matrix( (row, col) )
for i, k in enumerate(corpus):
	for index, value in k:
		m[i, index] = value	

m_csc = m.tocsc()
items= tokenid.items() 
backitems=[[v[1],v[0]] for v in items] 
backitems.sort() 
new_dict = [ backitems[i][1] for i in range(0,len(backitems))] 

filter_map = {}
for k, v in zip(xrange(0, col), new_dict):
	res = m_csc.getcol(k)
	num = len(res.nonzero()[0])
	if num > least_num:
		filter_map[v] = num
new_texts = []
for ele in texts:
	new_ele = [k for k in ele if filter_map.has_key(k)]
	new_texts.append(new_ele)
print "1 finish filter stop words", datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')
sys.stdout.flush()

####################################################
new_dictionary = corpora.Dictionary(new_texts)
new_corpus = [new_dictionary.doc2bow(text) for text in new_texts]
print "2 finish new dict", datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')
sys.stdout.flush()

topic_res = []
for i in xrange(50, 60, 10):
    ldamodel = gensim.models.ldamulticore.LdaMulticore(new_corpus, num_topics= i, id2word = new_dictionary, passes= 30, workers= 10, iterations=30,  batch=True)
    print "i", i , "\t", ldamodel.log_perplexity(new_corpus)
    topic_res = ldamodel.get_topics()

items= new_dictionary.token2id.items() 
backitems=[[v[1],v[0]] for v in items] 
backitems.sort() 
new_dict = [ backitems[i][1] for i in range(0,len(backitems))] 

print "finish sort words", datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')
sys.stdout.flush()
a, b = topic_res.shape
for i in range(0, b):
   sum_all = sum(topic_res[:,i])
   print new_dict[i], "\t", ",".join([str(value/sum_all) for value in topic_res[:,i]])
