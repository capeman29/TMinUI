#!/bin/sh

TARGET=$1
mkdir -p /opt/m21-toolchain
if [ -d /opt/m21-toolchain/usr ]; then
	rm -fr /opt/m21-toolchain/usr
fi
cp -rf ~/buildroot/output/host/* /opt/m21-toolchain/
# this version of buildroot doesn't have relocate-sdk.sh yet so we bring our own
cd /opt/m21-toolchain
ln -s ./ usr

if [ -f ~/hwcap.h ]; then
    if [ "$TARGET" = "MUSL" ]; then
	cp ~/hwcap.h arm-buildroot-linux-musleabihf/sysroot/usr/include/asm/
    else
	cp ~/hwcap.h arm-buildroot-linux-gnueabihf/sysroot/usr/include/asm/
    fi
fi

cp ~/relocate-sdk.sh /opt/m21-toolchain/
cp ~/sdk-location /opt/m21-toolchain/
/opt/m21-toolchain/relocate-sdk.sh

#pack the toolchain for speed up next builds


# move the rootfs.img and tar.gz to workspace
mv ~/buildroot/output/images/rootfs.tar.gz  /opt/m21-toolchain/
mv ~/buildroot/output/images/rootfs.ext2  /opt/m21-toolchain/

cd /opt/
if [ "$TARGET" = "MUSL" ]; then
    tar -czvf m21_toolchain_musl.tar.gz m21-toolchain/
    printf "m21_toolchain_musl.tar.gz can be shared as a blob\nby placing in support before calling 'make shell'\n"
else
    tar -czvf m21_toolchain_glibc.tar.gz m21-toolchain/
    printf "m21_toolchain_glibc.tar.gz can be shared as a blob\nby placing in support before calling 'make shell'\n"
fi



