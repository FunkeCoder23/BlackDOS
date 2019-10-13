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

   // if (cmd[0]=='b'&&cmd[1]=='o'&&cmd[2]=='o'&&cmd[3]=='t')
    if (strEql(cmd,"boot"))
    {
      interrupt(0x19,0,0,0,0);
    }
    else if (cmd =="clrs")
    {
      interrupt(0x21,12,10,20,0);
    }
    else if (cmd=="echo")
    {
      if(arg1[0]='\0')
      {
        interrupt(0x21,1,arg1,0,0);   //readString(arg1)
      }
      interrupt(0x21,0,arg1,0,0);
    }
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
