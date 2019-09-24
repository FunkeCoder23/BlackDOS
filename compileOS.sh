clear
echo "zeroing bootdisk"
dd if=/dev/zero of=floppya.img bs=512 count=2880
echo "copying bootloader"
dd if=bootload of=floppya.img bs=512 count=1 conv=notrunc
echo "compiling kernel"
bcc -ansi -c -o kernel.o kernel.c
echo "converting kernel to asm"
as86 kernel.asm -o kasm.o
echo "linking kernel"
ld86 -o kernel -d kernel.o kasm.o
echo "copy kernel to bootdisk"
dd if=kernel of=floppya.img bs=512 conv=notrunc seek=259
dd if=msg of=floppya.img bs=512 count=1 seek=30 conv=notrunc
