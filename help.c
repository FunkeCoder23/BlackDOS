char* readText(char* );


void main()
{
  int line=0;
  int page=0;
  char *c; //continue char
  char* helpText[80]; //helpText buffer


  helpText[0]= "NAME\r\n";
  helpText[1]= "\thelp - a help manual describing how to use BlackDOS and the BlackDOS shell.\r\n";
  helpText[2]= "DESCRIPTION\r\n";
  helpText[3]= "\thelp is a manual that describes and lists the functions and commands\r\n";
  helpText[4]= "\tthat are currently implemented into the OS.\r\n";
  helpText[5]= "COMMANDS\r\n";
  helpText[6]= "\tboot - reboot the system by calling interrupt(25,0,0,0,0) to reload\r\n";
  helpText[7]= "\tand restart the operating system\r\n";
  helpText[8]= "\r\n";
  helpText[9]= "\tclrs - clear the screen by issuing interrupt 0x21/12\r\n";
  helpText[10]= "\r\n";
  helpText[11]= "\techo comment - display comment on screen followed by a new line.\r\n";
  helpText[12]= "\tif no argument, simply issue a new prompt\r\n";
  helpText[13]= "\r\n";
  helpText[14]= "\tcopy - to be implemented\r\n";
  helpText[15]= "\r\n";
  helpText[16]= "\tddir - list directory contents, load and execute Ddir at segment 4\r\n";
  helpText[17]= "\r\n";
  helpText[18]= "\texec filename - call interrupt 0x21/4 to load and execute filename\r\n";
  helpText[19]= "\tat segment 4\r\n";
  helpText[20]= "\r\n";
  helpText[22]= "\thelp - display this user manual\r\n";
  helpText[23]= "\r\n";
  helpText[24]= "\tprnt filename - load filename into memory and print its contents\r\n";
  helpText[25]= "\tto the printer using interrupt 0x21 calls\r\n";
  helpText[26]= "\r\n";
  helpText[27]= "\tremv filename - to be implemented\r\n";
  helpText[28]= "\r\n";
  helpText[29]= "\tsenv - set environment variables, loads  and executes Stenv at segment 4\r\n";
  helpText[30]= "\r\n";
  helpText[31]= "\tshow filename - load filename into memory and display its contents\r\n";
  helpText[32]= "\tonscreen using interrupt 0x21 calls\r\n";
  helpText[33]= "\r\n";
  helpText[34]= "\ttwet filename - to be implemented\r\n";
  helpText[35]= "\r\n";
  helpText[36]= "\tcopy file1 file2 - to be implemented\r\n";

  do
  {
    for (line=(0+page*24); line<(24*(page+1)); ++line)
    {
      interrupt(0x21,0,helpText[line],0,0);
    }
    interrupt(0x21,0,"Press q to quit, any other key to continue.\r\n",0,0);
    *c = interrupt(0x16,0,0,0,0); //read in cont char
    page++;
  }while(*c != 'q');
  interrupt(0x21,5,0,0,0);  //END and return to shell
}


char* readText(char* Text)
{
  int i,j,k;
  int l=0;
  char buff[5][24][80];
  for (i=0;i<5;i++)
  {
    for(j=0;j<24;j++)
    {
      for(k=0;k<80;k++)
      {
        buff[i][j][k]=Text[l++];
      }
    }
  }
}
