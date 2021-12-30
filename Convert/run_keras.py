import keras
import numpy as np

model=keras.models.load_model("test_keras.h5")

mat=np.random.rand(475).astype('float32')
for i in range(475):
	mat[i]=i
#with open('test.npy', 'rb') as f:
#	mat=np.load(f)

out=model.predict(mat.reshape(1,-1))
print(out)
