import random
import time
import sys
import numpy as np
import tensorflow as tf

class DSSM:
    def __init__(self, num_classes, learning_rate, batch_size, decay_steps, decay_rate, vocab_size, 
                 is_training, initializer = tf.random_normal_initializer(stddev=0.1), clip_gradients=5.0):
        """init all hyperparameter here"""
        self.num_classes = num_classes
        self.learning_rate = learning_rate 
        #self.learning_rate = tf.Variable(learning_rate, trainable=False, name="learning_rate")
        self.batch_size = batch_size
        self.decay_steps = decay_steps
        self.decay_rate = decay_rate 
        self.vocab_size = vocab_size
        self.is_training = is_training
        self.loss = 0.0 
        self.query_y = 0.0 
        self.doc_y = 0.0 
        #self.learning_rate_decay_half_op = tf.assign(self.learning_rate, self.learning_rate * decay_rate_big)
        #self.num_filters_total=self.num_filters * len(filter_sizes) #how many filters totally.
        #self.clip_gradients = clip_gradients
 
        #with tf.name_scope('input'):
        if 1:
            # Shape [BS, TRIGRAM_D].
            #self.input_y_multilabel = tf.placeholder(tf.float32, [None,self.num_classes], name="input_y_multilabel")
            #self.input_x = tf.placeholder(tf.int32, [None, self.sequence_length], name="input_x")  # X
            self.input_x = tf.placeholder(tf.int32, [None, self.vocab_size], name='input_x')
            #self.query_batch = tf.sparse_placeholder(tf.float32, shape=[None, self.vocab_size], name='query_batch')
            #self.doc_batch = tf.placeholder(tf.float32, [None, self.vocab_size], name='doc_batch')
            #self.doc_batch = tf.sparse_placeholder(tf.float32, shape=[None, self.vocab_size], name='doc_batch')
            #self.label_batch = tf.placeholder(tf.float32, [None, 1], name='label_batch')
            #self.label_batch = tf.sparse_placeholder(tf.float32, shape=[None, 1], name='label_batch')
            #print (self.query_batch, self.doc_batch, self.label_batch)
        
        """
        with tf.name_scope('L1'):
            self.L1_N = 1000        
            l1_par_range = np.sqrt(6.0 / (self.vocab_size + self.L1_N))
            weight1 = tf.Variable(tf.random_uniform([self.vocab_size, self.L1_N], -l1_par_range, l1_par_range))
            bias1 = tf.Variable(tf.random_uniform([self.L1_N], -l1_par_range, l1_par_range))

            #query_l1 = tf.sparse_tensor_dense_matmul(self.query_batch, weight1) + bias1
            query_l1 = tf.matmul(self.query_batch, weight1) + bias1
            #doc_l1 = tf.sparse_tensor_dense_matmul(self.doc_batch, weight1) + bias1
            doc_l1 = tf.matmul(self.doc_batch, weight1) + bias1

            query_l1_out = tf.nn.relu(query_l1)
            doc_l1_out = tf.nn.relu(doc_l1)

        with tf.name_scope('L2'):
            self.L2_N = 100
            l2_par_range = np.sqrt(6.0 / (self.L1_N + self.L2_N))
            weight2 = tf.Variable(tf.random_uniform([self.L1_N, self.L2_N], -l2_par_range, l2_par_range))
            bias2 = tf.Variable(tf.random_uniform([self.L2_N], -l2_par_range, l2_par_range))

            query_l2 = tf.matmul(query_l1_out, weight2) + bias2
            doc_l2 = tf.matmul(doc_l1_out, weight2) + bias2
            self.query_y = tf.nn.relu(query_l2)
            self.doc_y = tf.nn.relu(doc_l2)
        """
        """
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
    with tf.Session() as sess:
       sess.run(tf.global_variables_initializer())
       for i in range(50):
           """
           query_bc = np.zeros([batch_size, vocab_size]) #[None, self.sequence_length]
           #query_bc[query_bc >= 0.5] = 1
           #query_bc[query_bc <0.5] = 0
           #query_bc = query_bc.astype(np.float32)

           doc_bc = np.random.rand(batch_size, vocab_size) #[None, self.sequence_length]
           doc_bc[doc_bc >= 0.5] = 1
           doc_bc[doc_bc  <0.5] = 0
           doc_bc = doc_bc.astype(np.float32)

           label_bc = np.random.rand(batch_size, 1) #[None, self.sequence_length]
           label_bc[label_bc >= 0.5] = 1
           label_bc[label_bc < 0.5] = 0
           label_bc = label_bc.astype(np.float32)

           #print (doc_bc, type(doc_bc))
           print (query_bc)
           #print (label_bc)

           sequence_length = 12
           #input_x=np.zeros((batch_size, sequence_length)) #[None, self.sequence_length]
           #input_y=input_y=np.array([1,0,1,1,1,2,1,1]) #np.zeros((batch_size),dtype=np.int32) #[None, self.sequence_length]
           #print (input_x, input_y)
            
           """

           input_x=np.zeros((batch_size, vocab_size)) #[None, self.sequence_length]
           feed_dict={dssm.input_x: input_x } 
           loss = sess.run([dssm.loss], feed_dict) 

           #input_y=input_y=np.array([1,0,1,1,1,2,1,1]) #np.zeros((batch_size),dtype=np.int32) #[None, self.sequence_length]
           #loss, query_y, doc_y = sess.run([dssm.loss, dssm.query_y, dssm.doc_y],
                                                   #feed_dict={dssm.query_batch:query_bc, dssm.doc_batch: doc_bc, dssm.label_batch: label_bc} ) 
           print(i, "loss:", loss,"-------------------------------------------------------")

test()
