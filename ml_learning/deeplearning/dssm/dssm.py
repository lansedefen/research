import random
import time
import sys
import numpy as np
import tensorflow as tf

class DSSM:
    def __init__(self, learning_rate, batch_size, decay_steps, decay_rate, sequence_length, vocab_size 
                 is_training, initializer=tf.random_normal_initializer(stddev=0.1), multi_label_flag=False,clip_gradients=5.0,decay_rate_big=0.50):
        """init all hyperparameter here"""
        self.num_classes = num_classes
        self.batch_size = batch_size
        self.vocab_size=vocab_size
        self.is_training=is_training
        self.learning_rate = tf.Variable(learning_rate, trainable=False, name="learning_rate")
        self.learning_rate_decay_half_op = tf.assign(self.learning_rate, self.learning_rate * decay_rate_big)
        self.num_filters_total=self.num_filters * len(filter_sizes) #how many filters totally.
        self.clip_gradients = clip_gradients
 
    with tf.name_scope('input'):
        # Shape [BS, TRIGRAM_D].
        self.query_batch = tf.sparse_placeholder(tf.float32, shape=[None, self.vocab_size], name='QueryBatch')
        self.doc_batch = tf.sparse_placeholder(tf.float32, shape=[None, self.vocab_size], name='DocBatch')
        self.label_batch = tf.sparse_placeholder(tf.float32, shape=[None, 2], name='LabelBatch')

    with tf.name_scope('L1'):
        l1_par_range = np.sqrt(6.0 / (TRIGRAM_D + L1_N))
        weight1 = tf.Variable(tf.random_uniform([TRIGRAM_D, L1_N], -l1_par_range, l1_par_range))
        bias1 = tf.Variable(tf.random_uniform([L1_N], -l1_par_range, l1_par_range))
        variable_summaries(weight1, 'L1_weights')
        variable_summaries(bias1, 'L1_biases')

        query_l1 = tf.sparse_tensor_dense_matmul(query_batch, weight1) + bias1
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
        train_step = tf.train.GradientDescentOptimizer(self.learning_rate).minimize(loss)

    with tf.name_scope('Test'):
        average_loss = tf.placeholder(tf.float32)
        loss_summary = tf.scalar_summary('average_loss', average_loss)

    """
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
        return query_in, doc_in
    """
