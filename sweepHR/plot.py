#! /usr/bin/env python3

import matplotlib.pyplot as plt
import numpy as np
import itertools
import sys


def torify(T, tol=0.15):
    n=len(T[0])//3
    X1=T[:,:n]
    X2=T[:,n:2*n]
    X3=T[:,2*n:3*n]
    P=X1[:,1:]-X1[:,:-1]
    f21=(X2[:,:-1]-X1[:,:-1])/P
    f31=(X3[:,:-1]-X1[:,:-1])/P
    
    # We compute the possible ends up to 2 decimal places
    ends = set( zip(np.round(f21[:,-1],2), np.round(f31[:,-1],2)) )
    
    # assign colors
    pallete = {}
    last_color = 0
    
    for newcolor in ends:
        is_it_new = True
        for c,t in itertools.product( pallete, np.array([[0,0],[0.5,0],[0,0.5],[0.5,0.5]]) ):
            if np.linalg.norm( (np.array(c)+t)%1 - (np.array(newcolor)+t)%1 ) < tol:
                pallete[newcolor] = pallete[c]
                is_it_new = False
        if is_it_new:
            pallete[newcolor] = last_color
            last_color += 1
        
    
    return f21,f31, list(map( lambda x: pallete[x]/(last_color-1), zip(np.round(f21[:,-1],2), np.round(f31[:,-1],2)) ))
    

def savefig(fich):
	T = np.loadtxt(fich)
	f21,f31,colors=torify(T)
	
	for (f,g,c) in zip(f21, f31,colors):
	    plt.plot(f,g,color=plt.cm.jet(c))
	plt.savefig(fich + '.png')
	plt.close()

    
if __name__ == "__main__":
    for fich in sys.argv[1:]:
    	print('Start with ' + fich, end=' ')
    	savefig(fich)
    	print('Finished')
    
    
    
