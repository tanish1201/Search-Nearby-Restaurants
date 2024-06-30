class Node:
    def __init__(self,data):
        self.left=None
        self.right=None
        self.data=data
        self.another=None
class PointDatabase:
    def __init__(self,pointList):
        self.my_global_list=[]
        m=len(pointList)//2
        pointList1=pointList[:]
        pointList1.sort(key=lambda x:x[0])
        X=pointList1
        pointList.sort(key=lambda x:x[1])
        Y=pointList
        self.root=self.Tree(X,Y)
    def Tree(self,X,Y):
        if X is not None and Y is not None:
            m=len(X)//2
            if len(X)==0:
                root=Node([])
                root.another=[]
            elif len(X)>0:
                if len(X)==1:
                    root=Node(X[m])
                    root.another=Y
                elif  m+1<len(X):
                    X1=X[0:m]
                    X2=X[m+1:len(X)]
                    root=Node(X[m])
                    root.another=Y
                    Y1=[]
                    Y2=[]
                    for i in range (0,len(Y)):
                        if Y[i][0]<X[m][0]:
                            Y1.append(Y[i])
                        elif Y[i][0]>X[m][0]:
                            Y2.append(Y[i])
                    root.left=self.Tree(X1,Y1)
                    root.right=self.Tree(X2,Y2)
                else:
                    
                    X1=X[0:m]
                    root=Node(X[m])
                    root.another=Y
                    Y1=[]
                    Y2=[]
                    for i in range (0,len(Y)):
                        if Y[i][0]<X[m][0]:
                            Y1.append(Y[i])
                        elif Y[i][0]>X[m][0]:
                            Y2.append(Y[i])
                    root.left=self.Tree(X1,Y1)
                    root.right=None
            return root
    def Nearby(self,t,q,d):
        s=t.data
        if s is not None:
            if q[0]-d<=s[0]<=q[0]+d:
                if q[1]-d<=s[1]<=q[1]+d:
                    self.my_global_list.append(s)
                if t.left is not None:
                    if t.left.data[0]>=q[0]-d:
                        if q[1]-d<=t.left.data[1]<=q[1]+d:
                            self.my_global_list.append(t.left.data)
                        if t.left.right is not None:
                            self.Nearby2(t.left.right.another,q,d)
                        if t.left.left is not None:
                            self.Nearby(t.left.left,q,d)
                    elif t.left.right is not None :
                        self.Nearby(t.left.right,q,d)
                if t.right is not None:
                    if t.right.data[0]<=q[0]+d:
                        if q[1]-d<=t.right.data[1]<=q[1]+d:
                            self.my_global_list.append(t.right.data)
                        if t.right.left is not None :
                            self.Nearby2(t.right.left.another,q,d)
                        if t.right.right is not None:
                            self.Nearby(t.right.right,q,d)
                    
                    elif t.right.left is not None:
                        self.Nearby(t.right.left,q,d)
            elif (s[0]>(q[0]+d)):
                if t.left is not None:
                    self.Nearby(t.left,q,d)             
            elif s[0]<q[0]-d :
                if t.right is not None:
                    self.Nearby(t.right,q,d)
            return self.my_global_list
    def Nearby2(self,t,q,d):
        a1=self.low(t,q[1]-d)
        b1=self.high(t,q[1]+d)
        t1=t[a1:b1+1]
        for i in range (len(t1)):
            if q[0]-d<=t1[i][0]<=q[0]+d :
                self.my_global_list.append(t1[i])
        
        
    def low(self,list, x):
        l = 0
        h = len(list)-1
        while (l <= h):
            m = int((l + h)//2)
            if (list[m][1] >= x):
                h = m - 1
            else:
                l = m + 1
        return l
    def high(self,list, y):
        l = 0
        h = len(list)-1
        while (l <= h):
            m = int((l + h)//2)
            if (list[m][1] <= y):
                l = m + 1
            else:
                h = m - 1
        return h
    def searchNearby(self,q,d):
        self.my_global_list=[]
        if self.root.data!=[]:
            return self.Nearby(self.root,q,d)
        else:
            return []
