import random
import time
import sys
import numpy as np
import tensorflow as tf
import scipy as sp

class DSSM:
    def __init__(self, num_classes, learning_rate, batch_size, decay_steps, decay_rate, vocab_size, 
                 is_training, initializer = tf.random_normal_initializer(stddev=0.1), clip_gradients=5.0):
        self.num_classes = num_classes
        self.learning_rate = tf.Variable(learning_rate, trainable=False, name="learning_rate")
        self.batch_size = batch_size
        self.decay_steps = decay_steps
        self.decay_rate = decay_rate 
        self.vocab_size = vocab_size
        self.is_training = is_training
        self.global_step = tf.Variable(0, name="global_step", trainable=False)
        self.L1_N = 1000        
        self.L2_N = 100
        #self.learning_rate_decay_half_op = tf.assign(self.learning_rate, self.learning_rate * decay_rate_big)
        #self.num_filters_total = self.num_filters * len(filter_sizes) #how many filters totally.
        #self.clip_gradients = clip_gradients
 
        #with tf.name_scope('input'):
        if 1:
            # Shape [BS, TRIGRAM_D].
            self.query_batch = tf.placeholder(tf.float32, shape=[None, self.vocab_size], name='query_batch')
            self.doc_batch = tf.placeholder(tf.float32, shape=[None, self.vocab_size], name='doc_batch')
            self.label_batch = tf.placeholder(tf.float32, [None, 1], name='label_batch')
            #print (self.query_batch, self.doc_batch, self.label_batch)
        
        with tf.name_scope('L1'):
            l1_par_range = np.sqrt(6.0 / (self.vocab_size + self.L1_N))
            weight1 = tf.Variable(tf.random_uniform([self.vocab_size, self.L1_N], -l1_par_range, l1_par_range))
            bias1 = tf.Variable(tf.random_uniform([self.L1_N], -l1_par_range, l1_par_range))

            query_l1 = tf.matmul(self.query_batch, weight1) + bias1
            doc_l1 = tf.matmul(self.doc_batch, weight1) + bias1

            self.query_l1_out = tf.nn.relu(query_l1)
            self.doc_l1_out = tf.nn.relu(doc_l1)

        with tf.name_scope('L2'):
            l2_par_range = np.sqrt(6.0 / (self.L1_N + self.L2_N))
            weight2 = tf.Variable(tf.random_uniform([self.L1_N, self.L2_N], -l2_par_range, l2_par_range))
            bias2 = tf.Variable(tf.random_uniform([self.L2_N], -l2_par_range, l2_par_range))

            query_l2 = tf.matmul(self.query_l1_out, weight2) + bias2
            doc_l2 = tf.matmul(self.doc_l1_out, weight2) + bias2
            self.query_y = tf.nn.relu(query_l2)
            self.doc_y = tf.nn.relu(doc_l2)


        with tf.name_scope('Cosine_Similarity'):
            # Cosine similarity
            self.query_norm = tf.sqrt(tf.reduce_sum(tf.square(self.query_y), 1, True))
            self.doc_norm = tf.sqrt(tf.reduce_sum(tf.square(self.doc_y), 1, True))
            self.norm_prod = tf.multiply(self.query_norm, self.doc_norm)
            self.prod = tf.reduce_sum(tf.multiply(self.query_y, self.doc_y), 1, True)
            self.cos_sim_raw = tf.truediv(self.prod, self.norm_prod)

            self.losses = tf.nn.sigmoid_cross_entropy_with_logits(labels = self.label_batch, logits = self.cos_sim_raw); #losses=tf.nn.softmax_cross_entropy_with_logits(labels=self.input__y,logits=self.logits)
            self.loss= tf.reduce_mean(self.losses)         #shape=().   average loss in the batch
            #l2_losses = tf.add_n([tf.nn.l2_loss(v) for v in tf.trainable_variables() if 'bias' not in v.name]) * l2_lambda
            #loss = loss + l2_losses

        with tf.name_scope('Training'):
            # Optimizer
            self.train_op = tf.train.GradientDescentOptimizer(self.learning_rate).minimize(self.loss, global_step = self.global_step)
            #optimizer = tf.train.AdamOptimizer(0.001)
            #grads_and_vars = optimizer.compute_gradients(cnn.loss)                                                                                                                                          
            #train_op = optimizer.apply_gradients(grads_and_vars, global_step=global_step)

        """
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
            return query_in, doc_in
        """

def test():
    num_classes = 2 
    learning_rate=0.001
    batch_size=8
    decay_steps=1000
    decay_rate=0.95
    vocab_size= 50
    is_training=True 
    dssm = DSSM(num_classes, learning_rate, batch_size, decay_steps, decay_rate, vocab_size, 
                 is_training, initializer = tf.random_normal_initializer(stddev=0.1), clip_gradients=5.0)
    #if 'session' in locals() and session is not None:
    #    print('Close interactive session')
    #    session.close()

    gpu_options=tf.GPUOptions(per_process_gpu_memory_fraction=0.005)
    sess = tf.Session(config=tf.ConfigProto(gpu_options=gpu_options)) 
    #tf.device('/cpu:0')
    #with tf.device('/device:cPU:1'):
    #with tf.Session() as sess:
    if 1:
       sess.run(tf.global_variables_initializer())
       for i in range(50):
           query_batch = np.random.randn(batch_size, vocab_size)
           doc_batch = np.random.randn(batch_size, vocab_size)
           label_batch= np.random.randn(batch_size, 1) #[None, self.sequence_length]
           label_batch[label_batch>=0]=1
           label_batch[label_batch<0] = 0
           #print label_batch, type(label_batch), label_batch.shape
           feed_dict={dssm.query_batch: query_batch, dssm.doc_batch: doc_batch, dssm.label_batch: label_batch}
           lr, query_y, cos_sim_raw, norm_prod, prod, losses, label, loss, step = sess.run([dssm.learning_rate, dssm.query_y, 
               dssm.cos_sim_raw, dssm.norm_prod, dssm.prod, dssm.losses, dssm.label_batch, dssm.loss, dssm.train_step], feed_dict) 
           #print ("lr:", lr, "query_y:", query_y, "cos_sim_raw:", cos_sim_raw, "norm_prod:", 
           print ("prod:", prod, "losses:", losses, "label:", label, "loss:", loss, "step:", step)

#test()
