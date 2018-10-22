import pickle
import random
import time
import sys
import numpy as np
import tensorflow as tf
from data_helpers import *
from dssm_dense import *
import scipy as sp

flags = tf.app.flags
FLAGS = flags.FLAGS
# Data loading params
tf.flags.DEFINE_float("dev_sample_percentage", .05, "Percentage of the training data to use for validation")
tf.flags.DEFINE_string("train_data_file", "./click_data3", "Data source for the positive data.")
tf.flags.DEFINE_string("test_data_file", "./click_data3", "Data source for the negative data.")

# Model Hyperparameters
tf.flags.DEFINE_float("dropout_keep_prob", 0.5, "Dropout keep probability (default: 0.5)")
tf.flags.DEFINE_float("l2_reg_lambda", 0.0, "L2 regularization lambda (default: 0.0)")
tf.flags.DEFINE_float("learning_rate", 0.001, "lr (default: 0.001)")
tf.flags.DEFINE_integer("vocab_size", 40, "lr (default: 50)")
tf.flags.DEFINE_integer("num_classes", 2, "class num (default: 2)")
BS = 1000
L1_N = 400
L2_N = 120

# Training parameters
tf.flags.DEFINE_integer("batch_size", 10, "Batch Size (default: 64)")
tf.flags.DEFINE_integer("num_epochs", 200, "Number of training epochs (default: 200)")
tf.flags.DEFINE_integer("evaluate_every",200, "Evaluate model on dev set after this many steps (default: 100)")
tf.flags.DEFINE_integer("checkpoint_every", 200, "Save model after this many steps (default: 100)")
tf.flags.DEFINE_integer("num_checkpoints", 5, "Number of checkpoints to store (default: 5)")

# Misc Parameters
tf.flags.DEFINE_boolean("allow_soft_placement", True, "Allow device soft device placement")
tf.flags.DEFINE_boolean("log_device_placement", False, "Log placement of ops on devices")

def variable_summaries(var, name):
    with tf.name_scope('summaries'):
        mean = tf.reduce_mean(var)
        tf.scalar_summary('mean/' + name, mean)
        with tf.name_scope('stddev'):
            stddev = tf.sqrt(tf.reduce_sum(tf.square(var - mean)))
        tf.scalar_summary('sttdev/' + name, stddev)
        tf.scalar_summary('max/' + name, tf.reduce_max(var))
        tf.scalar_summary('min/' + name, tf.reduce_min(var))
        tf.histogram_summary(name, var)

PATH = "./tf_dataset_and_estimator_apis"
PATH_DATASET = PATH + os.sep + "dataset"
FILE_TRAIN = PATH_DATASET + os.sep + "iris_training.csv"
FILE_TEST = PATH_DATASET + os.sep + "iris_test.csv"

training_filenames = ["./tmp.csv"] 
validation_filenames = ["./tmp.csv"] 
num_epochs = 1
num_class = 3

def decode_line(line):
    # Decode the csv_line to tensor.
    record_defaults = [[1.0] for col in range(81)]
    items = tf.decode_csv(line, record_defaults)
    features = items[1:81]
    label = items[0]

    features = tf.cast(features, tf.float32)
    label = tf.cast(label, tf.int64)
    label = tf.one_hot(label,num_class)
    return features,label

def create_dataset(filename, batch_size=32, is_shuffle=False, n_repeats=0):
    dataset = tf.data.TextLineDataset(filename).skip(1)
    if n_repeats > 0:
        dataset = dataset.repeat(n_repeats)         # for train
    # dataset = dataset.map(decode_line).map(normalize)  
    dataset = dataset.map(decode_line)    
    # decode and normalize
    if is_shuffle:
        pass
        #dataset = dataset.shuffle(10000)            # shuffle
    dataset = dataset.batch(batch_size)
    return dataset

# Create different datasets
training_dataset = create_dataset(training_filenames, batch_size=32, \
                                  is_shuffle=True, n_repeats=num_epochs) # train_filename
validation_dataset = create_dataset(validation_filenames, batch_size=32, \
                                  is_shuffle=True, n_repeats=num_epochs) # val_filename

handle = tf.placeholder(tf.string, shape=[])
iterator = tf.data.Iterator.from_string_handle(
    handle, training_dataset.output_types, training_dataset.output_shapes)
features, labels = iterator.get_next()

training_iterator = training_dataset.make_one_shot_iterator()
validation_iterator = validation_dataset.make_initializable_iterator()

with tf.Session() as sess:
    training_handle = sess.run(training_iterator.string_handle())
    validation_handle = sess.run(validation_iterator.string_handle())

    #print training_handle
    # Define Training procedure
    decay_steps=1000
    decay_rate=0.95
    is_training=True 

    dssm = DSSM(FLAGS.num_classes, FLAGS.learning_rate, FLAGS.batch_size, decay_steps, decay_rate, FLAGS.vocab_size, 
                 is_training, initializer = tf.random_normal_initializer(stddev=0.1), clip_gradients=5.0)
    sess.run(tf.global_variables_initializer())
    sess.run(tf.local_variables_initializer())

    print("TRAIN\n",sess.run([labels, features], feed_dict={handle: training_handle}))

    """
    batches = batch_iter(list(zip(train_doc_feas, train_label, train_query_feas)), FLAGS.batch_size, FLAGS.num_epochs)
    for batch in batches:
        train_doc_feas, train_label, train_query_feas = zip(*batch)
        feed_dict={dssm.query_batch: train_query_feas, dssm.doc_batch: train_doc_feas, dssm.label_batch: train_label}
        query_y, cos_sim_raw, norm_prod, prod, losses, label, loss, global_step, train_op = sess.run([dssm.query_y, 
               dssm.cos_sim_raw, dssm.norm_prod, dssm.prod, dssm.losses, dssm.label_batch, dssm.loss, dssm.global_step, dssm.train_op], feed_dict) 
        print ("train loss:", loss, "train_step:", global_step) 
        if global_step % FLAGS.evaluate_every == 1:
            print("\nEvaluation:")
            feed_dict={dssm.query_batch: dev_query_feas, dssm.doc_batch: dev_doc_feas, dssm.label_batch: dev_label}
            query_y, cos_sim_raw, norm_prod, prod, losses, label, loss = sess.run([dssm.query_y,
                               dssm.cos_sim_raw, dssm.norm_prod, dssm.prod, dssm.losses, dssm.label_batch, dssm.loss], feed_dict)
            print ("test loss:", loss, "test_step:",  global_step) 

    """
