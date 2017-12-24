import sys

input = [1,2,3]

def dfs(input, length, res):
    if length == 0:
        print "out:", "".join([str(xx) for xx in res])
        return 

    for ele in input:
        res.append(ele)
        dfs(input, length -1, res)
        res.pop()

res = []
dfs(input, 4, res)
