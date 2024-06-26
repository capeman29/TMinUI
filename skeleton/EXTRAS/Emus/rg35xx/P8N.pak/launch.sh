#!/bin/sh

# enable all CPU cores
#echo 0xf > /sys/devices/system/cpu/autoplug/plug_mask
#echo 1 > /sys/devices/system/cpu/cpu1/online
#echo 1 > /sys/devices/system/cpu/cpu2/online
#echo 1 > /sys/devices/system/cpu/cpu3/online

progdir="${SDCARD_PATH}/Tools/${PLATFORM}/Pico-8 Splore.pak/pico8-native"
thisdir=$(dirname "$0")
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
./pico8_dyn -v -run "${1}"  >> "${thisdir}/log.txt" 2>&1

# restore default CPU cores state
#echo 0x0 > /sys/devices/system/cpu/autoplug/plug_mask
#echo 0 > /sys/devices/system/cpu/cpu1/online
#echo 0 > /sys/devices/system/cpu/cpu2/online
#echo 0 > /sys/devices/system/cpu/cpu3/online

overclock.elf $CPU_SPEED_MENU
