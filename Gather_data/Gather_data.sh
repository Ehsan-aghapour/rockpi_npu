#!/bin/bash
#adb root
#adb remount

#these are aliases in ~/.bash_aliases :
##setdate
##actpanda

adb shell mkdir -p /data/dataset
adb shell chmod -R 777 data/dataset
adb push runer.bash /system
adb shell chmod +x /system/runer.bash


adb push /home/ehsan/UvA/DRLPM/RockPi/Gator/Rockpi/gator_v1_normalize/driver/gator.ko /system
adb push /home/ehsan/UvA/DRLPM/RockPi/Gator/Rockpi/gator_v1_normalize/libs/arm64-v8a/gatord /system

adb push model.rknn /data/dataset
adb push configs.txt /data/dataset/
adb push game_list.txt /data/dataset/


adb push session.xml /system
adb push configuration.xml /system

adb shell rm -r /system/out2.apc
##adb shell rm /data/dataset/Data*

adb shell /system/runer.bash


#adb shell /system/gatord -s /system/session.xml -c /system/configuration.xml -o /system/out2.apc &
adb shell /system/gatord &

#sleep 10
adb shell "chmod 666 /dev/pandoon_device"

FFF="0"

data_dir=/home/ehsan/UvA/DRLPM/RockPi/Working_dir/AOSP/Gather_data/Data/$1
mkdir -p ${data_dir}
echo -e '\n\n'
while [ $FFF -ne -1 ]
do

	
	adb shell "[ -e /data/dataset/Data0.csv ] && rm /data/dataset/Data0.csv"
	#rm /data/dataset/Data0.csv
	read  -n 1 -p "press any key to satrt ..." mainmenuinput

	###adb shell 'echo 1 > /proc/pandoon'
	adb shell 'echo 1 > /dev/pandoon_device'
	#adb shell 'cat /proc/pandoon'

	read  -n 1 -p "press any key to end the capturing and process data..." mainmenuinput

	##adb shell 'echo 0 > /proc/pandoon'
	adb shell 'echo 0 > /dev/pandoon_device'

	#rm Data.csv
	name=$(date +%Y%m%d_%H%M%S)
	
	
	adb pull /data/dataset/Data0.csv ${data_dir}/Data0_$name.csv


	read  -n 1 -p "Data copied to deirectory.press any key to start training..." mainmenuinput


	
	ls ${data_dir}


	#python3 /media/ehsan/Learn/SUT/model_gator/model_inputs=504/normalized/dataset_model_input\=504_crop_normal.py /media/ehsan/Learn/SUT/model_gator/model_inputs=504/normalized/Data/$2

	#python3 /media/ehsan/Learn/SUT/model_gator/model_inputs=504/normalized/fig.py /media/ehsan/Learn/SUT/model_gator/model_inputs=504/normalized/Data/$2

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


