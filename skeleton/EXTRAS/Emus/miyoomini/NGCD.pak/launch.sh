#!/bin/sh

EMU_EXE=neocd
#CORES_PATH=$(dirname "$0")

###############################

EMU_TAG=$(basename "$(dirname "$0")" .pak)
ROM="$1"
mkdir -p "$BIOS_PATH/$EMU_TAG"
mkdir -p "$SAVES_PATH/$EMU_TAG"
HOME="$USERDATA_PATH"
cd "$HOME"
nice -20 minarch.elf "$CORES_PATH/${EMU_EXE}_libretro.so" "$ROM" $2 &> "$LOGS_PATH/$EMU_TAG.txt"
