#include "blackdos.h"

void main()
{
  int i;//internal word iterator
  int j;//total string iterator
  char input[80];
  char cmd[80];
  char msg1[80];
  interrupt(0x21,12,10,20,0); //clear screen w/o changing colors
  interrupt(0x21,0,"Hello, Welcome to ShittyDOS\r\n",0,0);

  while(1)
  {
    i=0;
    j=0;
    cmd[0]="\0";
    interrupt(0x21,0,"^(~(oo)~)^: ",0,0);
    interrupt(0x21,1,input,0,0);   //readString(input)
    while(input[i]!=' '&& input[i]!='\0') //check for space or endline
    {
      //if(i=5)
      //{
      //  cmd[0]='X';
      //  break;
      //}
      cmd[i]=input[i]; //store cmd word
      i++;
    //  interrupt(0x21,0,cmd[i-1],0,0);
    //  j++;  //total string iterator
    }
    interrupt(0x21,0,cmd,0,0);
    interrupt(0x21,0,"\r\n");
    /*
    *input++;
    j=0;
    while(*input!=' ' || *input!='\0') //check for space or endline
    {
      msg1[j]=*input++; //store cmd word
      j++;
    }
    switch(cmd)
    {
      case "boot":
        interrupt(0x19,0,0,0,0);
        break;
      case "clrs":
        interrupt(0x21,12,10,20,0);
        break;
      case "echo":
        interrupt(0x21,0,msg1,0,0);
        break;
      default:
        interrupt(0x21,0,"Bad command, YA BASIC",0,0);
    }
    */
  }
}
