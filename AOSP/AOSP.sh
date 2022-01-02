
#https://wiki.radxa.com/RockpiN10/Android8
wget 'https://storage.googleapis.com/git-repo-downloads/repo' -P /tmp/
sudo cp /tmp/repo /usr/local/bin/repo
sudo chmod +x /usr/local/bin/repo

# this format is for running all commands as sudo:
sudo -- sh -c 'apt-get update -y && apt-get install -y openjdk-8-jdk python git-core gnupg flex bison gperf build-essential \
          zip curl liblz4-tool zlib1g-dev gcc-multilib g++-multilib libc6-dev-i386 \
          lib32ncurses5-dev x11proto-core-dev libx11-dev lib32z-dev ccache \
          libgl1-mesa-dev libxml2-utils xsltproc unzip mtools u-boot-tools \
          htop iotop sysstat iftop pigz bc device-tree-compiler lunzip \
          dosfstools vim-common parted udev lzop'
          
          
export JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64
export PATH=$JAVA_HOME/bin:$PATH
export CLASSPATH=.:$JAVA_HOME/lib:$JAVA_HOME/lib/tools.jar

mkdir rockpi-n10-android8
cd rockpi-n10-android8

repo init -u https://github.com/radxa/manifests.git -b rk3399pro-android-8.1 -m rk3399pro-rk-vendor-release.xml
repo sync -d --no-tags -j4

#build uboot
cd u-boot
./make.sh rk3399pro_dual
cd ..
#The generated images are **rk3399_loader_v_xxx.bin** , **idbloader.img** and **uboot.img**


#build kernel:
cd kernel
make rockchip_defconfig
# for core board older than version v1.3
make rk3399pro-rockpi-n10-android.img -j$(nproc)
# for new core board
make rk3399pro-rockpi-n10-v1.3-android.img -j$(nproc)
cd ..
#The generated images are **kernel.img** and **resource.img**


#Building AOSP:
source build/envsetup.sh
lunch rk3399pro-userdebug
make -j$(nproc)

#some errors:
#export LC_ALL="en_US.UTF-8"

#SSL error when connecting to the jack server:
#https://stackoverflow.com/questions/67363030/rebuild-android-code-with-error-ssl-error-when-connecting-to-the-jack-server-t
#1:
#Try to simply restart the jack server by below command at your android root folder
#./prebuilts/sdk/tools/jack-admin kill-server ./prebuilts/sdk/tools/jack-admin start-server

#2:
#Remove TLSv1, TLSv1.1 from jdk.tls.disabledAlgorithms in /etc/java-8-openjdk/security/java.security file
#Restart the jack server: cd ./prebuilts/sdk/tools/ ./jack-admin kill-server ./jack-admin start-server 
#*prebuilts in AOSP
          
#3: ...


ln -s RKTools/linux/Linux_Pack_Firmware/rockdev/ rockdev
./mkimage.sh ota
#The generated images under rockdev/Image-rk3399pro (are all images)

cd rockdev
ln -s Image-rk3399pro Image

#RkUpdate Image
./mkupdate.sh
#The images under rockdev/ are `update.img`


#installation https://wiki.radxa.com/RockpiN10/dev/usb-install-for-android-image
# go to maskroom mode by:Press and hold the maskrom key, short press the reset key (lsusb should show the device in pc)
upgrade_tool uf update.img


#configing upgrade tool : https://wiki.radxa.com/Android/upgrage_tool
# download tool : https://wiki.radxa.com/mw/images/7/74/Linux_Upgrade_Tool.zip
#Copy Config File
mkdir -p ~/.config/upgrade_tool
cp $(Linux_Upgrade_Tool)/config.ini ~/.config/upgrade_tool/

#Copy Process File
sudo cp $(Linux_Upgrade_Tool)/upgrade_tool /usr/local/bin/upgrade_tool
sudo chmod +x /usr/local/bin/upgrade_tool

#Check Upgrade_Tool Work
upgrade_tool -v

#List Devices
upgrade_tool ld


#changes files locally
#https://stackoverflow.com/questions/3407287/how-do-you-edit-files-over-ssh/3407378
#https://superuser.com/questions/340297/edit-text-files-over-ssh-using-a-local-text-editor
sudo apt-get install sshfs
mkdir ~/remote_code
sshfs ehsan@145.100.131.45:/home/ehsan/rockpi_n10/frameworks/native/opengl/libs/EGL/ ~/remote_code

#Choreographer: Skipped 85 frames!  The application may be doing too much work on its main thread.


WARNING: drivers/gpu/arm/midgard/midgard_kbase: 'kbase_va_free' exported twice. Previous export was in drivers/gpu/arm/bifrost/bifrost_kbase.ko
WARNING: drivers/gpu/arm/midgard/midgard_kbase: '_mali_profiling_control' exported twice. Previous export was in drivers/gpu/arm/bifrost/bifrost_kbase.ko
WARNING: drivers/gpu/arm/midgard/midgard_kbase: 'kbase_va_alloc' exported twice. Previous export was in drivers/gpu/arm/bifrost/bifrost_kbase.ko
WARNING: drivers/gpu/arm/midgard/midgard_kbase: 'kbase_context_set_create_flags' exported twice. Previous export was in drivers/gpu/arm/bifrost/bifrost_kbase.ko
WARNING: drivers/gpu/arm/midgard/midgard_kbase: 'kbase_release_device' exported twice. Previous export was in drivers/gpu/arm/bifrost/bifrost_kbase.ko
WARNING: drivers/gpu/arm/midgard/midgard_kbase: 'kbase_create_context' exported twice. Previous export was in drivers/gpu/arm/bifrost/bifrost_kbase.ko
WARNING: drivers/gpu/arm/midgard/midgard_kbase: 'kbase_instr_hwcnt_clear' exported twice. Previous export was in drivers/gpu/arm/bifrost/bifrost_kbase.ko
WARNING: drivers/gpu/arm/midgard/midgard_kbase: 'kbasep_debug_assert_call_hook' exported twice. Previous export was in drivers/gpu/arm/bifrost/bifrost_kbase.ko
WARNING: drivers/gpu/arm/midgard/midgard_kbase: 'kbase_gator_hwcnt_init_names' exported twice. Previous export was in drivers/gpu/arm/bifrost/bifrost_kbase.ko
WARNING: drivers/gpu/arm/midgard/midgard_kbase: 'kbase_gator_instr_hwcnt_dump_complete' exported twice. Previous export was in drivers/gpu/arm/bifrost/bifrost_kbase.ko
WARNING: drivers/gpu/arm/midgard/midgard_kbase: 'kbase_gator_hwcnt_init' exported twice. Previous export was in drivers/gpu/arm/bifrost/bifrost_kbase.ko
WARNING: drivers/gpu/arm/midgard/midgard_kbase: 'kbase_gator_hwcnt_term' exported twice. Previous export was in drivers/gpu/arm/bifrost/bifrost_kbase.ko
WARNING: drivers/gpu/arm/midgard/midgard_kbase: 'kbase_gator_hwcnt_term_names' exported twice. Previous export was in drivers/gpu/arm/bifrost/bifrost_kbase.ko
WARNING: drivers/gpu/arm/midgard/midgard_kbase: 'kbase_instr_hwcnt_request_dump' exported twice. Previous export was in drivers/gpu/arm/bifrost/bifrost_kbase.ko
WARNING: drivers/gpu/arm/midgard/midgard_kbase: 'kbase_destroy_context' exported twice. Previous export was in drivers/gpu/arm/bifrost/bifrost_kbase.ko
WARNING: drivers/gpu/arm/midgard/midgard_kbase: 'kbase_find_device' exported twice. Previous export was in drivers/gpu/arm/bifrost/bifrost_kbase.ko
WARNING: drivers/gpu/arm/midgard/midgard_kbase: 'kbase_gator_instr_hwcnt_dump_irq' exported twice. Previous export was in drivers/gpu/arm/bifrost/bifrost_kbase.ko
WARNING: drivers/gpu/arm/midgard/midgard_kbase: 'kbase_instr_hwcnt_dump_complete' exported twice. Previous export was in drivers/gpu/arm/bifrost/bifrost_kbase.ko






