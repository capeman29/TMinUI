#!/system/bin/sh

SYSTEM_PATH=/mnt/sdcard/.system/rg35xx
SWAPFILE=${SYSTEM_PATH}/myswapfile

if [ -f ${SWAPFILE}.gz ]; then
#the swapfile does not exists, let's create it
    rm -rf $SWAPFILE
    busybox gzip -d ${SWAPFILE}.gz
    chmod 600 $SWAPFILE
    mkswap $SWAPFILE
fi
swapon $SWAPFILE