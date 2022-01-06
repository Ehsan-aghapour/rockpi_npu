path=/sys/devices/system/cpu/cpufreq
GPU_path=/sys/class/devfreq/ff9a0000.gpu

#hikey:
#GPU_path=/sys/devices/platform/e82c0000.mali/devfreq/e82c0000.mali

cat $path/policy0/scaling_cur_freq
echo pandoon > $path/policy4/scaling_governor
echo pandoon > $path/policy0/scaling_governor
echo pandoon > $GPU_path/governor


cat $path/policy4/scaling_governor
cat $path/policy0/scaling_governor
cat $GPU_path/governor



#insmod /system/gator.ko
#chmod +x /system/gatord

dmesg -C
logcat -c

cd system







