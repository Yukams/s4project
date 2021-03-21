#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Oct 24 16:14:40 2020

@author: vincent
"""
def masse_monetaire(masse_initiale,reward,nb_blocks):
    masse_courante = masse_initiale*10**8 # en satoshi
    nb_tours = 0
    reward = reward*10**8
    while reward > 0: #satoBnb
        masse_courante +=nb_blocks*reward
        reward//=2
        nb_tours +=1
        #print(masse_courante,reward,nb_tours)
    return (masse_courante,nb_tours)


# (m,t)= masse_monetaire(0,20,500) # Bonobo
# print("Masse monétaire = ",m)
# print("Nombre de tours = ",t)

(m,t)= masse_monetaire(0,50,20) # Bonobo
print("Masse monétaire Bnb = ",m/10**8)
print("Nombre de tours = ",t)


(m,t)= masse_monetaire(0,50,210000) # paramètres du Bitcoin
print("Masse monétaire BTC = ",m/10**8)
print("Nombre de tours = ",t)
