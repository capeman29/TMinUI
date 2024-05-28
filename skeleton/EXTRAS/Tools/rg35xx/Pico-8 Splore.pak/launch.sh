#!/bin/sh

#set here the dir where splore looks for carts
romdir="${SDCARD_PATH}/Roms/Pico-8 (P8)"

# enable all CPU cores
echo 0xf > /sys/devices/system/cpu/autoplug/plug_mask
echo 1 > /sys/devices/system/cpu/cpu1/online
echo 1 > /sys/devices/system/cpu/cpu2/online
echo 1 > /sys/devices/system/cpu/cpu3/online

thisdir=$(dirname "$0")
progdir="$thisdir/pico8-native"
cd "$progdir"
echo "PICO-8 Starting Splore" > $thisdir/log.txt

export SDL_VIDEODRIVER=directfb
export SDL_AUDIODRIVER=alsa

# set CPU speed
#overclock.elf $CPU_SPEED_MENU
overclock.elf $CPU_SPEED_GAME
#overclock.elf $CPU_SPEED_PERF
#overclock.elf $CPU_SPEED_MAX

HOME="${progdir}" \
./pico8_dyn -v -splore -root_path "${romdir}" >> $thisdir/log.txt 2>&1

# restore default CPU cores state
echo 0x0 > /sys/devices/system/cpu/autoplug/plug_mask
echo 0 > /sys/devices/system/cpu/cpu1/online
echo 0 > /sys/devices/system/cpu/cpu2/online
echo 0 > /sys/devices/system/cpu/cpu3/online

overclock.elf $CPU_SPEED_MENU
