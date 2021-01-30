# -*- coding: utf-8 -*-
"""
Created on Fri Jan 29 11:41:35 2021

@author: pawel
"""
import numpy as np
import matplotlib.pyplot as plt
import csv


dane = [[], [], [], [], [], []]


file = 'results.txt'


with open(file, 'r') as csv_file:
    csv_reader = csv.reader(csv_file)

    for line in csv_reader:
        for i in range(6):
            dane[i].append(line[i])

XX = np.array(dane[0])
XX = XX.astype('float64')
 
CX = np.array(dane[1])
CX = CX.astype('float64') 

X = np.array(dane[2])
X = X.astype('float64') 

dot = np.array(dane[3])
dot = dot.astype('float64') 

carrier = np.array(dane[4])
carrier = carrier.astype('float64') 

t = np.array(dane[5])
t = t.astype('float64') 

a = 50000

fig = plt.figure(dpi=500)
ax = fig.add_subplot()
ax.plot(t[:a], XX[:a], "g",label = "XX")
ax.plot(t[:a], CX[:a], "r",label = "CX")
ax.plot(t[:a], X[:a], "b",label = "X")
ax.plot(t[:a], dot[:a], "y",label = "dot")
ax.plot(t[:a], carrier[:a], "black",label = "carrier")
ax.set_xlabel('T [ns]')
ax.set_ylabel('Prawdopodobieństwo obsadzenia danego stanu')
plt.legend(["XX","CX","X",'dot','carrier'])
dane = [[], [], [], [], [], []]


file = 'results_1.txt'


with open(file, 'r') as csv_file:
    csv_reader = csv.reader(csv_file)

    for line in csv_reader:
        for i in range(6):
            dane[i].append(float(line[i]))

XX = np.array(dane[0])
CX = np.array(dane[1])
X = np.array(dane[2])
dot = np.array(dane[3])
carrier = np.array(dane[4])
t = np.array(dane[5])
 

a = 15000
fig = plt.figure(dpi=500)
ax = fig.add_subplot()
ax.plot(t[:a], XX[:a], "g",label = "XX")
ax.plot(t[:a], CX[:a], "r",label = "CX")
ax.plot(t[:a], X[:a], "b",label = "X")
ax.plot(t[:a], dot[:a], "y",label = "dot")
ax.plot(t[:a], carrier[:a], "black",label = "carrier")
ax.set_xlabel('T [ns]')
ax.set_ylabel('Prawdopodobieństwo obsadzenia danego stanu')
plt.legend(["XX","CX","X",'dot','carrier'])


dane = [[], [], [], [], [], []]


file = 'results3.txt'


with open(file, 'r') as csv_file:
    csv_reader = csv.reader(csv_file)

    for line in csv_reader:
        for i in range(4):
            dane[i].append(float(line[i]))

XX = np.array(dane[0])
XX = XX.astype('float64')
 
CX = np.array(dane[1])
CX = CX.astype('float64') 

X = np.array(dane[2])
X = X.astype('float64') 

k = np.array(dane[3])
 


a = 200000

fig = plt.figure(dpi=500)
ax = fig.add_subplot()
ax.plot(np.log(k), np.log(XX), "g", label = "XX")
ax.plot(np.log(k), np.log(CX), "r", label = "CX")
ax.plot(np.log(k), np.log(X) , "b", label = "X")
ax.set_xlabel('ln(K)')
ax.set_ylabel('Wartość całki dla danego k w skali ln')
plt.legend(["XX","CX","X"])