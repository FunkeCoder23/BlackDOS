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
echo "copy diskmap file to bootdisk"
dd if=map of=floppya.img bs=512 count=1 seek=256 conv=notrunc
echo "copy config file to bootdisk"
dd if=config of=floppya.img bs=512 count=1 seek=258 conv=notrunc

echo "compiling shell"
bcc -ansi -c -o Shell.o Shell.c
echo "linking shell"
ld86 -o Shell -d Shell.o basm.o
echo "copy shell to bootdisk"
dd if=Shell of=floppya.img bs=512 count=11 conv=notrunc seek=30

echo "compiling ddir"
bcc -ansi -c -o ddir.o ddir.c
echo "linking ddir"
ld86 -o ddir -d ddir.o basm.o

echo "compiling lab7"
bcc -ansi -c -o lab7.o lab7.c
echo "linking lab7"
ld86 -o lab7 -d lab7.o basm.o

./loadFile Help
./loadFile Shell
./loadFile Stenv
./loadFile fib
./loadFile msg
./loadFile kitty1
./loadFile ddir
./loadFile kitty2
./loadFile lab7
./loadFile fpc02
