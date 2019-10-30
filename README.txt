Wrote compileOS.sh which compiles and links the bootloader and kernel, can be tested by either double clicking, or (preferably) running in terminal with ./compileOS.sh

Wrote a function printString that accepts a c-string and an integer.
The integer's value determined whether the c-string was printed or displayed to the screen.
We then changed the printString function to an interrupt call.
This can be tested by changing cx in the interrupt call .
i.e,    interrupt(33,0,"Print to screen\0",0,0);
	interrupt(33,0,"Print to printer\0",1,0);

Added readString(char*)
takes input from console and stores in character array
interrupt(33,1,cstring,0,0);

Added writeInt(int)
takes a number, converts into a char array and prints to screen or printer
interrupt(33,1,2019,0,0);

Added readInt(*int)
invokes readString, stores string (backwards), reverses string, and then converts to an int
interrupt(33,1,&num,0,0);

Added readSectors(char*, int, int)
takes an absolute sector, the total number of sectors to be read, and stores it in the character array
interrupt(0x21, 2, buffer, 258, 1);

Added writeSectors(char*, int, int)
takes an absolute sector, the total number of sectors to be written, and stores it on the disk
interrupt(0x21, 6, buffer, 258, 1);

Added clearScreen(int, int)
takes two ints, one for the foreground and one for the background and changes the colors and clears the screen
interrupt(0x21, 12, buffer[0] + 1, buffer[1] + 1, 0);

Added runProgram(int, int, int)
takes the starting sector of a program on disk, reads the sectors into a buffer
then transfers the buffer into memory (putInMemory) at the segment*4096(base segment location)
then calls launchProgram to start execution
runProgram(30,1,2); //runs program stored in sector 30 of length 1 sector, stores in segment 2

Added stop()
infinite loop
interrupt(0x21,5,0,0,0);


Added Shell.c
-> added parser to take input and parse into cmd, arg1, arg2
-> compares cmd to available commands
-> if missing arg1 or 2, prompts to enter
to test:
run kernel, wait for shell prompt, type commands: exec, senv, boot, clrs, prnt, echo,...

Added help.c
Displays a simple help manual that lists and describes the various shell commands 
that have been implemented. Implemented commands include: boot, clrs, echo, ddir,
exec, help, prnt, senv, and show.