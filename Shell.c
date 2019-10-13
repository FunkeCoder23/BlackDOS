#include "blackdos.h"

void main()
{
  int i;//internal word iterator
  int j;//total string iterator
  char input[80];
  int args=0;
  char cmd[80];
  char arg1[80];
  char arg2[80];
  interrupt(0x21,12,10,20,0); //clear screen w/o changing colors
  interrupt(0x21,0,"=========================\r\n\0",0,0);
  interrupt(0x21,0,"Welcome to BlackDOS Shell\r\n\0",0,0);
  interrupt(0x21,0,"=========================\r\n\0",0,0);

  cmdinput:
  while(1)
  {
    args=0;
    for(i=0;i<80;++i)
    {
      input[i]='\0';  //clear input buffer
      cmd[i]='\0';  //clear cmd buffer
      arg1[i]='\0';  //clear arg1 buffer
      arg2[i]='\0';  //clear arg2 buffer
    }

    i=0;
    j=0;

    interrupt(0x21,0,"^(~(oo)~)^: \0",0,0);
    interrupt(0x21,1,input,0,0);   //readString(input)

    while(input[j]!=' ' && j<79) //check for space or endline
    {

    if(input[j]=='\0')  //if reaches NUL, only one arg
    {
        args=1;
        break;
    }

    cmd[i++]=input[j++]; //store cmd word
   }

    if(i!=4)
    {
      interrupt(0x21,0,"Command not found\r\n",0,0); //non-4-letter cmd
      goto cmdinput; //grab new input
    }
    cmd[i]='\0'; //terminate cmd

    while(input[++j]==' '); //skip spaces

    i=0; //reset internal iter
    while(input[j]!=' ' && j<79 && args==0) //check for space or endline
    {
      if(input[j]=='\0')  //if reaches NUL, only two args
      {
        args=2;
        break;
      }
      arg1[i]=input[j]; //store cmd word
      i++;  //inc cmd iter
      j++;  //inc string iterator
    }
    arg1[i]='\0'; //terminate arg1;

    while(input[++j]==' '); //skip spaces

    i=0; //reset internal iter
    while(input[j]!=' ' && j<80  && args==0) //check for space or endline
    {
      if(input[j]=='\0')
      {
        args=3;
      }
      arg2[i]=input[j]; //store cmd word
      i++;  //inc cmd iter
      j++;  //inc string iterator
    }

    if (cmd[0]=='b'&&cmd[1]=='o'&&cmd[2]=='o'&&cmd[3]=='t')
    {
      interrupt(0x19,0,0,0,0);
    }//boot
    else if (cmd[0]=='c'&&cmd[1]=='l'&&cmd[2]=='r'&&cmd[3]=='s')
    {
      interrupt(0x21,12,10,20,0);
    }//clrs
    else if (cmd[0]=='e'&&cmd[1]=='c'&&cmd[2]=='h'&&cmd[3]=='o')
    {
      if(args==1)
      {
        interrupt(0x21,0,"Please enter the message to echo: \r\n",0,0);
        interrupt(0x21,1,arg1,0,0);   //readString(arg1)
      }
      interrupt(0x21,0,arg1,0,0);
    }//echo
    else if (cmd[0]=='c'&&cmd[1]=='o'&&cmd[2]=='p'&&cmd[3]=='y')
    {
      if(args==1)
      {
        interrupt(0x21,0,"Enter file source: \r\n",0,0);
        interrupt(0x21,1,arg1,0,0);
        args=2;
      }
      if(args==2)
      {
        interrupt(0x21,0,"Enter file destination: \r\n",0,0);
        interrupt(0x21,1,arg2,0,0);
      }
      interrupt(0x21,cmd,0,0);
      interrupt(0x21,arg1,0,0);
      interrupt(0x21,arg2,0,0);
    }//copy
    else if (cmd[0]=='d'&&cmd[1]=='d'&&cmd[2]=='i'&&cmd[3]=='r')
    {
      interrupt(0x21,cmd,0,0);
    }//ddir
    else if (cmd[0]=='e'&&cmd[1]=='x'&&cmd[2]=='e'&&cmd[3]=='o')
    {
      if(args==1)
      {
        interrupt(0x21,0,"Enter file to execute: \r\n",0,0);
        interrupt(0x21,1,arg1,0,0);
        args=2;
      }
      interrupt(0x21,cmd,0,0);
    }//exec
    else if (cmd[0]=='h'&&cmd[1]=='e'&&cmd[2]=='l'&&cmd[3]=='p')
    {
      interrupt(0x21,cmd,0,0);
    }//help
    else if (cmd[0]=='p'&&cmd[1]=='r'&&cmd[2]=='n'&&cmd[3]=='t')
    {
      if(args==1)
      {
      interrupt(0x21,0,"Enter file to print: \r\n",0,0);
      interrupt(0x21,1,arg1,0,0);
      args=2;
      }
      interrupt(0x21,cmd,0,0);
    }//prnt
    else if (cmd[0]=='r'&&cmd[1]=='e'&&cmd[2]=='m'&&cmd[3]=='v')
    {
      if(args==1)
      {
        interrupt(0x21,0,"Enter file to remove: \r\n",0,0);
        interrupt(0x21,1,arg1,0,0);
        args=2;
      }
      interrupt(0x21,cmd,0,0);
    }//remv
    else if (cmd[0]=='s'&&cmd[1]=='e'&&cmd[2]=='n'&&cmd[3]=='v')
    {
      interrupt(0x21,cmd,0,0);
    }//senv
    else if (cmd[0]=='s'&&cmd[1]=='h'&&cmd[2]=='o'&&cmd[3]=='w')
    {
      if(args==1)
      {
        interrupt(0x21,0,"Enter file to show: \r\n",0,0);
        interrupt(0x21,1,arg1,0,0);
        args=2;
      }
      interrupt(0x21,cmd,0,0);
    }//show
    else if (cmd[0]=='t'&&cmd[1]=='w'&&cmd[2]=='e'&&cmd[3]=='t')
    {
      if(args==1)
      {
        interrupt(0x21,0,"Enter file to twet: \r\n",0,0);
        interrupt(0x21,1,arg1,0,0);
        args=2;
      }
      interrupt(0x21,cmd,0,0);
    }//twet
    else
    {
      interrupt(0x21,0,"Bad command, YA BASIC\r\n",0,0);
    }
  }//cmdinput
}

int strEql(char s1[], char s2[])
{
  int i;
  for(i=0;1;i++)
  {
    if(s1[i] != s2[i]) return 0;
    if(s1[i] == '\0' && s2[i] != '\0') return 0;
    if(s1[i] != '\0' && s2[i] == '\0') return 0;
  }
  return 1;
}
