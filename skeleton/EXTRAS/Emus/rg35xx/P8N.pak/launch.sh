#!/bin/sh

progdir="${SDCARD_PATH}/Tools/${PLATFORM}/Pico-8 Splore.pak/pico8-native"
thisdir=$(dirname "$0")
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

HOME="${progdir}" "${progdir}/pico8_dyn" -v -run "${1}"  &> $LOGS_PATH/P8N.txt
#restore previous state
rm -rf /usr/share/alsa/alsa.conf.d/mypatch.conf
overclock.elf $CPU_SPEED_MENU
