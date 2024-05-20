#!/bin/sh
progdir=${SDCARD_PATH}/Emus/${PLATFORM}/P8N.pak/pico8-native
thisdir=$(dirname "$0")

# enable all CPU cores
echo 0xf > /sys/devices/system/cpu/autoplug/plug_mask
echo 1 > /sys/devices/system/cpu/cpu1/online
echo 1 > /sys/devices/system/cpu/cpu2/online
echo 1 > /sys/devices/system/cpu/cpu3/online

cd $progdir
echo "PICO-8 Starting Splore" > $thisdir/log.txt
#echo $progdir >> $thisdir/log.txt 2>&1

# set CPU speed
#overclock.elf $CPU_SPEED_MENU
overclock.elf $CPU_SPEED_GAME
#overclock.elf $CPU_SPEED_PERF
echo "mount --bind \"${SDCARD_PATH}/Roms/Pico-8 Native (P8N)\" \"${progdir}/.lexaloffle/pico-8/carts\"" >> $thisdir/log.txt 2>&1
mount --bind "${SDCARD_PATH}/Roms/Pico-8 Native (P8N)" "${progdir}/.lexaloffle/pico-8/carts" >> $thisdir/log.txt 2>&1
Sync 
HOME="${progdir}" \
SDL_VIDEODRIVER=directfb \
SDL_AUDIODRIVER=alsa \
./pico8_dyn -v -splore -home  >> $thisdir/log.txt 2>&1
umount /mnt/SDCARD/App/pico/.lexaloffle/pico-8/carts
sync

# restore default CPU cores state
echo 0x0 > /sys/devices/system/cpu/autoplug/plug_mask
echo 0 > /sys/devices/system/cpu/cpu1/online
echo 0 > /sys/devices/system/cpu/cpu2/online
echo 0 > /sys/devices/system/cpu/cpu3/online

overclock.elf $CPU_SPEED_MENU
