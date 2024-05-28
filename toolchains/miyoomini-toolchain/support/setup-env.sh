export PATH="/opt/miyoomini-toolchain/usr/bin:${PATH}:/opt/miyoomini-toolchain/usr/arm-linux-gnueabihf/sysroot/bin"
export CROSS_COMPILE=/opt/miyoomini-toolchain/usr/bin/arm-linux-gnueabihf-
export PREFIX=/opt/miyoomini-toolchain/usr/arm-linux-gnueabihf/sysroot/usr
export UNION_PLATFORM=miyoomini
export MYARCH="-marm -mtune=cortex-a7 -mfpu=neon-vfpv4 -mfloat-abi=hard -march=armv7ve"