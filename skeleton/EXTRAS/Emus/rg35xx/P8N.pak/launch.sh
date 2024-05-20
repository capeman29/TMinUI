#!/bin/sh
progdir=$(dirname "$0")/pico8-native


# enable all CPU cores
echo 0xf > /sys/devices/system/cpu/autoplug/plug_mask
echo 1 > /sys/devices/system/cpu/cpu1/online
echo 1 > /sys/devices/system/cpu/cpu2/online
echo 1 > /sys/devices/system/cpu/cpu3/online

if [ -f "$1" ]; then
	GAME="$1"
fi

cd $progdir


# set CPU speed
#overclock.elf $CPU_SPEED_MENU
overclock.elf $CPU_SPEED_GAME
#overclock.elf $CPU_SPEED_PERF
HOME=$progdir \
SDL_VIDEODRIVER=directfb \
SDL_AUDIODRIVER=alsa \
./pico8_dyn -v  -run "$GAME" &> log.txt
sync

# restore default CPU cores state
echo 0x0 > /sys/devices/system/cpu/autoplug/plug_mask
echo 0 > /sys/devices/system/cpu/cpu1/online
echo 0 > /sys/devices/system/cpu/cpu2/online
echo 0 > /sys/devices/system/cpu/cpu3/online

overclock.elf $CPU_SPEED_MENU
