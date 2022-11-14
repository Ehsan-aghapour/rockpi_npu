from PIL import Image
import os
import sys

image_size={"GoogLeNet":[224,224],"alexnet":[227,227],"SqueezeNet":[227,227], "ResNet50":[224,224], "MobileNet":[224,224]}
height=sys.argv[2]
weight=sys.argv[2]
name=sys.argv[1]
image = Image.open(name)
resized_image=image.resize((int(height),int(weight)))
name2=name[0:name.find('.')]+str(height)+'.jpg'
resized_image.save(name2)

