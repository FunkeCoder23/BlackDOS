#include "blackdos.h"

int strEql(char[],char[]);

void main()
{
  int i;//internal word iterator
  int j;//total string iterator
  int size;
  char input[80];
  int args=0;
  char cmd[80];
  char arg1[80];
  char arg2[80];
  char msg[80];
  char buffer[512];
  char text[140];
  char fileBuff[13312];
  //interrupt(0x21,12,10,20,0); //clear screen w/o changing colors
  interrupt(0x21,0,"=========================\r\n\0",0,0);
  interrupt(0x21,0,"Welcome to BlackDOS Shell\r\n\0",0,0);
  interrupt(0x21,0,"=========================\r\n\0",0,0);

  cmdinput:
  while(1)
  {
    args=0;
    for(i=0;i<512;++i)
    {
      buffer[i]=0; //clear buffer
    }
    for(i=0;i<80;++i)
    {
      input[i]='\0';  //clear input buffer
      cmd[i]='\0';  //clear cmd buffer
      arg1[i]='\0';  //clear arg1 buffer
      arg2[i]='\0';  //clear arg2 buffer
      msg[i]='\0';  //clear msg buffer
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
      interrupt(0x21,0,"Command not found.\r\n",0,0); //non-4-letter cmd
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
      arg1[i]=input[j]; //store arg1 word
      i++;  //inc arg1 iter
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
      arg2[i]=input[j]; //store arg2 word
      i++;  //inc arg2 iter
      j++;  //inc string iterator
    }

    if (strEql(cmd,"boot"))
    {
      interrupt(0x19,0,0,0,0);
    }//boot
    else if (strEql(cmd,"clrs"))
    {
      interrupt(0x21,12,10,20,0);
    }//clrs
    else if (strEql(cmd,"echo"))
    {
      if(args==1)
      {
        interrupt(0x21,0,"Please enter the message to echo: \r\n",0,0);
        interrupt(0x21,1,msg,0,0);   //readString(arg1)
      }
      else
      {
        for(i=4;input[i]!='\0';i++)
        {
          msg[i-4]=input[i]; //print msg with spaces
        }
        msg[i]='\0';
      }
      interrupt(0x21,0,msg,0,0);
      interrupt(0x21,0,"\r\n",0,0);
    }//echo
    else if (strEql(cmd,"copy"))
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
      interrupt(0x21,3,arg1,fileBuff,&size);
      interrupt(0x21,8,arg2,fileBuff,size);
    }//copy
    else if (strEql(cmd,"ddir"))
    {
      interrupt(0x21,4,"ddir\0",4,0);
    }//ddir
    else if (strEql(cmd,"exec"))
    {
      if(args==1)
      {
        interrupt(0x21,0,"Enter file to execute: \r\n",0,0);
        interrupt(0x21,1,arg1,0,0);
        args=2;
      }
      interrupt(0x21,4,arg1,4,0);
    }//exec
    else if (strEql(cmd,"help"))
    {
      interrupt(0x21,4,"Help\0",4,0);
    }//help
    else if (strEql(cmd,"prnt"))
    {
      if(args==1)
      {
      interrupt(0x21,0,"Enter file to print: \r\n",0,0);
      interrupt(0x21,1,arg1,0,0);
      args=2;
      }
      interrupt(0x21,3,arg1,buffer,&size);
      interrupt(0x21,0,buffer,0,0);

    }//prnt
    else if (strEql(cmd,"remv"))
    {
      if(args==1)
      {
        interrupt(0x21,0,"Enter file to remove: \r\n",0,0);
        interrupt(0x21,1,arg1,0,0);
        args=2;
      }
      interrupt(0x21,7,arg1,0,0);
    }//remv
    else if (strEql(cmd,"senv"))
    {
      interrupt(0x21,4,"Stenv\0",4,0);
    }//senv
    else if (strEql(cmd,"show"))
    {
      if(args==1)
      {
        interrupt(0x21,0,"Enter file to show: \r\n",0,0);
        interrupt(0x21,1,arg1,0,0);
        args=2;
      }
      interrupt(0x21,3,arg1,buffer,&size);
      interrupt(0x21,0,buffer,0,1);
      interrupt(0x21,0,"\r\n",0,0);
    }//show
    else if (strEql(cmd,"twet"))
    {
      if(args==1)
      {
        interrupt(0x21,0,"Enter file to save tweet: \r\n",0,0);
        interrupt(0x21,1,arg1,0,0);
        args=2;
      }
      interrupt(0x21,0,"Tweet Here: (140 chars or less)\r\n",0,0);
      interrupt(0x21,1,text,0,0);
      text[139]=0;
      interrupt(0x21,8,arg1,text,1);
    }//twet
    else
    {
      interrupt(0x21,0,"Command not recognized. \r\n",0,0);
    }
  }//cmdinput
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
