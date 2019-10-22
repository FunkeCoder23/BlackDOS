/* ACADEMIC INTEGRITY PLEDGE                                              */
/*                                                                        */
/* - I have not used source code obtained from another student nor        */
/*   any other unauthorized source, either modified or unmodified.        */
/*                                                                        */
/* - All source code and documentation used in my program is either       */
/*   my original work or was derived by me from the source code           */
/*   published in the textbook for this course or presented in            */
/*   class.                                                               */
/*                                                                        */
/* - I have not discussed coding details about this project with          */
/*   anyone other than my instructor. I understand that I may discuss     */
/*   the concepts of this program with other students and that another    */
/*   student may help me debug my program so long as neither of us        */
/*   writes anything during the discussion or modifies any computer       */
/*   file during the discussion.                                          */
/*                                                                        */
/* - I have violated neither the spirit nor letter of these restrictions. */
/*                                                                        */
/*                                                                        */
/*                                                                        */
/* Signed: Molly Kendrick, Aaron Tobias, Matt Stran,  Date:9/10/19        */
/*                                                                        */
/*                                                                        */
/* 3460:4/526 BlackDOS2020 kernel, Version 1.03, Fall 2019.               */

void handleInterrupt21(int,int,int,int);
void printLogo();
void readSectors(char, int, int);
void runProgram(char, int);
void readFile(char, char, int);

void main()
{

 char buffer[512];
 makeInterrupt21();
 interrupt(33,2,buffer,258,1);
 interrupt(33,12,buffer[0]+1,buffer[1]+1,0);
 printLogo();
 interrupt(33,4,"Shell\0",2,0);
 interrupt(33,0,"Bad or missing command interpreter.\r\n\0",0,0);

 while (1) ;



}



void printString(char* c, int d)
{
  char al;
  int ax;
  while(*c)
  {
    al = *c++; 	/*get deref char, and then inc*/
    ax = 3584 + al;  /*ah*256+al*/
    if (d)
    {
      interrupt(0x17, al, 0,0,0); /*print out*/
    }
    else
    {
      interrupt(0x10, ax, 0, 0, 0);  /* display on screen*/
    }
  }
  return;
}


void printLogo()
{
  interrupt(0x21,0,"       ___   `._   ____  _            _    _____   ____   _____ \r\n\0",0,0);
  interrupt(0x21,0,"      /   \\__/__> |  _ \\| |          | |  |  __ \\ / __ \\ / ____|\r\n\0",0,0);
  interrupt(0x21,0,"     /_  \\  _/    | |_) | | __ _  ___| | _| |  | | |  | | (___ \r\n\0",0,0);
  interrupt(0x21,0,"    // \\ /./      |  _ <| |/ _` |/ __| |/ / |  | | |  | |\\___ \\ \r\n\0",0,0);
  interrupt(0x21,0,"   //   \\\\        | |_) | | (_| | (__|   <| |__| | |__| |____) |\r\n\0",0,0);
  interrupt(0x21,0,"._/'     `\\.      |____/|_|\\__,_|\\___|_|\\_\\_____/ \\____/|_____/\r\n\0",0,0);
  interrupt(0x21,0," BlackDOS2020 v. 1.03, c. 2019. Based on a project by M. Black. \r\n\0",0,0);
  interrupt(0x21,0," Author(s): Aaron Tobias, Matt Stran, Molly Kendrick.\r\n\r\n\0",0,0);
}

/* MAKE FUTURE UPDATES HERE */
/* VVVVVVVVVVVVVVVVVVVVVVVV */

void readString(char* c)
{
  int i=0;
  char* in;
  do{
    *in =interrupt(0x16,0,0,0,0); /*read in character*/
    if(*in==13)                            //Enter pressed
    {
      interrupt(0x10, 3584+10, 0, 0, 0);  /* newline*/ //3584 = (ax=14)*256
      interrupt(0x10, 3584+*in, 0, 0, 0);  /*Carriage Return*/
      break;
    }
    if(*in==8)
    {			                     /* backspace pressed*/
      interrupt(0x10, 3584+*in, 0, 0, 0);  /* delete character */
      interrupt(0x10, 3584+32, 0, 0, 0);  /* overwrite with space*/
      interrupt(0x10, 3584+*in, 5,0, 0, 0);  /* delete space*/
      if(i>0) {
       --i;				/*dec iter*/
      }
    }
    else
    {
      interrupt(0x10,3584+*in,0,0,0);    /*display character*/
      c[i]=*in;
      ++i;                                      /*next character location*/
    }
  } while(1); 		/*enter pressed*/
  c[i]=0x0;					/*add null terminator*/
  return;
}

void readInt(int* n)
{
  int num = 0, i=0;
  char nstring[6]; //5 digits and NUL

  interrupt(0x21,1,nstring,0,0);
  while(nstring[i]!='\0')  //until end of string
  {
    num *= 10;				//move digit left
    num += (nstring[i++]-'0');  //read in LSD
  }
  *n = num;                 //return num
  return;
}

void writeInt(int num, int d)
{
  int i=0, j=0;
  char nstring[6], revstring[6];//5 digits and NUL
  if (!num)                         //if 0
  {
    nstring[0]='0';
    nstring[1]='\0';				//print 0 and NUL
  }
  else
  {
    while (num)
    {
      revstring[i++]=(char) (mod(num,10)+'0');  //store LSD
      num=div(num,10);                          //new LSD
    } 				                            //stores number in reverse order
    while(i-- > 0)
    {
      nstring[j++]=revstring[i];     //reverses (reversed) number
    }
    nstring[j]='\0';
  }
  interrupt(0x21,0,nstring,d,0); //print number
  return;
}


int mod(int n, int d)
{
  int q=div(n,d);
  int r=n-(q*d);
  return r;
}

int div(int n, int d)
{
  int q=0;
  while(n>=d)
  {
    n-=d;
    ++q;
  }
  return q;
}

void readSectors(char *buffer, int sector, int sectorCount)
{
  int relSecNo = mod(sector, 18) + 1;
  int headNo = mod( (div(sector, 18)), 2);
  int trackNo = div(sector, 36);
  int AX = 512 + sectorCount;
  int CX = trackNo * 256 +relSecNo;
  int DX = headNo * 256;

  interrupt(0x13, AX, buffer, CX, DX);
}

void writeSectors(char *buffer, int sector, int sectorCount)
{
  int relSecNo = mod(sector, 18) + 1;
  int headNo = mod( (div(sector, 18)), 2);
  int trackNo = div(sector, 36);
  int AX = 768 + sectorCount;
  int CX = trackNo * 256 +relSecNo;
  int DX = headNo * 256;

  interrupt(0x13, AX, buffer, CX, DX);
}

void clearScreen(int bg, int fg)
{
  int i;
  for (i = 0; i < 24; ++i)
  {
    interrupt(0x10, 3584+13, 0, 0, 0);    //24 carriage returns
    interrupt(0x10, 3584+10, 0, 0, 0);    //24 newlines
  }

  interrupt(0x10, 512, 0, 0, 0);
  if ((bg > 8) || (fg > 16))
  {
    return;
  }

  if ((bg > 0) && (fg > 0))
  {
    interrupt(0x10, 1536, 4096 * (bg - 1) + 256 * (fg -1), 0, 6223);
  }

}

void runProgram(char* name, int segment)
{
  int i, segLoc;
  char buffer[13312];  //Big char array
  readFile(name,buffer,segment);
  segLoc = segment * 4096; //segment * 0x1000 = base location of seg
  for (i = 0; i < 13311; ++i) //transfer 13312 bytes to memory
  {
    putInMemory(segLoc, i, buffer[i]);//transfer byte i from buffer to memory
  }
  launchProgram(segLoc);

}

int strEql(char s1[], char s2[])
{
  int i;
  for(i=0;i>-1;i++)
  {
    if(s1[i] != s2[i]) return 0;
    else if(s1[i] == '\0' && s2[i] == '\0') return 1;
  }
  return 1;
}

void stop() { launchProgram(8192); }

void readFile(char* fname, char* buffer, int* size)
{
  char dir[512];
  char map[512];
  int i;
  interrupt(0x21,2,dir,257,1); //load disk dir into dir
  for(i=0;i<512;i+=16)
  {
    if(strEql(&dir[i],fname))
    {
      size=dir[i+9];
      interrupt(0x21,2,buffer,dir[i+8],dir[i+9]);//file found, load into buffer
      return;
    }
  }
  interrupt(0x21,15,0,0,0);  //call error 0
}

void error(int bx)
{
   switch (bx) {
	   case 0:
	   /* error 0 = "File not found." */
	   interrupt(16, 3654, 0, 0, 0); interrupt(16, 3689, 0, 0, 0); interrupt(16, 3692, 0, 0, 0);
	   interrupt(16, 3685, 0, 0, 0); interrupt(16, 3616, 0, 0, 0); interrupt(16, 3694, 0, 0, 0);
	   interrupt(16, 3695, 0, 0, 0); interrupt(16, 3700, 0, 0, 0); interrupt(16, 3616, 0, 0, 0);
	   interrupt(16, 3686, 0, 0, 0); interrupt(16, 3695, 0, 0, 0); interrupt(16, 3701, 0, 0, 0);
	   interrupt(16, 3694, 0, 0, 0); interrupt(16, 3684, 0, 0, 0);
	   break;
	   case 1:
	   /* error 1 = "Bad file name." */
	   interrupt(16, 3650, 0, 0, 0); interrupt(16, 3681, 0, 0, 0); interrupt(16, 3684, 0, 0, 0);
	   interrupt(16, 3616, 0, 0, 0); interrupt(16, 3686, 0, 0, 0); interrupt(16, 3689, 0, 0, 0);
	   interrupt(16, 3692, 0, 0, 0); interrupt(16, 3685, 0, 0, 0); interrupt(16, 3616, 0, 0, 0);
	   interrupt(16, 3694, 0, 0, 0); interrupt(16, 3681, 0, 0, 0); interrupt(16, 3693, 0, 0, 0);
	   interrupt(16, 3685, 0, 0, 0);
	   break;
	   case 2:
	   /* error 2 = "Disk full." */
	   interrupt(16, 3652, 0, 0, 0); interrupt(16, 3689, 0, 0, 0); interrupt(16, 3699, 0, 0, 0);
	   interrupt(16, 3691, 0, 0, 0); interrupt(16, 3616, 0, 0, 0); interrupt(16, 3686, 0, 0, 0);
	   interrupt(16, 3701, 0, 0, 0); interrupt(16, 3692, 0, 0, 0); interrupt(16, 3692, 0, 0, 0);
	   break;
	   default:
	   /* default = "General error." */
	   interrupt(16, 3655, 0, 0, 0); interrupt(16, 3685, 0, 0, 0); interrupt(16, 3694, 0, 0, 0);
	   interrupt(16, 3685, 0, 0, 0); interrupt(16, 3698, 0, 0, 0); interrupt(16, 3681, 0, 0, 0);
	   interrupt(16, 3692, 0, 0, 0); interrupt(16, 3616, 0, 0, 0); interrupt(16, 3685, 0, 0, 0);
	   interrupt(16, 3698, 0, 0, 0); interrupt(16, 3698, 0, 0, 0); interrupt(16, 3695, 0, 0, 0);
	   interrupt(16, 3698, 0, 0, 0);
   }
   interrupt(16, 3630, 0, 0, 0); interrupt(16, 3597, 0, 0, 0); interrupt(16, 3594, 0, 0, 0);
   interrupt(33, 5, 0, 0, 0);
}


/* ^^^^^^^^^^^^^^^^^^^^^^^^ */
/* MAKE FUTURE UPDATES HERE */

void handleInterrupt21(int ax, int bx, int cx, int dx)
{
  switch(ax)
  {
    case 0:
      printString(bx,cx);
      break;
    case 1:
      readString(bx);
      break;
    case 2:
      readSectors(bx,cx,dx);
      break;
    case 3:
      readFile(bx,cx,dx);
      break;
    case 4:
      runProgram(bx,cx);
      break;
    case 5:
      stop();
      break;
    case 6:
      writeSectors(bx,cx,dx);
      break;
      /*case 7: case 8: case 9: case 10: */
/*      case 11: */
    case 12:
      clearScreen(bx, cx);
      break;
    case 13:
      writeInt(bx,cx);
      break;
    case 14:
      readInt(bx);
      break;
    case 15:
      error(bx);
      break;
    default:
      error(3);
  }
}
