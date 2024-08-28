#!/bin/sh
#set here the dir where splore looks for carts
romdir="${SDCARD_PATH}/Roms/Pico-8 (P8)"



# set CPU speed
#overclock.elf $CPU_SPEED_MENU
overclock.elf $CPU_SPEED_GAME
#overclock.elf $CPU_SPEED_PERF
#overclock.elf $CPU_SPEED_MAX


progdir=$(dirname "$0")/pico8-native
thisdir=$(dirname "$0")
cd "${progdir}"

export LD_LIBRARY_PATH="$progdir/lib:$thisdir/patch:/mnt/SDCARD/.system/my282/lib:/lib:${LD_LIBRARY_PATH}"
export SDL_VIDEODRIVER=mali
export SDL_AUDIODRIVER=alsa
export SDL_JOYSTICKDRIVER=a30

cp "$thisdir/patch/onioncfg.json" "$progdir/cfg/"
HOME="$progdir" \
./pico8_dyn -v -splore -root_path "${romdir}" &> $thisdir/log.txt

overclock.elf $CPU_SPEED_MENU
