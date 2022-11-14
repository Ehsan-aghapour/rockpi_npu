from rknn.api import RKNN
import sys
 
name=sys.argv[1]
rknn_name=name.split('/')[-1].split('.')[0]+'.rknn'
 
if __name__ == '__main__':
    rknn = RKNN()   # Create an RKNN execution object
 
    '''
    Configure model input for NPU preprocessing of input data
    channel_mean_value='0 0 0 255', when runing forward inference, the RGB data will be
    converted as follows (R - 0) / 255, (G - 0) / 255, (B - 0) / 255,
    The RKNN model automatically performs the mean and normalization.
    reorder_channel='0 1 2' , used to specify whether to adjust the image channel order, 
    set to 0 1 2, means no adjustment according to the input image channel order.
    reorder_channel='2 1 0' , indicates that 0 and 2 channels are exchanged.
    If the input is RGB, it will be adjusted to BGR. If it is BGR will be adjusted to RGB
    Image channel order is not adjusted
    '''
 
    #rknn.config(channel_mean_value='0 0 0 255', reorder_channel='0 1 2')
    #rknn.config(target_platform=["rk1806", "rk1808", "rk3399pro"])
    rknn.config()
 
    '''
    load TensorFlow model
    tf_pb='digital_gesture.pb' specify the TensorFlow model to be converted
    inputs specify the input node in the model
    outputs specify the output node in the model
    input_size_list specify the size of the model input
    '''
 
    print('--> Loading model')
    #rknn.load_tensorflow(tf_pb='model.pb',
    #                     inputs=['test_in'],
    #                     outputs=['test_out/BiasAdd'],
    #                     input_size_list=[[INPUT_SIZE]])
    rknn.load_onnx(name)
    print('done')
 
    '''
    Create a parsing pb model
    do_quantization=False do not to be quantified
    Quantization will reduce the size of the model and increase the speed of the operation,
    but there will be loss of precision.
    '''
 
    print('--> Building model')
    rknn.build(do_quantization=False)
    print('done')
    #rknn.export_rknn('./model.rknn')  # Export and save rknn model file
    rknn.export_rknn(rknn_name)  # Export and save rknn model file
    rknn.release()  # Release RKNN Context

