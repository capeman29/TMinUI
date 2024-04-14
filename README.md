# MyMinUI

MyMinUI is a fork of the latest MinUI, I like MinUI but I also like playing old arcade coin up (thanks to FinUI) and DOOM which were missing so I added them. 
A missing feature when using MinUI with arcades is that while in the official MinUI's cores usually the name of the rom is enough to identify a game with arcade the rom naming is quit difficult to decode so boxarts are nearly mandatory to properly identifying a game, that's why I spent a lot of time adding boxarts.
I'm a player that uses a lot savestates, I really can't understand why almost all firmwares available in the retrogaming do not provide a way to select a specific slot with a graphical preview, when I saw for the first time the in game menu of MinUI I immediately felt that that was the way, then I added the minarch code to minui.   


Features from FinUI:
- Add Favorites Collections (Press SELECT to toggle a rom)
- Clear "Recently Played"
- Additional emulators (MAME2003-PLUS)
- Base and Extras are merged into one Full release

New features of MyMinUI (RG35XX and MiyooMiniplus only):
- added Retroarch 1.14 as alternative libretro frontend for cores it has the same video filters available on garlicos (WIP).
- added prboom libretro core (Doom), it works only with retroarch as libretro frontend
- added puae2021 libretro core (Amiga), not really tested, expect issues, please report
- added FinalBurnNeo libretro core, it works surprisingly well on some arcade game which are slow on other OS, use an FBNeo romset as many 0.78 roms (mame2003+) don't work well.
- added Overclock Max profile (1.5GHz on rg35xx and 1.8GHz on miyoominiplus)
- replaced dinguxcommander with the garlicos version (source rg35xx.com) which has more features
- the power button now performs a shutdown as garlicos 1.4.9 does instead of standby, to restore the MinUI sleep mode behavior just create the file enable-sleep-mode in the folder /mnt/sdcard/.userdata/shared
- to use retroarch instead of minarch just copy to the ROMS/Extras/Emus/xxxx.pak the launch.sh from ROMS/Extras/Emus/Doom.pak then set the right core name and the cpu speed required.
- added retroarch as Tools
- added the main menu mode selector to version page, press up/down to change the mode then exit the page to get the new mode activated
  Three modes are implemented:
  1) STANDARD  -> this is the standard MinUI interface
  2) SIMPLE -> same as STANDARD with Tools and Settings items hidden
  3) FANCY -> it changes the look of the main menu showing boxarts and save state window selector if present.
      Boxarts must be png 640x480 (same garlic os format) and saved in the "Imgs" folder on each Roms folder. it is suggested to leave the left side of the image dark for better user experience
      it is allowed adding boxarts also for systems not only roms, just add the image named as the folder.
        i.e. if the rom folder is "Doom (DOOM)" then create a png called "Doom (DOOM).png" in the "Doom (DOOM)/Imgs" folder
      If saves are present in the selected rom the same state selector available in the in game menu (IMHO that is a MinUI awesome feature), the latest save is automatically selected, press X to load it, if x is pressed whiel an empty slot is selected the game starts without recalling state. save state selector is available ONLY for cores running Minarch.
      In fancy mode You can read the current folder in the top left corner of the display, while scrolling the recent or favorite lists it shows the folder of the currently selected game. 

Some changes under the hood:
- reduced footprint of the docker toolchain from 4.5GB down to 1.5GB.
- various improvements on makefiles
- the release files are separated and dedicated for each platform (WIP)
- all cores moved to the same system directory as BASE cores (which should be better for retroarch)
- all core launchers moved to SDCARD/Emus folders as EXTRAS


Install process on RG35XX:
flash an sdcard with the TF1.img (please follow official MinUI instructions) then unzip the rg35xx release file in the root.
Don't forget to copy the file dmenu.bin in the misc directory.

Install process on Miyoo Mini Plus:
format an sdcard in Fat32 then unzip the content of the miyoo mini release file in the root of the sdcard.

Upgrade process (both devices):
Even if theorically updating an existing MinUI or FinUI would be possible it is recommended to install MyMinUI from scratch.
To update a previous MyMinUI sdcard just copy the file MinUI.zip file in the root of the sdcard then reboot the device.
It is usually not needed unzipping the whole release file as if not made carefully You would lose existing roms/bios/saves, etc... in doubt choose merge instead of replace folders.

# MinUI

MinUI is a focused, custom launcher and libretro frontend for the RGB30, M17 (early revs), Trimui Smart (and Pro), Miyoo Mini (and Plus), and Anbernic RG35XX (and Plus).

<img src="github/minui-main.png" width=320 /> <img src="github/minui-menu-gbc.png" width=320 />  
See [more screenshots](github/).

## Features

- Simple launcher, simple SD card
- No settings or configuration
- No boxart, themes, or distractions
- Automatically hides hidden files
  and extension and region/version 
  cruft in display names
- Consistent in-emulator menu with
  quick access to save states, disc
  changing, and emulator options
- Automatically sleeps after 30 seconds 
  or press POWER to sleep (and wake)
- Automatically powers off while asleep
  after two minutes or hold POWER for
  one second
- Automatically resumes right where
  you left off if powered off while
  in-game, manually or while asleep
- Resume from manually created, last 
  used save state by pressing X in 
  the launcher instead of A
- Streamlined emulator frontend 
  (minarch + libretro cores)
- Single SD card compatible with
  multiple devices from different
  manufacturers

You can [grab the latest version here](https://github.com/shauninman/MinUI/releases).

> Devices with a physical power switch
> use MENU to sleep and wake instead of
> POWER. Once asleep the device can safely
> be powered off manually with the switch.

## Supported consoles

Base:

- Game Boy
- Game Boy Color
- Game Boy Advance
- Nintendo Entertainment System
- Super Nintendo Entertainment System
- Sega Genesis
- PlayStation

Extras:

- Neo Geo Pocket (and Color)
- Pico-8
- Pokémon mini
- Sega Game Gear
- Sega Master System
- Super Game Boy
- TurboGrafx-16 (and TurboGrafx-CD)
- Virtual Boy


## Legacy versions

The original Trimui Model S version of MinUI has been archived [here](https://github.com/shauninman/MinUI-Legacy-Trimui-Model-S).

The sequel, MiniUI for the Miyoo Mini, has been archived [here](https://github.com/shauninman/MiniUI-Legacy-Miyoo-Mini).

The return of MinUI for the Anbernic RG35XX has been archived [here](https://github.com/shauninman/MinUI-Legacy-RG35XX).