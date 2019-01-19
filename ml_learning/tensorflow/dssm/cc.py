import os
import six.moves.urllib.request as request
import tensorflow as tf

PATH = "./tf_dataset_and_estimator_apis"
# Fetch and store Training and Test dataset files
PATH_DATASET = PATH + os.sep + "dataset"
FILE_TRAIN = PATH_DATASET + os.sep + "iris_training.csv"
FILE_TEST = PATH_DATASET + os.sep + "iris_test.csv"

training_filenames = [FILE_TRAIN] 
validation_filenames = [FILE_TEST] 
print training_filenames
num_epochs = 1
num_class = 3

def decode_line(line):
    # Decode the csv_line to tensor.
    record_defaults = [[1.0] for col in range(785)]
    items = tf.decode_csv(line, record_defaults)
    features = items[1:785]
    label = items[0]
    print features

    features = tf.cast(features, tf.float32)
    features = tf.reshape(features,[28,28])
    label = tf.cast(label, tf.int64)
    label = tf.one_hot(label,num_class)
    print features, label
    return features,label

def create_dataset(filename, batch_size= 15, is_shuffle=False, n_repeats=1):
    dataset = tf.data.TextLineDataset(filename).skip(1)
    if n_repeats > 0:
        dataset = dataset.repeat(n_repeats)         # for train
    # dataset = dataset.map(decode_line).map(normalize)  
    dataset = dataset.map(decode_line)    
    # decode and normalize
    if is_shuffle:
        dataset = dataset.shuffle(10000)            # shuffle
    dataset = dataset.batch(batch_size)
    print dataset
    return dataset

# Create different datasets
training_dataset = create_dataset(training_filenames, batch_size=32, \
                                  is_shuffle=True, n_repeats=num_epochs) # train_filename
validation_dataset = create_dataset(validation_filenames, batch_size=32, \
                                  is_shuffle=True, n_repeats=num_epochs) # val_filename

handle = tf.placeholder(tf.string, shape=[])
iterator = tf.data.Iterator.from_string_handle(
    handle, training_dataset.output_types, training_dataset.output_shapes)
next_element = iterator.get_next()
training_iterator = training_dataset.make_one_shot_iterator()
validation_iterator = validation_dataset.make_initializable_iterator()

with tf.Session() as sess:
    training_handle = sess.run(training_iterator.string_handle())
    validation_handle = sess.run(validation_iterator.string_handle())
    while True:
      # iteration.
      #for _ in range(20):
      #try:
      if 1:
        res = sess.run(next_element , feed_dict={handle: training_handle})
        print "res:", res[0]
      #except:
      #  break

      # Run one pass over the validation dataset.
      #sess.run(validation_iterator.initializer)
      #for _ in range(50):
      #  sess.run(next_element, feed_dict={handle: validation_handle})
