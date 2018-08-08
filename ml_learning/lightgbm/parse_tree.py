#!coding=utf8

import sys
import json
import Queue 

class Node():
	def __init__(self, left, right, split_feature, threshold, decision_type, is_leaf, index, leaf_value):
		self.left = left
		self.right = right

		self.split_feature = split_feature
		self.threshold= threshold
		self.decision_type = decision_type

		self.is_leaf = is_leaf
		self.leaf_value = leaf_value

		self.index = index

def createTree(tree_json):
	if tree_json.has_key("threshold"):
		threshold= tree_json["threshold"]
		decision_type = tree_json["decision_type"]
		split_feature = tree_json["split_feature"]
		left_child = createTree(tree_json["left_child"])
		right_child = createTree(tree_json["right_child"])
		split_index = tree_json["split_index"]
		index = str(split_index)
		return Node(left_child, right_child, split_feature, threshold, decision_type, False, index, None) 
	else:
		leaf_value = tree_json["leaf_value"]		
		leaf_index = tree_json["leaf_index"]
		index = "9999" + str(leaf_index)
		return Node(None, None, None, None, None, True, index, leaf_value) 

def printTreeByLay(root):
	q = Queue.Queue() 
	q.put(root)
	count = 0
	level = 1
	while(not q.empty()):
		cur = q.get()
		level -=1
		if cur.is_leaf == False:
			print "\t"+str(cur.index) + ":[f" + str(cur.split_feature) + cur.decision_type  +  str( cur.threshold) +  "]", "yes="+ str(cur.left.index) + ",no=" + str(cur.right.index) + ",missing=" + str(cur.left.index)
		else:
			print "\t"+str(cur.index) + ":leaf=" + str(cur.leaf_value)

		if cur.left is not None:
			q.put(cur.left)
			count +=1
		if cur.right is not None:
			q.put(cur.right)
			count +=1

		if level == 0:
			#print ""
			level = count
			count = 0


obj = open(sys.argv[1], 'r')
content = json.load(obj)

for i, k in enumerate(content["tree_info"]):
	first_tree = k["tree_structure"]
	root = createTree(first_tree)
	#print "booster[" + str(i) + "]:"
	print "booster[" + str(i) + "]:", "shrinkage=" + str(k["shrinkage"])
	printTreeByLay(root)

#loadModel(sys.argv[1])
