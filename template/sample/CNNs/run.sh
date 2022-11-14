wdir=/data/dataset/npu

#adb shell ${wdir}/a.out model.rknn 20 
#adb shell ${wdir}/a.out mobilenet_v1_sample_test_precompiled.rknn ${wdir}/dog_224x224.jpg 20 
adb shell ${wdir}/a.out model_precompiled.rknn ${wdir}/space_shuttle_227.jpg 2
