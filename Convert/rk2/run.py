
import numpy as np
from PIL import Image
from rknn.api import RKNN


# Analyze the output of the model to get the most probable gesture and corresponding probability
def get_predict(probability):
    data = probability[0][0]
    data = data.tolist()
    max_prob = max(data)
    return data.index(max_prob), max_prob


def load_model():
    rknn = RKNN()  # Create an RKNN execution object
    print('-->loading model')
    rknn.load_rknn('./model.rknn')  # Load RKNN model
    print('loading model done')
    print('--> Init runtime environment')
    ret = rknn.init_runtime(target='rk3399pro')  # Initialize the RKNN runtime environment
    #ret = rknn.init_runtime()  # Initialize the RKNN runtime environment
    if ret != 0:
        print('Init runtime environment failed')
        exit(ret)
    print('done')
    return rknn


def predict(rknn):
    rknn.list_devices()
    ##im = Image.open("../picture/6_7.jpg")   # load image
    ##im = im.resize((64, 64), Image.ANTIALIAS)  # Image resize to 64x64
    ##mat = np.asarray(im.convert('RGB'))    # Convert to RGB format
    ###mat=np.random.rand(475).astype('float32')
    with open('test.npy', 'rb') as f:
    	mat=np.load(f)
    mat=[]
    mat=[i for i in range(475)]
    print (mat)
    mat=np.array(mat).astype('float32')
    print(f'inputs:{mat}')
    outputs = rknn.inference(inputs=[mat])   # Run forward inference and get the inference result
    print(outputs)
    pred, prob = get_predict(outputs)     # Transform the inference results into visual information
    print(prob)
    print(pred)
    rknn.eval_perf(inputs=[mat], is_print=True)


if __name__=="__main__":
    rknn = load_model()
    predict(rknn)
    rknn.release()
