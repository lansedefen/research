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
from gensim.models import Word2Vec

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

model = Word2Vec(texts, min_count=5, size=50, window=8, workers =10, iter = 20)
#print dir(model.wv),
for k in model.wv.vocab:
	print k + "\t" + ",".join([str(e) for e in model.wv[k]])
