import cv2
import sys

scale=58.82
m1=103.94
m2=116.78
m3=123.68
mean=np.array([m1,m2,m3])

img=cv2.imread(sys.argv[1])
#if you want to change RGB sequence:
#img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
norm_img=(img-mean)/sclae
img2=(norm_img.transpose([2,0,1]))
