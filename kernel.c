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
void readInt(int);
void writeInt(int);

void main()
{
  char string[80];
  int n;
  makeInterrupt21();
  printLogo();
  interrupt(0x21,0,"Hello world from Matt Stran, Molly Kendrick, Aaron Tobias.\r\n\0",1,0);
  interrupt(0x21,0,"please type random nonsense, thx :)\r\n\0",0,0);
  interrupt(0x21,1,string,0,0);
  interrupt(0x21,0,"Your string is: ",0,0);
  interrupt(0x21,0,string,0,0);
  interrupt(0x21,0,"\r\n",0,0);
  interrupt(0x21,0,"Please type a number (0-32767)",0,0);
  readInt(n);
  writeInt(n);
  while(1);
}

void printString(char* c, int d)
{
  char al;
  int ax;
  while(*c)
  {
    al = *c++; 	/*get deref char, and then inc*/
    ax = 3584 + al;  /*ah*256+al*/
    if (d!=1) {
      interrupt(0x10, ax, 0, 0, 0);  /* display on screen*/
    }
    else {
      interrupt(0x17, al, 0,0,0); /*print out*/
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
    if(*in==13)
    {
      interrupt(0x10, 3584+10, 0, 0, 0);  /* newline*/
      interrupt(0x10, 3584+*in, 0, 0, 0);  /*Carriage Return*/
      break;
    }
    if(*in==8)
    {			/* backspace pressed*/
      interrupt(0x10, 3584+*in, 0, 0, 0);  /* delete character */
      interrupt(0x10, 3584+32, 0, 0, 0);  /* overwrite with space*/
      interrupt(0x10, 3584+*in, 0, 0, 0);  /* delete space*/
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
  int num, sum=0;      /*int to return*/
  char *nstring[5];
  char nchar; /*char array to store number*/
  readString(nstring); /*get num from user*/
  while(*nstring)
  {
    nchar = *nstring; 	/*get deref number, and then inc*/
    *nstring=*nstring+1;
    num=nchar-'0';
    sum*=10;            //move digits left
    sum+=num;           //add new ones digit
  }
  n=sum;
  return;
}

void writeInt(int num)
{
  int i=0;
  char nstring[5];
  while (num)
  {
    nstring[i++]=(char) (mod(num,10)+'0');
    num=div(num,10);
  }
  interrupt(0x21,0,nstring,0,0);
}


int mod(int a, int b)
{
  int x=a;
  while (x>=b)
  {
    x=x-b;
  }
  return x;
}

int div(int a, int b)
{
  int q=0;
  while(q*b<=a)
  {
    ++q;
  }
  return(q-1);
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
/*case 2: case 3: case 4: case 5: */
/*      case 6: case 7: case 8: case 9: case 10: */
/*      case 11: case 12: case 13: case 14: case 15: */
    default:
      printString("General BlackDOS error.\r\n\0");
  }
}
