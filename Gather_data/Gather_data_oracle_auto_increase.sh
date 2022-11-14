#!/bin/bash

#adb root
#adb remount


#adb shell sh /sdcard/.chaozhuo.gameassistant2/inject.sh

adb shell mkdir /data/dataset
adb shell chmod -R 777 data/dataset
adb push runer.bash /system
adb shell chmod +x /system/runer.bash

#adb push /media/ehsan/Learn/NUS/ubuntu/gator/modified/gator/driver/gator.ko /system
#adb push /media/ehsan/Learn/NUS/ubuntu/gator/modified/gator/libs/arm64-v8a/gatord /system


adb push /media/ehsan/Learn/NUS/ubuntu/gator/modified_withoutsending_data_for_streamline/gator_v1_normalize/driver/gator.ko /system
adb push /media/ehsan/Learn/NUS/ubuntu/gator/modified_withoutsending_data_for_streamline/gator_v1_normalize/libs/arm64-v8a/gatord /system


adb push /media/ehsan/Learn/SUT/model_gator/model_inputs=504/normalized/$1/nm1.cambricon /system
adb push /media/ehsan/Learn/SUT/model_gator/model_inputs=504/normalized/$1/nm1.cambricon /data/dataset
adb push /media/ehsan/Learn/SUT/model_gator/model_inputs=504/normalized/$1/nm1.cambricon.inputs_outputs.aux /system
adb push /media/ehsan/Learn/SUT/model_gator/model_inputs=504/normalized/$1/nm1.cambricon.inputs_outputs.aux /data/dataset
##adb push configs.txt /data/dataset/

adb push session.xml /system
adb push configuration.xml /system

adb shell rm -r /system/out2.apc
#adb shell rm /data/dataset/Data*

adb shell /system/runer.bash


adb shell /system/gatord -s /system/session.xml -c /system/configuration.xml -o /system/out2.apc &
#adb shell /system/gatord &

sleep 6

mkdir /media/ehsan/Learn/SUT/model_gator/model_inputs=504/$2

FFF="0"

adb shell "rm /data/dataset/configs.txt"

adb shell "chmod 666 /dev/pandoon_device"

echo -e '\n\n'

read -p "Enter desired Frequencies: " FFF

step=1

while [ $FFF -ne -1 ]
do

	#sleep 10


	#adb shell 'echo 1 > /dev/pandoon_device'

	adb shell "echo 101'\n'$FFF > /data/dataset/configs.txt"

	#FFF=`expr $FFF + $step`	

	echo "Frequency is: $FFF"


	read  -n 1 -p "Press any key to start the capturing..." mainmenuinput

	adb shell 'echo 1 > /dev/pandoon_device'
	#adb shell 'cat /proc/pandoon'
	
	adb shell "rm /data/dataset/configs.txt"

	sleep 60

	read  -n 1 -p "Press any key to end the capturing and process data..." mainmenuinput

	adb shell 'echo 0 > /dev/pandoon_device'

	#rm Data.csv

	mkdir /media/ehsan/Learn/SUT/model_gator/model_inputs=504/$2/$FFF
	
	adb pull /data/dataset/Data$FFF.csv /media/ehsan/Learn/SUT/model_gator/model_inputs=504/$2/$FFF/

	#libreoffice --calc /media/ehsan/Learn/SUT/model_gator/model_inputs=504/$2/Data$FFF.csv
	#read  -n 1 -p "\nData copied to deirectory.\npress any key to start training...\n" mainmenuinput

	((FFF=FFF-step))
	
	ls /media/ehsan/Learn/SUT/model_gator/model_inputs=504/$2



done 


#/media/ehsan/Learn/sut/newmodel/$2/train.sh $2

#read  -n 1 -p "\n when model trained press any key to phreeze and convert to pb file...\n" mainmenuinput


#python3 /media/ehsan/Learn/sut/newmodel/tools/keras_to_tensorflow.py --input_model=/media/ehsan/Learn/sut/newmodel/$2/nm1.h5 --output_model=/media/ehsan/Learn/sut/newmodel/$2/nm1.pb

#read  -n 1 -p "\n model converted press any key to check compatibility...\n" mainmenuinput

#java -jar /media/ehsan/Learn/sut/newmodel/tools/OperatorsCheck.jar -t tensorflow -p /media/ehsan/Learn/sut/newmodel/$2/nm1.pb

#read  -n 1 -p "\nCompatibility OK :). press any key to convert to hikey970 npu format...\n" mainmenuinput

#export LD_LIBRARY_PATH=/media/ehsan/Learn/sut/newmodel/tools/so

#/media/ehsan/Learn/sut/newmodel/tools/pb_to_offline --graph=/media/ehsan/Learn/sut/newmodel/$2/nm1.pb --param_file=/media/ehsan/Learn/sut/newmodel/tools/nm.txt

#read  -n 1 -p "\nConverted.:). press any key to move to directory...\n" mainmenuinput

