#!/bin/sh
CUST_LOGO=0
CUST_CPUCLOCK=1
USE_752x560_RES=0

mydir=$(dirname "$0")/drastic

get_curvol() {
    awk '/LineOut/ {if (!printed) {gsub(",", "", $8); print $8; printed=1}}' /proc/mi_modules/mi_ao/mi_ao0
}


purge_devil() {
    if pgrep -f "/dev/l" > /dev/null; then
        echo "Process /dev/l is running. Killing it now..."
        killall -9 l
    else
        echo "Process /dev/l is not running."
    fi
}

cd $mydir
if [ ! -f "/tmp/.show_hotkeys" ]; then
    touch /tmp/.show_hotkeys
    LD_LIBRARY_PATH=./libs:/customer/lib:/config/lib ./show_hotkeys
fi

export HOME=$mydir
export PATH=$mydir:$PATH
export LD_LIBRARY_PATH=$mydir/libs:$LD_LIBRARY_PATH
export SDL_VIDEODRIVER=mmiyoo
export SDL_AUDIODRIVER=mmiyoo
export EGL_VIDEODRIVER=mmiyoo




#purge_devil

if [  -d "/customer/app/skin_large" ]; then
    USE_752x560_RES=1
fi

if [ "$USE_752x560_RES" == "1" ]; then
    fbset -g 752 560 752 1120 32
fi

cd $mydir
if [ "$CUST_LOGO" == "1" ]; then
    ./png2raw
fi

sv=`cat /proc/sys/vm/swappiness`

# 60 by default
echo 10 > /proc/sys/vm/swappiness

cd $mydir

if [ "$CUST_CPUCLOCK" == "1" ]; then
    overclock.elf $CPU_SPEED_PERF
fi

wait_for_device() {
    local start_time
    local elapsed_time
    start_time=$(date +%s)
    while [ ! -e /proc/mi_modules/mi_ao/mi_ao0 ]; do
        sleep 0.2
        elapsed_time=$(( $(date +%s) - start_time ))
        if [ "$elapsed_time" -ge 4 ]; then
        #echo "FAILED">>$SDCARD_PATH/audioserver.txt
            return 1
        fi
    done
    #keymon.elf &
}


set_snd_level() {
    local target_vol="$1"
    wait_for_device
    echo "set_ao_mute 0" > /proc/mi_modules/mi_ao/mi_ao0
    echo "set_ao_volume 0 ${target_vol}" > /proc/mi_modules/mi_ao/mi_ao0
    echo "set_ao_volume 1 ${target_vol}" > /proc/mi_modules/mi_ao/mi_ao0
}

curvol=$(get_curvol)
#killall -9 keymon.elf
if $IS_PLUS; then
    killall -9 audioserver
else
    killall -9 audioserver.mod
fi
sleep 0.2
set_snd_level "${curvol}" &

./drastic "$1"
sync

echo $sv > /proc/sys/vm/swappiness

if [  -d "/customer/app/skin_large" ]; then
    USE_752x560_RES=0
fi

if [ "$USE_752x560_RES" == "1" ]; then
    fbset -g 640 480 640 960 32
fi

#killall -9 keymon.elf
sleep 0.2
if $IS_PLUS; then
	/customer/app/audioserver -60 & # &> $SDCARD_PATH/audioserver.txt &
	export LD_PRELOAD=/customer/lib/libpadsp.so
else
	if [ -f /customer/lib/libpadsp.so ]; then
	    LD_PRELOAD=as_preload.so audioserver.mod &
	    export LD_PRELOAD=libpadsp.so
	fi
fi
wait_for_device &
overclock.elf $CPU_SPEED_MENU
