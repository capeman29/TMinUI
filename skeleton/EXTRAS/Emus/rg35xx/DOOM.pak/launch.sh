#!/bin/sh

EMU_EXE=prboom

#CPU_OC=${CPU_SPEED_MAX} # 1.5 GHz
#CPU_OC=${CPU_SPEED_PERF}  # 1.4 GHz
CPU_OC=${CPU_SPEED_GAME}  # 1.2 GHz
#CPU_OC=${CPU_SPEED_POWERSAVE}  # 1.1 GHz
#CPU_OC=${CPU_SPEED_MENU}  # 0.5 GHz

###############################


EMU_TAG=$(basename "$(dirname "$0")" .pak)
ROM="$1"
mkdir -p "$BIOS_PATH/$EMU_TAG"
mkdir -p "$SAVES_PATH/$EMU_TAG"
mkdir -p "${USERDATA_PATH}/${EMU_TAG}-${EMU_EXE}"
mkdir -p "${SHARED_USERDATA_PATH}/${EMU_TAG}-${EMU_EXE}"

THIS_CORE_PATH="$(dirname "$0")"

#create custom cfg for retroarch
if [ ! -f "${THIS_CORE_PATH}/specialcfg.cfg" ]; then
echo "system_directory = \"${BIOS_PATH}/$EMU_TAG\"" > "${THIS_CORE_PATH}/specialcfg.cfg"
echo "rgui_config_directory = \"${SHARED_USERDATA_PATH}/${EMU_TAG}-${EMU_EXE}\"" >> "${THIS_CORE_PATH}/specialcfg.cfg"
echo "cheat_database_path = \"${BIOS_PATH}/$EMU_TAG/cheats\"" >> "${THIS_CORE_PATH}/specialcfg.cfg"
echo "input_remapping_directory = \"${BIOS_PATH}/$EMU_TAG/config/remaps\"" >> "${THIS_CORE_PATH}/specialcfg.cfg"
echo "recording_output_directory = \"${SAVES_PATH}/$EMU_TAG\"" >> "${THIS_CORE_PATH}/specialcfg.cfg"
echo "savefile_directory = \"${SAVES_PATH}/${EMU_TAG}\"" >> "${THIS_CORE_PATH}/specialcfg.cfg"
echo "savestate_directory = \"${USERDATA_PATH}/${EMU_TAG}-${EMU_EXE}\"" >> "${THIS_CORE_PATH}/specialcfg.cfg"
echo "screenshot_directory = \"${SAVES_PATH}/${EMU_TAG}\"" >> "${THIS_CORE_PATH}/specialcfg.cfg"
echo "system_directory = \"${BIOS_PATH}/${EMU_TAG}\"" >> "${THIS_CORE_PATH}/specialcfg.cfg"
fi


RA_HOME="${BIOS_PATH}/RETROARCH"
cd "$RA_HOME"
overclock.elf ${CPU_OC}
retroarch.elf -v --config "${BIOS_PATH}/RETROARCH/${PLATFORM}/retroarch.cfg" --appendconfig "${THIS_CORE_PATH}/specialcfg.cfg" -L "${CORES_PATH}/${EMU_EXE}_libretro.so" "$ROM" &> "$LOGS_PATH/$EMU_TAG.txt"
overclock.elf ${CPU_SPEED_MENU}
