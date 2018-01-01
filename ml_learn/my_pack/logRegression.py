from numpy import *  
import time  
  
# calculate the sigmoid function  
def sigmoid(inX):  
    return 1.0 / (1 + exp(-inX))  
  
# train a logistic regression model using some optional optimize algorithm  
# input: train_x is a mat datatype, each row stands for one sample  
#        train_y is mat datatype too, each row is the corresponding label  
#        opts is optimize option include step and maximum number of iterations  
def trainLogRegres(train_x, train_y, opts):  
    # calculate training time  
    startTime = time.time()  
  
    numSamples, numFeatures = shape(train_x)  
    alpha = opts['alpha']; maxIter = opts['maxIter']  
    weights = ones((numFeatures, 1))  
    print "weight:", weights, type(weights), shape(weights)
    print "train_x", train_x, type(train_x), shape(train_x)
    print "train_y", train_y, type(train_y)
  
    # optimize through gradient descent algorilthm  
    for k in range(maxIter):  
        if opts['optimizeType'] == 'gradDescent': # gradient descent algorilthm  
            output = sigmoid(train_x * weights)  
            error = train_y - output  
            print "error:", error, type(error), shape(error)
            print "trans_x.trans:", train_x.transpose(), type(train_x.transpose()), shape(train_x.transpose())
            weights = weights + alpha * train_x.transpose() * error  
        elif opts['optimizeType'] == 'stocGradDescent': # stochastic gradient descent  
            for i in range(numSamples):  
                output = sigmoid(train_x[i, :] * weights)  
                error = train_y[i, 0] - output  
                weights = weights + alpha * train_x[i, :].transpose() * error  
        elif opts['optimizeType'] == 'smoothStocGradDescent': # smooth stochastic gradient descent  
            # randomly select samples to optimize for reducing cycle fluctuations   
            dataIndex = range(numSamples)  
            for i in range(numSamples):  
                alpha = 4.0 / (1.0 + k + i) + 0.01  
                randIndex = int(random.uniform(0, len(dataIndex)))  
                output = sigmoid(train_x[randIndex, :] * weights)  
                error = train_y[randIndex, 0] - output  
                weights = weights + alpha * train_x[randIndex, :].transpose() * error  
                del(dataIndex[randIndex]) # during one interation, delete the optimized sample  
        else:  
            raise NameError('Not support optimize method type!')  
    print 'Congratulations, training complete! Took %fs!' % (time.time() - startTime)  
    return weights  
  
# test your trained Logistic Regression model given test set  
def testLogRegres(weights, test_x, test_y):  
    numSamples, numFeatures = shape(test_x)  
    matchCount = 0  
    for i in xrange(numSamples):  
        predict = sigmoid(test_x[i, :] * weights)[0, 0] > 0.5  
        if predict == bool(test_y[i, 0]):  
            matchCount += 1  
    accuracy = float(matchCount) / numSamples  
    return accuracy  
