import pickle
import random
import time
import sys
import numpy as np
import tensorflow as tf
from data_helpers import *

flags = tf.app.flags
FLAGS = flags.FLAGS
flags.DEFINE_string('summaries_dir', '/tmp/dssm-400-120-relu', 'Summaries directory')
flags.DEFINE_float('learning_rate', 0.1, 'Initial learning rate.')
flags.DEFINE_integer('max_steps', 900000, 'Number of steps to run trainer.')
flags.DEFINE_integer('epoch_steps', 18000, "Number of steps in one epoch.")
flags.DEFINE_integer('pack_size', 2000, "Number of batches in one pickle pack.")
flags.DEFINE_bool('gpu', 1, "Enable GPU or not")
TRIGRAM_D = 49284
NEG = 50
BS = 1000
L1_N = 400
L2_N = 120
query_in_shape = np.array([BS, TRIGRAM_D], np.int64)
doc_in_shape = np.array([BS, TRIGRAM_D], np.int64)

start = time.time()
doc_train_data = None
query_train_data = None
train_data_file, test_data_file = "./click_data2", "./click_data2"
train_doc_feas, train_label, train_query_feas, dev_doc_feas, dev_label, dev_query_feas, test_doc_feas, test_label, test_query_feas = build_voc(train_data_file, test_data_file, 0.05)
print train_doc_feas, train_label, train_query_feas
end = time.time()
print("Loading data from HDD to memory: %.2fs" % (end - start))

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

with tf.name_scope('input'):
    # Shape [BS, TRIGRAM_D].
    query_batch = tf.sparse_placeholder(tf.float32, shape=query_in_shape, name='QueryBatch')
    doc_batch = tf.sparse_placeholder(tf.float32, shape=doc_in_shape, name='DocBatch')

# Training
# ==================================================
with tf.Graph().as_default():
    session_conf = tf.ConfigProto(
      allow_soft_placement=FLAGS.allow_soft_placement,
      log_device_placement=FLAGS.log_device_placement)
    sess = tf.Session(config=session_conf)
    with sess.as_default():
        cnn = TextCNN(
            sequence_length=x_train.shape[1],
            num_classes=y_train.shape[1],
            vocab_size=len(vocab_processor.vocabulary_),
            embedding_size=FLAGS.embedding_dim,
            filter_sizes=list(map(int, FLAGS.filter_sizes.split(","))),
            num_filters=FLAGS.num_filters,
           l2_reg_lambda=FLAGS.l2_reg_lambda)

        # Define Training procedure
        global_step = tf.Variable(0, name="global_step", trainable=False)
        optimizer = tf.train.AdamOptimizer(0.005)
        grads_and_vars = optimizer.compute_gradients(cnn.loss)
        train_op = optimizer.apply_gradients(grads_and_vars, global_step=global_step)
 
    batches = batch_iter(list(zip(x_train, y_train, feas_train)), FLAGS.batch_size, FLAGS.num_epochs)
        # Training loop. For each batch...
    for batch in batches:
        x_batch, y_batch, feas_batch = zip(*batch)
        train_step(x_batch, y_batch, feas_batch)
        current_step = tf.train.global_step(sess, global_step)
        if current_step % FLAGS.evaluate_every == 0:
            print("\nEvaluation:")
            dev_step(x_dev, y_dev, feas_dev, writer=dev_summary_writer)
            test_step(test_x, test_y, test_other_feas)
            print("")
        if current_step % FLAGS.checkpoint_every == 0:
            path = saver.save(sess, checkpoint_prefix, global_step=current_step)
            print("Saved model checkpoint to {}\n".format(path))

"""
with tf.name_scope('L1'):
    l1_par_range = np.sqrt(6.0 / (TRIGRAM_D + L1_N))
    weight1 = tf.Variable(tf.random_uniform([TRIGRAM_D, L1_N], -l1_par_range, l1_par_range))
    bias1 = tf.Variable(tf.random_uniform([L1_N], -l1_par_range, l1_par_range))
    variable_summaries(weight1, 'L1_weights')
    variable_summaries(bias1, 'L1_biases')

    # query_l1 = tf.matmul(tf.to_float(query_batch),weight1)+bias1
    query_l1 = tf.sparse_tensor_dense_matmul(query_batch, weight1) + bias1
    # doc_l1 = tf.matmul(tf.to_float(doc_batch),weight1)+bias1
    doc_l1 = tf.sparse_tensor_dense_matmul(doc_batch, weight1) + bias1

    query_l1_out = tf.nn.relu(query_l1)
    doc_l1_out = tf.nn.relu(doc_l1)

with tf.name_scope('L2'):
    l2_par_range = np.sqrt(6.0 / (L1_N + L2_N))

    weight2 = tf.Variable(tf.random_uniform([L1_N, L2_N], -l2_par_range, l2_par_range))
    bias2 = tf.Variable(tf.random_uniform([L2_N], -l2_par_range, l2_par_range))
    variable_summaries(weight2, 'L2_weights')
    variable_summaries(bias2, 'L2_biases')

    query_l2 = tf.matmul(query_l1_out, weight2) + bias2
    doc_l2 = tf.matmul(doc_l1_out, weight2) + bias2
    query_y = tf.nn.relu(query_l2)
    doc_y = tf.nn.relu(doc_l2)

with tf.name_scope('FD_rotate'):
    # Rotate FD+ to produce 50 FD-
    temp = tf.tile(doc_y, [1, 1])

    for i in range(NEG):
        rand = int((random.random() + i) * BS / NEG)
        doc_y = tf.concat(0,
                          [doc_y,
                           tf.slice(temp, [rand, 0], [BS - rand, -1]),
                           tf.slice(temp, [0, 0], [rand, -1])])

with tf.name_scope('Cosine_Similarity'):
    # Cosine similarity
    query_norm = tf.tile(tf.sqrt(tf.reduce_sum(tf.square(query_y), 1, True)), [NEG + 1, 1])
    doc_norm = tf.sqrt(tf.reduce_sum(tf.square(doc_y), 1, True))

    prod = tf.reduce_sum(tf.mul(tf.tile(query_y, [NEG + 1, 1]), doc_y), 1, True)
    norm_prod = tf.mul(query_norm, doc_norm)

    cos_sim_raw = tf.truediv(prod, norm_prod)
    cos_sim = tf.transpose(tf.reshape(tf.transpose(cos_sim_raw), [NEG + 1, BS])) * 20

with tf.name_scope('Loss'):
    # Train Loss
    prob = tf.nn.softmax((cos_sim))
    hit_prob = tf.slice(prob, [0, 0], [-1, 1])
    loss = -tf.reduce_sum(tf.log(hit_prob)) / BS
    tf.scalar_summary('loss', loss)

with tf.name_scope('Training'):
    # Optimizer
    train_step = tf.train.GradientDescentOptimizer(FLAGS.learning_rate).minimize(loss)

# with tf.name_scope('Accuracy'):
#     correct_prediction = tf.equal(tf.argmax(prob, 1), 0)
#     accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))
#     tf.scalar_summary('accuracy', accuracy)

merged = tf.merge_all_summaries()

with tf.name_scope('Test'):
    average_loss = tf.placeholder(tf.float32)
    loss_summary = tf.scalar_summary('average_loss', average_loss)


def pull_batch(query_data, doc_data, batch_idx):
    # start = time.time()
    query_in = query_data[batch_idx * BS:(batch_idx + 1) * BS, :]
    doc_in = doc_data[batch_idx * BS:(batch_idx + 1) * BS, :]
    query_in = query_in.tocoo()
    doc_in = doc_in.tocoo()

    query_in = tf.SparseTensorValue(
        np.transpose([np.array(query_in.row, dtype=np.int64), np.array(query_in.col, dtype=np.int64)]),
        np.array(query_in.data, dtype=np.float),
        np.array(query_in.shape, dtype=np.int64))
    doc_in = tf.SparseTensorValue(
        np.transpose([np.array(doc_in.row, dtype=np.int64), np.array(doc_in.col, dtype=np.int64)]),
        np.array(doc_in.data, dtype=np.float),
        np.array(doc_in.shape, dtype=np.int64))

    # end = time.time()
    # print("Pull_batch time: %f" % (end - start))

    return query_in, doc_in


def feed_dict(Train, batch_idx):
    if Train:
        query_in, doc_in = pull_batch(query_train_data, doc_train_data, batch_idx)
    else:
        query_in, doc_in = pull_batch(query_test_data, doc_test_data, batch_idx)
    return {query_batch: query_in, doc_batch: doc_in}


config = tf.ConfigProto()  # log_device_placement=True)
config.gpu_options.allow_growth = True

with tf.Session(config=config) as sess:
    sess.run(tf.initialize_all_variables())
    train_writer = tf.train.SummaryWriter(FLAGS.summaries_dir + '/train', sess.graph)
    test_writer = tf.train.SummaryWriter(FLAGS.summaries_dir + '/test', sess.graph)

    # Actual execution
    start = time.time()
    for step in range(FLAGS.max_steps):
        batch_idx = step % FLAGS.epoch_steps
        if batch_idx % FLAGS.pack_size == 0:
            load_train_data(batch_idx / FLAGS.pack_size + 1)
        if batch_idx % (FLAGS.pack_size / 64) == 0:
            progress = 100.0 * batch_idx / FLAGS.epoch_steps
            sys.stdout.write("\r%.2f%% Epoch" % progress)
            sys.stdout.flush()

        sess.run(train_step, feed_dict=feed_dict(True, batch_idx % FLAGS.pack_size))
        if batch_idx == FLAGS.epoch_steps - 1:
            end = time.time()
            epoch_loss = 0
            for i in range(FLAGS.pack_size):
                loss_v = sess.run(loss, feed_dict=feed_dict(True, i))
                epoch_loss += loss_v

            epoch_loss /= FLAGS.pack_size
            train_loss = sess.run(loss_summary, feed_dict={average_loss: epoch_loss})
            train_writer.add_summary(train_loss, step + 1)
            print ("\nEpoch #%-5d | Train Loss: %-4.3f | PureTrainTime: %-3.3fs" %
                    (step / FLAGS.epoch_steps, epoch_loss, end - start))

            epoch_loss = 0
            for i in range(FLAGS.pack_size):
                loss_v = sess.run(loss, feed_dict=feed_dict(False, i))
                epoch_loss += loss_v

            epoch_loss /= FLAGS.pack_size

            test_loss = sess.run(loss_summary, feed_dict={average_loss: epoch_loss})
            test_writer.add_summary(test_loss, step + 1)

            start = time.time()
            print ("Epoch #%-5d | Test  Loss: %-4.3f | Calc_LossTime: %-3.3fs" %
                   (step / FLAGS.epoch_steps, epoch_loss, start - end))

"""
