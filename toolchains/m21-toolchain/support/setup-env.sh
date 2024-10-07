export PATH="/opt/m21-toolchain/bin:${PATH}:/opt/m21-toolchain/arm-buildroot-linux-${MY_SYS}eabihf/sysroot/usr/bin"
export CROSS_COMPILE=/opt/m21-toolchain/bin/arm-buildroot-linux-${MY_SYS}eabihf-
export PREFIX=/opt/m21-toolchain/arm-buildroot-linux-${MY_SYS}eabihf/sysroot/usr
export UNION_PLATFORM=m21
export MYARCH="-marm -mtune=cortex-a7 -mfpu=neon -mfloat-abi=hard -march=armv7ve"
export LD_LIBRARY_PATH=/opt/m21-toolchain/lib