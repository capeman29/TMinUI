#!/bin/sh
# NOTE: becomes emulationstation

PLATFORM="m21"
FWNAME=MinUI
SDCARD_PATH="/mnt/SDCARD"
UPDATE_PATH="${SDCARD_PATH}/MinUI.zip"
SYSTEM_PATH="${SDCARD_PATH}/.system"

export LD_LIBRARY_PATH=${SDCARD_PATH}/${PLATFORM}/libmusl:$LD_LIBRARY_PATH
export SDL_NOMOUSE=1


CPU_PATH=/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor
#echo performance > "$CPU_PATH"

# install/update
# is there an update available?
if [ -f ${SDCARD_PATH}/My${FWNAME}-*-${PLATFORM}.zip ]; then
        NEWFILE=$(ls ${SDCARD_PATH}/My${FWNAME}-*-${PLATFORM}.zip)
#	echo "Trovato release file" >> $SDCARD_PATH/log.txt
#	echo "Sono nella directory " $(pwd) >> $SDCARD_PATH/log.txt

	if [ -d "$SYSTEM_PATH" ]; then
	    ACTION="updating"
	else
	    ACTION="installing"
	fi
	${SDCARD_PATH}/${PLATFORM}/binmusl/show.elf ${SDCARD_PATH}/${PLATFORM}/$ACTION.png
	#echo "Found Release file $NEWFILE ! ACTION = $ACTION" >> $LOGFILE
        ${SDCARD_PATH}/${PLATFORM}/binmusl/unzip -o $NEWFILE -d $SDCARD_PATH -x "m21/*" #&>> $LOGFILE
	sync

	#remove useless dirs
#	rm -rf $SDCARD_PATH/rg35xx
	rm -rf $SDCARD_PATH/trimui
#	rm -rf $SDCARD_PATH/miyoo354
	rm -rf $NEWFILE
	sync

#	echo "Finita fase 1" >> $SDCARD_PATH/log.txt
	
fi


#same as original MinUI install/update process
if [ -f "$UPDATE_PATH" ]; then


	if [ -d "$SYSTEM_PATH" ]; then
	    ACTION="updating"
	else
	    ACTION="installing"
	fi
	${SDCARD_PATH}/${PLATFORM}/binmusl/show.elf ${SDCARD_PATH}/${PLATFORM}/$ACTION.png
	#echo "Found Release file $NEWFILE ! ACTION = $ACTION" >> $LOGFILE
        ${SDCARD_PATH}/${PLATFORM}/binmusl/unzip -o $UPDATE_PATH -d $SDCARD_PATH #&>> $LOGFILE
	sync
	# the updated system finishes the install/update
	rm -rf ${UPDATE_PATH}
	$SYSTEM_PATH/$PLATFORM/bin/install.sh

fi

ROOTFS_MOUNTPOINT=/overlay
ROOTFS_IMG=${SYSTEM_PATH}/${PLATFORM}/rootfs.ext2
${SDCARD_PATH}/${PLATFORM}/binmusl/fuse2fs ${ROOTFS_IMG} ${ROOTFS_MOUNTPOINT} 2&> /dev/null

sync
#ls -l ${ROOTFS_MOUNTPOINT}/* >> /mnt/SDCARD/ls.txt && sync
if [ -f ${ROOTFS_MOUNTPOINT}/bin/busybox ]; then
    rm -rf ${ROOTFS_MOUNTPOINT}/tmp/*
    mkdir -p ${ROOTFS_MOUNTPOINT}/mnt/SDCARD
    if [ ! -f ${ROOTFS_MOUNTPOINT}/etc/asound.conf ]; then
	cp /etc/asound.conf ${ROOTFS_MOUNTPOINT}/etc/asound.conf
	chmod 666 ${ROOTFS_MOUNTPOINT}/etc/asound.conf
	sync
    fi

    if [ ! -f ${ROOTFS_MOUNTPOINT}/etc/fb.modes ]; then
	cp $SDCARD_PATH/fb.modes ${ROOTFS_MOUNTPOINT}/etc/fb.modes
	chmod 666 ${ROOTFS_MOUNTPOINT}/etc/fb.modes
	sync
    fi



#mount all other fs as minui on rg35xx og
    for f in dev dev/pts proc sys mnt/SDCARD tmp
    do
	mount -o bind /${f} ${ROOTFS_MOUNTPOINT}/${f}
    done
    export PATH=/bin:/sbin:/usr/bin:/usr/sbin
    export LD_LIBRARY_PATH=/usr/lib/:/lib/
    export HOME=$SDCARD_PATH
    chroot $ROOTFS_MOUNTPOINT ${SYSTEM_PATH}/${PLATFORM}/paks/MinUI.pak/launch.sh #&> $SDCARD_PATH/chroot.txt
    sync
fi


#umount ${ROOTFS_MOUNTPOINT}
sync

echo "Exiting" > ${SDCARD_PATH}/bootfailed.txt

sync
halt # under no circumstances should stock be allowed to touch this card
