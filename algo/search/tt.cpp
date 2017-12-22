#include <iostream>
#include <string>
#include<queue>

using namespace std;

class Student
{
    public:
        int key;
        string major;
        //other data
        Student(int k=int(),string s="") : key(k), major(s){}
        //重载赋值运算符 
        void operator=(const Student& rhs)
        {
            if(this != &rhs)
            {
                key = rhs.key;
                major = rhs.major;
            }
        }   
};

//重载<<,便于输出自定义类对象 
ostream& operator<<(ostream &out, const Student& s)
{
    out<<"("<<s.key<<","<<s.major<<")";
}

typedef Student ElementType;
typedef int KeyType;

typedef struct BSTNode
{
    ElementType data;
    struct BSTNode* lchild;
    struct BSTNode* rchild;
}BSTNode, *BST;

//非递归查找 
bool searchBST(BST t, KeyType key, BSTNode* f, BSTNode* &p)
{
    while(t && key != t->data.key)
    {
        f = t;
        if(key < t->data.key)
        {
            t = t->lchild;
        }
        else
        {
            t = t->rchild;
        }           
    }
    if(t)//查找成功 
    {
        p = t;
        return true;
    }
    else
    {
        p = f;
        return false;
    }
}

//插入给定元素 
void insertBST(BST& t,ElementType elem)
{
    BSTNode * p = NULL;

    if(!searchBST(t, elem.key, NULL, p))//查找失败，不含该关键字，可以插入 
    {
        BSTNode * s = new BSTNode;
        s->data = elem;//可能需要重载= 
        s->lchild = NULL;
        s->rchild = NULL;
        
        if(p == NULL)//查找树为空 
        {
            t = s;//置s为根结点 
        }
        else if(elem.key < p->data.key)
        {
            p->lchild = s;  //*s为p左结点 
        }
        else
        {
            p->rchild = s;  //*s为p右结点 
        }
    }
}

//从二叉查找树中删除指针p所指向的结点 ,p非空,直接删除p的方式 
void removeNode3(BSTNode *& p)
{
    BSTNode *q = NULL;
    cout << "p:" << p->data << endl << p << endl;
    if(!p->rchild)//*p的右子树为空 
    {
        cout << "r is empty" << endl;
        q = p;
        p = p->lchild;
        cout << "new p" << p << endl;
        delete q;
    }
    else if(!p->lchild)//*p的左子树为空 
    {
        q = p;
        p = p->rchild;
        delete q;
    }
    else//左右子树均不空 
    {
        BSTNode *s = NULL;
        q = p;
        s = p->lchild;      //左子树根结点
        while(s->rchild)    //寻找结点*p的中序前驱结点，                    
        {                   //也就是以*s为根结点的子树中最右的结点 
            s = s->rchild;   
        }
        s->rchild = p->rchild;//*p的右子树接到*s的右子树上 
        p = p->lchild;          //*p的左子树接到父节点上 
        delete q;           //删除结点*q 
    }
}

//删除关键字为key的元素结点 -递归 
void removeBST_recursion(BST& t, KeyType key)
{
    if(t)
    {
        if(key < t->data.key)
        {
            removeBST_recursion(t->lchild,key);
        }
        else if(t->data.key < key)
        {
            removeBST_recursion(t->rchild,key);
        }
        else//找到关键字为key的元素 
        {
            removeNode3(t);
        }
    }
}

void printTree(const BST& t) {
     queue<BST> tmp;
     tmp.push(t);
     int first=1;
     int second = 0;
     while(!tmp.empty()) {
        BST top_node = tmp.front();
        tmp.pop();
        first -=1;
        cout << top_node->data << " "<< top_node;

        if(top_node->lchild) {
           tmp.push(top_node->lchild);
           second +=1;
        }   

        if(top_node->rchild) {
           tmp.push(top_node->rchild);
           second +=1;
        }   

        if(first == 0) {
          //cout << "----------" << first << "," << second << endl;
          cout << endl;
          first = second;
          second = 0;
        }   
     }   
}

int main(int argc, char *argv[])
{
    const int N = 10;
    BST root = NULL;

    Student s(5,"cs");//关键字为1-10 
    insertBST(root,s);
    for(int i=8; i>=6; i--)
    {
        Student s(i,"cs");//关键字为1-10 
        insertBST(root,s);
    }
    for(int i=1; i<=2; i++)
    {
        Student s(i,"cs");//关键字为1-10 
        insertBST(root,s);
    }
    
    cout<<"after insert: "<<endl;
    printTree(root);
    cout<<endl<<endl;
    cout << "root:" << root << endl << "root->right" << root->rchild << endl;;
    
    removeBST_recursion(root,8);//删除关键字为1-3-5-7-9的结点 
    cout<<"after delete: "<<endl;
    cout << "root:" << root << endl << "root->right" << root->rchild << endl;;
    printTree(root);
    cout<<endl<<endl;
    return -1;    
}
