import sys

if len(sys.argv) > 1:
    if sys.argv[1] == '-h':
	    print('This file train model from start with dataset at arg1 dir')
	    exit()
	    
model_name="n" 	   

'''
if sys.argv[1] == 'tf':
	from tensorflow import keras
	model_name="test_tf_keras"
if sys.argv[1] == 'k':
	import keras
	model_name="test_keras"
	
'''
import keras

import numpy as np

import matplotlib.pyplot as plt
from collections import deque
import random

import tensorflow as tf
#from tensorflow import keras

from keras.models import Sequential
from keras.layers import Dense, Flatten
from keras.layers.convolutional import Conv2D
from keras.optimizers import RMSprop
from keras import layers
from keras.models import Model

import sys
from random import shuffle


import pickle



def FC_model():
   input_flattened = layers.Input((475,), name='test_in')
   #actions_input = layers.Input((A_t_size,), name='action_mask')	
   hidden1 = layers.Dense(512, activation='relu')(input_flattened)
   hidden2 = layers.Dense(512, activation='relu')(hidden1)
   #hidden3 = layers.Dense(512, activation='relu')(hidden2)
   #hidden4 = layers.Dense(600, activation='relu')(hidden3)
   output = layers.Dense(100,name="test_out")(hidden2)
   #filtered_output = layers.Multiply(name='QValue')([output, actions_input])
   #model = Model(inputs=[input_flattened, actions_input], outputs=filtered_output)
   model = Model(inputs=input_flattened, outputs=output)
   model.summary()
   keras.utils.plot_model(model, 'model.png')
   optimizer = RMSprop(lr=0.00025, rho=0.95, epsilon=0.01)#lr=0.00025
   model.compile(optimizer, loss='mse')#loss=huber_loss)#
   return model
   
model = FC_model()
model.summary()

for i, layer in enumerate(model.layers):
	print (layer.name)
	#print (layer._name)
model.save(f'{model_name}.h5')


#################################################

#read  -n 1 -p "\n When model trained press any key to phreeze and convert to pb file...\n" mainmenuinput


#python keras_to_tensorflow.py --input_model=${model_name}.h5 --output_model=${model_name}.pb

