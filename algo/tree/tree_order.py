import sys

class Node(object):
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None
        self.flag = None 
    
def postOrder(root):
    if (root):
        postOrder(root.left)
        postOrder(root.right)
        print root.val

def postOrderFor(root):
    s = []
    p = root 
    while ( (len(s) > 0) or (p is not None)):
        if ( p is not None ): 
            s.append(p)
            p = p.left
        else:
            p = s[-1]
            s.pop()
            if ( p.flag is not None ):
                for ele in s:
                    print "s:", ele.val,
                print ""
                print p.val
                p = None
                continue
            else:
                p.flag = "visit"
                s.append(p)
                p = p.right 

def build():
    A, B, C, D, E, F, G = Node("A"), Node("B"), Node("C"), Node("D"), Node("E"), Node("F"), Node("G")
    A.left = B
    A.right = C
    B.left = D
    B.right = E
    E.left = G 
    C.right = F
    return A

root = build()
#postOrder(root)
postOrderFor(root)
