#!/usr/bin/python3
# -*- coding: utf-8 -*-
# <nbformat>3.0</nbformat>


import matplotlib.pyplot as plt
import numpy as np
import sys

def torify (T):
    n=int(len(T[0])/3)
    f21=[]
    f31=[]
    for data in T:
        data = data.reshape(3,n)
        P=data[0,1:]-data[0,:-1]
        d21=data[1,:-1]-data[0,:-1]
        d31=data[2,:-1]-data[0,:-1]
        f21.append(d21/P)
        f31.append(d31/P)
    return f21,f31


T=np.loadtxt(sys.argv[1])


f21,f31=torify(T)


for (f,g) in zip(f21, f31):
    plt.plot(f,g,color=(f[-1]%1,g[-1]%1,(2*f[-1]+g[-1])%1))
plt.show()


