## MyMinUI install instructions:

# Miyoo Mini:

Format as FAT32 a micro sdcard with enough space to contains all Your games, the volume name assigned to the partition doesn't matter.
in the release file (i.e. MyMinUI-YYYYMMDDb-0-miyoomini.zip) there is a folder called "miyoo" copy that folder as is in the FAT32 partition created above.
Copy also the whole release zip file (leave it zipped) in the FAT32 partition created above.

Put the sdcard in the device and boot, a screen reporting "Installing MyMinUI..." is shown, after a while the device will reboot, again "Installing MyMinUI..." screen then after a while (be patient in this stage as the swap creation process takes time)
Once installation process is completed press the PWR button to shutdown the device, remove the sdcard and insert it in the pc, now You can fill the bios and roms folders with Your files. Put the sdcard in the device and play Your games. 


# Miyoo Mini Plus:

Format as FAT32 a micro sdcard with enough space to contains all Your games, the volume name assigned to the partition doesn't matter.
in the release file (i.e. MyMinUI-YYYYMMDDb-0-miyoomini.zip) there is a folder called "miyoo354" copy that folder as is in the FAT32 partition created above.
Copy also the whole release zip file (leave it zipped) in the FAT32 partition created above.

Put the sdcard in the device and boot, a screen reporting "Installing MyMinUI..." is shown, after a while the device will reboot, again "Installing MyMinUI..." screen then after a while (be patient in this stage as the swap creation process takes time)
Once installation process is completed press the PWR button to shutdown the device, remove the sdcard and insert it in the pc, now You can fill the bios and roms folders with Your files. Put the sdcard in the device and play Your games. 


# Miyoo A30:

Format as FAT32 a micro sdcard with enough space to contains all Your games, the volume name assigned to the partition doesn't matter.
in the release file (i.e. MyMinUI-YYYYMMDDb-0-my282.zip) there is a folder called "miyoo" copy that folder as is in the FAT32 partition created above.
Copy also the whole release zip file (leave it zipped) in the FAT32 partition created above.

Put the sdcard in the device and boot, a screen reporting "Installing MyMinUI..." is shown.
Once installation process is completed press the PWR button to shutdown the device, remove the sdcard and insert it in the pc, now You can fill the bios and roms folders with Your files. Put the sdcard in the device and play Your games. 


# RG35XX OG (2022-2023) Single SDCard method:

Download the debloated stock ambernic image (TF1.img) from the legacy MinUI repo: https://github.com/shauninman/MinUI-Legacy-RG35XX/releases/download/stock-tf1-20230309/TF1.img.zip
Unzip then flash TF1.img to a micro sdcard with enough space to contains all Your games, use the flasher You like. 

This creates 4 partitions in the sdcard, 2 of them are visible only in Linux os while the "misc" and "ROMS" FAT32 partitions are both visible in Macos as well as Windows.
in the release file (i.e. MyMinUI-YYYYMMDDb-0-rg35xx.zip) there is a folder called "rg35xx" that contains a file called "dmenu.bin" copy this file to the "misc" partition.
The "ROMS" partition just created is limited to 3GB, use a partition manager to resize the partition to fill the remaining sdcard available space. 
Copy also the whole release zip file (leave it zipped) to the "ROMS" partition.

Put the sdcard in the device and boot, a screen reporting "Installing MyMinUI..." is shown, after a while the device will reboot, again "Installing MyMinUI..." screen then after a while (be patient in this stage as the swap creation process takes time)
Once installation process is completed press the PWR button to shutdown the device, remove the sdcard and insert it in the pc, now You can fill the bios and roms folders with Your files. Put the sdcard in the device and play Your games. 


# RG35XX OG (2022-2023) Two SDCard method:

Download the debloated stock ambernic image (TF1.img) from the legacy MinUI repo: https://github.com/shauninman/MinUI-Legacy-RG35XX/releases/download/stock-tf1-20230309/TF1.img.zip
Unzip then flash TF1.img to a micro sdcard (at least 8GB no need to be bigger than that), I personally use BalenaEtcher on macos, use the flasher You like. 

This creates 4 partitions in the sdcard, 2 of them are visible only in Linux os while the "misc" and "ROMS" FAT32 partitions are both visible in Macos as well as Windows.
in the release file (i.e. MyMinUI-YYYYMMDDb-0-rg35xx.zip) there is a folder called "rg35xx" that contains a file called "dmenu.bin" copy this file to the "misc" partition.

Format the second sdcard as FAT32, it is also supported exFAT if You like.
Copy the whole release zip file (leave it zipped) to the partition of the second sdcard.

Put both sdcards (sdcard flashed with TF1.img in the TF1 slot...) in the device and boot, a screen reporting "Installing MyMinUI..." is shown, after a while the device will reboot, again "Installing MyMinUI..." screen then after a while (be patient in this stage as the swap creation process takes time)
Once installation process is completed press the PWR button to shutdown the device, remove the second sdcard and insert it in the pc, now You can fill the bios and roms folders with Your files. Put the second sdcard in the device and play Your games. 

The TF1 sdcard is used to boot MinUI while the second is used to store minui, all files are in TF2.

# Share sdcard across other devices:

Well You can setup a single sdcard that can run on all 4 supported devices.

requirements:
The shared sdcard must be formatted as FAT32.
In case one of the devices is the RG35XX OG the shared sdcard must be the second sdcard

You must follow a precise sequence:
1)  In case one of the devices is an RG35XX OG it must be the first to be installed, so follow the install process "RG35XX OG (2022-2023) Two SDCard method"
2)  now follow the install process for miyoomini
3)  now follow the install process for miyoomini plus
4)  now follow the install process for miyoo A30

!!!IMPORTANT NOTE!!!: Please not that every time You install/update a device it may delete some files needed by another device. 
When (if...) I'll move to a single setup file device independent I'll change this behavior.
Every time a device is installed/updated the .tmp_update folder is deleted and created again wih only the files needed by the device.
Currently the fix is a manual process, You must ensure that in the root of the sdcard should be present the folders "miyoo" and "miyoo354" that did You copy during installation process.
The hidden folder .tmp_update of the sdcard must contains the folders "my282" and "miyoomini" moreover the files "miyoomini.sh", "my282.sh" and "updater".

the devices will share bios, roms and saves folders.
Some saved state files may work across devices (i.e. doom), but not so many so don't expect support on that. If I'll move to a single setup file device independent I'll keep them separated per device.

The pico8 native binary files must be copied under the Tools/<devicename>/splore folder for each device. 
