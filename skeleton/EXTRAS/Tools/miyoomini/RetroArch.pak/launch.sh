#!/bin/sh

RA_HOME = /mnt/SDCARD/Bios/RETROARCH
cd ${RA_HOME}
retroarch.elf --features -v &> "$LOGS_PATH/RetroArchFeatures.txt"
retroarch.elf --help -v &> "$LOGS_PATH/RetroArchHelp.txt"
retroarch.elf --config=${RA_HOME}/${PLATFORM}/retroarch.cfg --menu -v &> "$LOGS_PATH/RetroArch.txt"