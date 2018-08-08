import sys
from logRegression import *
from numpy import *  
import time  
  
def loadData(path):  
    train_x = []  
    train_y = []  
    fileIn = open(path)  
    for line in fileIn.readlines():  
        lineArr = line.strip().split()  
        train_x.append([1.0, float(lineArr[0]), float(lineArr[1])])  
        train_y.append(float(lineArr[2]))  
    return mat(train_x), mat(train_y).transpose()  
  
## step 1: load data  
print "step 1: load data..."  
train_x, train_y = loadData(sys.argv[1])  
test_x = train_x; test_y = train_y  
  
## step 2: training...  
print "step 2: training..."  
opts = {'alpha': 0.01, 'maxIter': 20, 'optimizeType': 'gradDescent'}  
optimalWeights = trainLogRegres(train_x, train_y, opts)  
  
## step 3: testing  
print "step 3: testing..."  
accuracy = testLogRegres(optimalWeights, test_x, test_y)  
print 'The classify accuracy is: %.3f%%' % (accuracy * 100)  
