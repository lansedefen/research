import numpy as np
import re
import itertools
from collections import Counter
from tensorflow.contrib import learn
import jieba

def clean_str(string):
    """
    Tokenization/string cleaning for all datasets except for SST.
    Original taken from https://github.com/yoonkim/CNN_sentence/blob/master/process_data.py
    """
    #string = re.sub(r"[^A-Za-z0-9(),!?\'\`]", " ", string)
    string = re.sub(r"\'s", " \'s", string)
    string = re.sub(r"\'ve", " \'ve", string)
    string = re.sub(r"n\'t", " n\'t", string)
    string = re.sub(r"\'re", " \'re", string)
    string = re.sub(r"\'d", " \'d", string)
    string = re.sub(r"\'ll", " \'ll", string)
    string = re.sub(r",", " , ", string)
    string = re.sub(r"!", " ! ", string)
    string = re.sub(r"\(", " \( ", string)
    string = re.sub(r"\)", " \) ", string)
    #string = re.sub(r"\?", " \? ", string)
    #string = re.sub(r"\s{2,}", " ", string)
    return string.strip().lower()

def load_data_and_labels(data_file):
    """
    Loads MR polarity data from files, splits the data into words and generates labels.
    Returns split sentences and labels.
    """
    # Load data from files
    obj = open(data_file, "r")
    y, x_text, query= [],[],[]
    for ele in obj:
         ele = ele.strip().split("\t")
         if len(ele) !=5 or ele[0].strip() not in ["1", "-1"]:
            #print ele
            continue
         if (ele[0].strip() == "1"):
            y.append([0])
         else:
            y.append([1])

         query_text = ele[1].strip().decode("utf8")
         doc_text = ele[2].strip().decode("utf8")
         x_text.append( " ".join( jieba.cut(doc_text) ) )
         query.append( " ".join( jieba.cut(query_text) ) )
    return [x_text, np.array(y), np.array(query)]

def batch_iter(data, batch_size, num_epochs, shuffle=True):
    """
    Generates a batch iterator for a dataset.
    """
    data = np.array(data)
    data_size = len(data)
    num_batches_per_epoch = int((len(data)-1)/batch_size) + 1
    for epoch in range(num_epochs):
        # Shuffle the data at each epoch
        if shuffle:
            shuffle_indices = np.random.permutation(np.arange(data_size))
            shuffled_data = data[shuffle_indices]
        else:
            shuffled_data = data
        for batch_num in range(num_batches_per_epoch):
            start_index = batch_num * batch_size
            end_index = min((batch_num + 1) * batch_size, data_size)
            yield shuffled_data[start_index:end_index]

def build_voc(train_data_file, test_data_file, dev_sample_percentage, max_document_length):
    print("Loading data...")
    train_doc, train_label, train_query = load_data_and_labels(train_data_file)
    test_doc, test_label, test_query = load_data_and_labels(test_data_file)

    # Build vocabulary
    #max_document_length = max([len(x.split(" ")) for x in train_doc])
    vocab_processor = learn.preprocessing.VocabularyProcessor(max_document_length, 2)
    vocab_processor.fit(train_doc)

    train_doc_feas = np.array(list(vocab_processor.transform(train_doc)))
    train_query_feas = np.array(list(vocab_processor.transform(train_query)))

    test_doc_feas = np.array(list(vocab_processor.transform(test_doc)))
    test_query_feas = np.array(list(vocab_processor.transform(test_query)))

    np.random.seed(9)
    shuffle_indices = np.random.permutation(np.arange(len(train_label)))
    train_doc_feas_shuffled = train_doc_feas[shuffle_indices]
    train_query_feas_shuffled = train_query_feas[shuffle_indices]
    train_label_shuffled = train_label[shuffle_indices]

    # Split train/test set
    dev_sample_index = -1 * int(dev_sample_percentage * float(len(train_label)))
    train_doc_feas, dev_doc_feas = train_doc_feas_shuffled[:dev_sample_index], train_doc_feas_shuffled[dev_sample_index:]
    train_label, dev_label = train_label_shuffled[:dev_sample_index], train_label_shuffled[dev_sample_index:]
    train_query_feas, dev_query_feas = train_query_feas_shuffled[:dev_sample_index], train_query_feas_shuffled[dev_sample_index:]

    print("Vocabulary Size: {:d}".format(len(vocab_processor.vocabulary_)))
    return  train_doc_feas, train_label, train_query_feas, dev_doc_feas, dev_label, dev_query_feas, test_doc_feas, test_label, test_query_feas
