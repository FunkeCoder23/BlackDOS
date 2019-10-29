
char* readText(char* );


void main()
{
  int line=0;
  int page=0;
  char *c; //continue char
  char* helpText[80]; //helpText buffer


  helpText[0]="Nulla vitae diam eget lacus placerat consequat in at dui.\r\n";
  helpText[1]=    "Vivamus vel odio feugiat, elementum mauris vel, dictum mi.\r\n";
  helpText[2]=    "In in sapien vel nisi pretium porttitor nec ut ante.\r\n";
  helpText[3]=    "Etiam volutpat ipsum quis nisi porta dictum.\r\n";
  

  do
  {
    for (line=(0+page*24); line<(24*(page+1)); ++line)
    {
      interrupt(0x21,0,helpText[line],0,0);
    }
    interrupt(0x21,0,"Press q to quit, any other key to continue.\r\n");
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
