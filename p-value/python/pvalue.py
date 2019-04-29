# -*- coding:UTF-8 -*-

infile=open("data_dm.txt",'r')
list=[]
for line in infile:
    lline=line.strip().split('\t')
    term=[]
    for elem in lline:
        term.append(elem)
    list.append(term)


def C(n, m):
    result = 1
    a = (int(n)-int(m))
    b=int(m)
    if a > b:
        t=a
        a=b
        b=t
    i = 1
    while i<= a:
        result *= ((b + i) / i)
        i+=1
    return result


def pvalue(n, x,p):
    pvalue=0
    j = int(x)
    while j <= int(n):
        t=C(n, j)
        pvalue += t*pow(float(p), int(j))*pow(1 - float(p), int(n) -int(j))
        j+=1
    return pvalue


#print(pvalue(66,16,0.236861))

resultlist=[]
for term in list:
    p=pvalue(term[1],term[2],term[3])
    list=[]
    list.append(term[0])
    list.append(p)
    resultlist.append(list)

for result in resultlist:
    if result[1]<0.01:
        print("%s\t%s" % (result[0],result[1]))