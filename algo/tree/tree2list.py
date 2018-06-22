import collections
import sys

s = "aa"
print collections.Counter(s)


class Node(object):
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None

def create():
    a = Node("a")
    b = Node("b")
    c = Node("c")
    d = Node("d")
    e = Node("e")
    f = Node("f")
    g = Node("g")
    a.left = b
    a.right = c
    b.left = d
    b.right = e 
    e.left = g
    c.right = f
    return a

def order(root):
    if(root):
        print root.val
        order(root.left)
        order(root.right)

root = create()
order(root)

print "-------"
def tree2list(root):
    if(root is not None):
        head, tail = root, root
        (lhead, ltail) = tree2list(root.left)
        (rhead, rtail) = tree2list(root.right)
        if (lhead):
            ltail.right = root
            root.left = ltail
            head = lhead 
        if (rhead):
            root.right = rhead
            rhead.left = root
            tail = rtail
        return head, tail 
    else:
        return None, None

head, tail = tree2list(root)
print "*****list*******head"
while(head):
    print head.val
    head = head.right
print "*****list*******tail"
while(tail):
    print tail.val
    tail = tail.left
