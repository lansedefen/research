#!coding=utf-8
import pandas as pd  
import numpy as np  
import xgboost as xgb 
from xgboost.sklearn import XGBClassifier  
from sklearn.model_selection import GridSearchCV, cross_val_score  
from sklearn import  metrics  
from sklearn import metrics
import datetime
import lightgbm as lgb
from sklearn.metrics import mean_squared_error

import sys
reload(sys)
sys.setdefaultencoding('utf-8')

def dataParse(file_path):
    data, label = [], []
    obj = open(file_path)
    count = 0
    for line in obj:
        count +=1
	if count % 100000 == 1:
		print "count is:", count
		sys.stdout.flush()
        ele = line.strip().split("\t")
        text_feature = [ float(e) for e in ele[3].strip().split(",")]
        user_feature = [float(e) for e in  ele[4].strip().split(",")]
        source_feature = [float(e) for e in ele[5].strip().split(",")]
        data.append( text_feature + user_feature + source_feature )
        if float(ele[0]) > 0.35:
            label.append(1)
        else:
            label.append(0)
    return np.array(data), np.array(label) 

def importData(train_file, test_file):
    train_x, train_y = dataParse(train_file)
    test_x, test_y = dataParse(test_file)
    print len(train_x), len(train_y)
    print len(test_x), len(test_y)
    print np.bincount(train_y)
    print np.bincount(test_y)
    return train_x, train_y, test_x, test_y 

def metricAll(clf, train_x, train_y, test_x, test_y, m_thresh = 0.3):
    def _metricSet(test_y, ypred, thresh = 0.5):
        y_pred = (ypred >= thresh) * 1
        print 'AUC: %.4f' % metrics.roc_auc_score(test_y, ypred)
        print 'F1-score: %.4f' %metrics.f1_score(test_y, y_pred)
        print 'Recall: %.4f' % metrics.recall_score(test_y, y_pred)
        print 'Precesion: %.4f' %metrics.precision_score(test_y, y_pred)

    clf.fit(train_x, train_y, verbose = True, eval_metric = 'auc')  
    train_predprob = clf.predict(train_x)
    test_predprob = clf.predict(test_x)
    print train_predprob
    print "train, thresh:", m_thresh 
    _metricSet(train_y, train_predprob, m_thresh)
    print "\ntest, thresh:", m_thresh 
    _metricSet(test_y, test_predprob, m_thresh)
    sys.stdout.flush()

def getEstimators(clf, train_x, train_y):
    # n_estimators
    xgb_param = clf.get_xgb_params()
    xgtrain = xgb.DMatrix(train_x, label = train_y)  
    stopping_rounds = 50
    cvresult = xgb.cv(xgb_param, xgtrain, num_boost_round = clf.get_params()['n_estimators'], nfold = 5,  
                        metrics='auc', early_stopping_rounds = stopping_rounds)
    print "cvresult:\n", cvresult
    sys.stdout.flush()
    clf.set_params(n_estimators = cvresult.shape[0])  
    metricAll(clf, train_x, train_y, test_x, test_y, m_thresh = 0.3)
    return clf 

def getBestParam(flag, clf, train_x, train_y, param_test): 
    def _searchParam(clf, param_test, train_x, train_y):
        gsearch = GridSearchCV( n_jobs = 24, estimator = clf, param_grid = param_test, scoring='roc_auc', iid=False, cv=5)
        gsearch.fit(train_x, train_y)
        for ele in gsearch.grid_scores_:
            print ele
        print "cv best_para:", gsearch.best_params_
        print "cv best_score:", gsearch.best_score_  
    	sys.stdout.flush()
        return gsearch
    gsearch = _searchParam(clf, param_test, train_x, train_y)

    """
    if flag == "n_estimators":
        clf.set_params(n_estimators = gsearch.best_params_["n_estimators"])
    if flag == "scale_pos_weight":
        clf.set_params(scale_pos_weight = gsearch.best_params_["scale_pos_weight"])
    elif flag == "max_depth":
        clf.set_params(max_depth = gsearch.best_params_["max_depth"])
        clf.set_params(min_child_weight = gsearch.best_params_["min_child_weight"])
    elif flag == "gamma":
        clf.set_params(gamma = gsearch.best_params_["gamma"])
    elif flag == "subsample":
        clf.set_params(subsample = gsearch.best_params_["subsample"])
        clf.set_params(colsample_bytree = gsearch.best_params_["colsample_bytree"])
    elif flag == "reg_alpha":
        clf.set_params(reg_alpha = gsearch.best_params_["reg_alpha"])
    """
    #sys.stdout.flush()
    #metricAll(clf, train_x, train_y, test_x, test_y, m_thresh = 0.3)
    return clf

def saveModel(clf, train_x, train_y, test_x, test_y):
    # train and save model
    param = {
            "eta":0.1,
            'max_depth':3, 
            "min_child_weight":3,
            'eta':1, 
            'silent':1, 
            "subsample": 0.8,
            "reg_alpha":0.005,
            "gamma":0.05,
            "colsample_bytree": 0.8,
            'objective':'binary:logistic',
            "scale_pos_weight": 1, 
            "seed": 27,
            "eval_metric":"auc"
            }
    xgb_param =  clf.get_xgb_params()
    tree_num = xgb_param["n_estimators"]

    dtrain = xgb.DMatrix(train_x, label = train_y)
    dtest = xgb.DMatrix(test_x, label = test_y)
    watchlist = [(dtest, 'eval'), (dtrain, 'train')]
    bst = xgb.train(xgb_param, dtrain, tree_num, watchlist)
    #bst.save_model('0001.model')
    bst.dump_model('dump_raw_config')

"""
# train
gbm = lgb.LGBMRegressor(objective='regression',
                        num_leaves=31,
                        learning_rate=0.05,
                        n_estimators=20)

gbm.fit(X_train, y_train,
        eval_set=[(X_test, y_test)],
        eval_metric='l1',
        early_stopping_rounds=5)

print('Start predicting...')
# predict
y_pred = gbm.predict(X_test, num_iteration=gbm.best_iteration_)
# eval
print('The rmse of prediction is:', mean_squared_error(y_test, y_pred) ** 0.5)

# feature importances
print('Feature importances:', list(gbm.feature_importances_))

estimator = lgb.LGBMRegressor(num_leaves=31)
param_grid = {
    'learning_rate': [0.01, 0.1, 1],
    'n_estimators': [20, 40]
}
gbm = GridSearchCV(estimator, param_grid, n_jobs = 24)
gbm.fit(X_train, y_train)
#print('Best parameters found by grid search are:', gbm.best_params_)

"""

def initTree():
    return lgb.LGBMRegressor(objective='regression', num_leaves=31, learning_rate=0.05, n_estimators=20)

if __name__ == "__main__":
    time_stamp = datetime.datetime.now()
    print "start time_stamp" + time_stamp.strftime('%Y.%m.%d-%H:%M:%S')

    # 0 load data
    train_x, train_y, test_x, test_y = importData(sys.argv[1], sys.argv[2])
    time_stamp = datetime.datetime.now()
    print "0 time_stamp" + time_stamp.strftime('%Y.%m.%d-%H:%M:%S')
    sys.stdout.flush()

    # 1 init tree
    clf = initTree()
    #print "\ninit tree para:\n", clf.get_xgb_params()
    metricAll(clf, train_x, train_y, test_x, test_y, m_thresh = 0.3)
    print "1 time_stamp" + time_stamp.strftime('%Y.%m.%d-%H:%M:%S')
    sys.stdout.flush()
	
    # 2 best tree num
    param_test = {
    	'n_estimators': [20, 40]
    }
    clf = getBestParam("n_estimators", clf, train_x, train_y, param_test)
    #print "\nafter set n_estimators:\n", clf.get_xgb_params()
    print "2 time_stamp" + time_stamp.strftime('%Y.%m.%d-%H:%M:%S')
    sys.stdout.flush()
	
    """
    # 3 best scale_pos_wegith
    param_test = {
        'scale_pos_weight': [1.2, 1.4, 1.6, 1.8, 2.0 ,2.2]
    }
    clf = getBestParam("scale_pos_weight", clf, train_x, train_y, param_test)
    print "\nafter set scale_pos_wegith:\n", clf.get_xgb_params()
    print "3 time_stamp" + time_stamp.strftime('%Y.%m.%d-%H:%M:%S')
    sys.stdout.flush()
	
    # 4 best max_depth, min_child_weight
    param_test = {
        'max_depth':range(3, 10, 2),
        'min_child_weight':range(1, 6, 2)
    }
    clf = getBestParam("max_depth", clf, train_x, train_y, param_test)
    print "\nafter set max_depth:\n", clf.get_xgb_params()
    print "4 time_stamp" + time_stamp.strftime('%Y.%m.%d-%H:%M:%S')
    sys.stdout.flush()
	
    # 5 best gamma
    param_test = {
        'gamma':[i/10.0 for i in range(0,5)]
    }
    clf = getBestParam("gamma", clf, train_x, train_y, param_test)
    print "\nafter set gamma:\n", clf.get_xgb_params()
    print "5 time_stamp" + time_stamp.strftime('%Y.%m.%d-%H:%M:%S')
    sys.stdout.flush()
	
    # 6 best subsample, colsample_bytree
    param_test = {
        'subsample':[i/10.0 for i in range(6,10)],
        'colsample_bytree':[i/10.0 for i in range(6,10)]
    }
    clf = getBestParam("subsample", clf, train_x, train_y, param_test)
    print "\nafter set subsample:\n", clf.get_xgb_params()
    print "6 time_stamp" + time_stamp.strftime('%Y.%m.%d-%H:%M:%S')
    sys.stdout.flush()
	
    # 7 best reg_alpha
    param_test = {
        'reg_alpha':[0, 0.001, 0.005, 0.01, 0.05]
    }
    clf = getBestParam("reg_alpha", clf, train_x, train_y, param_test)
    print "\nafter set reg_alpha:\n", clf.get_xgb_params()
    print "7 time_stamp" + time_stamp.strftime('%Y.%m.%d-%H:%M:%S')
    sys.stdout.flush()
    """	
    # 8 save model
    #saveModel(clf, train_x, train_y, test_x, test_y)
