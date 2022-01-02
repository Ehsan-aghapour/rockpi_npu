import numpy as np
mat=np.random.rand(475).astype('float32')
with open('test.npy', 'wb') as f:
	np.save(f,mat)
	

