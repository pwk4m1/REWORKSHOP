#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/Nyanix.kernel isodir/boot/Nyanix.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "Nyanix" {
	multiboot /boot/Nyanix.kernel
}
EOF
grub-mkrescue -o Nyanix.iso isodir
