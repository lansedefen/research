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

def dense2sparse(dense_mat):
   #print type(dense_mat)
   row, col = dense_mat.shape
   tmp = sp.sparse.csc_matrix((dense_mat), (row,col) )
   col, row = tmp.nonzero()
   indices = []
   for k,v in zip(col, row):
       indices.append([k,v])
   indices = np.array(indices)
   values = tmp.data
   shape = np.array([batch_size, vocab_size], dtype=np.int64)
   return tf.SparseTensorValue(indices, values, shape)

start = time.time()
train_doc_feas, train_label, train_query_feas, dev_doc_feas, dev_label, dev_query_feas, test_doc_feas, test_label, test_query_feas = build_voc(FLAGS.train_data_file, FLAGS.test_data_file, FLAGS.dev_sample_percentage, FLAGS.vocab_size)
end = time.time()
print("Loading data from HDD to memory: %.2fs" % (end - start))

obj_w = open("tmp.csv", "w")
for a,b,c in zip(train_label, train_doc_feas, train_query_feas):
    a = [str(k) for k in a]
    b = [str(k) for k in b]
    c = [str(k) for k in c]
    a.extend(b)
    a.extend(c)
    tmp = ",".join(a)
    obj_w.write(tmp + "\n")


# Training
gpu_options=tf.GPUOptions(per_process_gpu_memory_fraction=0.01)
sess = tf.Session(config=tf.ConfigProto(gpu_options=gpu_options)) 
if 1:
    # Define Training procedure
    decay_steps=1000
    decay_rate=0.95
    is_training=True 

    dssm = DSSM(FLAGS.num_classes, FLAGS.learning_rate, FLAGS.batch_size, decay_steps, decay_rate, FLAGS.vocab_size, 
                 is_training, initializer = tf.random_normal_initializer(stddev=0.1), clip_gradients=5.0)
    sess.run(tf.global_variables_initializer())
    sess.run(tf.local_variables_initializer())
 
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

        #if current_step % FLAGS.checkpoint_every == 0:
        #    path = saver.save(sess, checkpoint_prefix, global_step=current_step)
        #    print("Saved model checkpoint to {}\n".format(path))
           #print label_batch, type(label_batch), label_batch.shape
           #feed_dict={dssm.query_batch: query_batch, dssm.doc_batch: doc_batch, dssm.label_batch: label_batch}
           #lr, query_y, cos_sim_raw, norm_prod, prod, losses, label, loss, step = sess.run([dssm.learning_rate, dssm.query_y, 
           #    dssm.cos_sim_raw, dssm.norm_prod, dssm.prod, dssm.losses, dssm.label_batch, dssm.loss, dssm.train_step], feed_dict) 
           #print ("lr:", lr, "query_y:", query_y, "cos_sim_raw:", cos_sim_raw, "norm_prod:", 
           #print ("prod:", prod, "losses:", losses, "label:", label, "loss:", loss, "step:", step)
