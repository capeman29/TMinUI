#!/bin/sh

#set here the dir where splore looks for carts
romdir="${SDCARD_PATH}/Roms/Pico-8 (P8)"

thisdir=$(dirname "$0")
progdir="$thisdir/pico8-native"
cd "$progdir"
echo "PICO-8 Starting Splore" > "${thisdir}/log.txt"

export SDL_VIDEODRIVER=directfb
export SDL_AUDIODRIVER=alsa

# set CPU speed
#overclock.elf $CPU_SPEED_MENU
overclock.elf $CPU_SPEED_GAME
#overclock.elf $CPU_SPEED_PERF
#overclock.elf $CPU_SPEED_MAX

cp "${progdir}/patch/mypatch.conf" /usr/share/alsa/alsa.conf.d/mypatch.conf

HOME="${progdir}" "${progdir}/pico8_dyn" -v -splore -root_path "${romdir}" &> $LOGS_PATH/pico8_splore.txt

#restore previous state
rm -rf /usr/share/alsa/alsa.conf.d/mypatch.conf
overclock.elf $CPU_SPEED_MENU
