#!/bin/sh

TARGET=$1
cd /opt/
if [ "$TARGET" = "MUSL" ]; then
    tar -czvf m21_toolchain_musl.tar.gz m21-toolchain/
else
    tar -czvf m21_toolchain_glibc.tar.gz m21-toolchain/
fi
rm -rf /opt/m21-toolchain/rootfs.ext2
rm -rf /opt/m21-toolchain/rootfs.tar.gz


printf "m21_toolchain.tar.gz can be shared as a blob\nby placing in support before calling 'make shell'\n"