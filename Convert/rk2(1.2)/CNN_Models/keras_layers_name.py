# ai2
import keras
import numpy as np
import sys

name=sys.argv[1]
model=keras.models.load_model(name)
model.summary()

for i,layer in enumerate(model.layers):
	print(f'Layer {i}, Layer name:{layer.name}. Layer input:{layer.input}\n layer output: {layer.output}\n')
if False:
	mat=np.random.rand(475).astype('float32')
	for i in range(475):
		mat[i]=i
	#with open('test.npy', 'rb') as f:
	#	mat=np.load(f)

	out=model.predict(mat.reshape(1,-1))
	print(out)
