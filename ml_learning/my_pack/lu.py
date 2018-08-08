# coding:utf8
import numpy as np

def lu(mat):
    r,c=np.shape(mat)
    s=min(r,c)
    for k in range(s):
        x=1.0/mat[k][k]  # 将后续除法变成乘法
        for i in range(k+1,r):
            mat[i][k]=mat[i][k]*x  # L[1:][0]*U[0][0]=A[1:][0]；A[0][:]=mat[0][:]
        for i in range(k+1,r):
            for j in range(k+1,c):
                # U[1][2]*L[1][1]=A[1][2]-U[0][2]*L[1][0]；L[1][1]=1
                # L[2][1]*U[1][1]=A[2][1]-U[0][1]*L[2][0]；下一个k时mat[i][j]/mat[k][k](i>j)
                mat[i][j]=mat[i][j]-mat[k][j]*mat[i][k]
    return mat,c

def solve(A,b):
    mat,n=lu(A)  # LU合并
    print mat  # [[16, 4, 8], [0.25, 4.0, -6.0], [0.5, -1.5, 9.0]]
    Z= np.zeros(n)  # L*Z=b U*X=Z
    X= np.zeros(n)
    Z[0]=b[0]
    for i in range(1,n):
        sumup=0
        for tmp in range(0,i):
            sumup+=mat[i][tmp]*Z[tmp]
        Z[i]=(b[i]-sumup)
    X[n-1]=Z[n-1]/mat[n-1][n-1]
    for i in range(n-2,-1,-1):
        sumup=0
        for tmp in range(i+1,n):
            sumup+=mat[i][tmp]*X[tmp]
        X[i]=(Z[i]-sumup)/mat[i][i]
    return X

A=[[16,4,8],[4,5,-4],[8,-4,22]]
y=[-4,3,10]
print "The result of the fomula is:"+str(solve(A,y))  # [-2.25  4.    2.  ]
