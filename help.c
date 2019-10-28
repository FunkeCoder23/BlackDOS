
char* readText(char* );


void main()
{
  int i;
  char *c; //continue char
  /*
  //static char helpText[0][80]="Nulla vitae diam eget lacus placerat consequat in at dui.\r\n";
  //static char helpText[1][80]=    "Vivamus vel odio feugiat, elementum mauris vel, dictum mi.\r\n";
  //static char helpText[2][80]=    "In in sapien vel nisi pretium porttitor nec ut ante.\r\n";
  //static char helpText[3][80]=    "Etiam volutpat ipsum quis nisi porta dictum.\r\n";
  */
  //char *helpText=readText("Aenean tristique est at velit convallis, ut feugiat lectus tincidunt. Donec id lectus eu nulla venenatis placerat non ac elit.  Nullam dignissim urna quis sapien hendrerit, id commodo nisi eleifend.  Donec eu dui vel mauris auctor sodales.  Nullam lacinia enim a eros rhoncus, id scelerisque quam fringilla.  Vivamus aliquam neque quis facilisis dictum.  Etiam id sem eu elit bibendum mattis.  Quisque ut leo ut lacus volutpat vulputate.  Donec sit amet risuspellentesque,consectetur turpis ultrices, elementum mi.  Phasellus in ipsum in augue volutpat auctor id at metus.  Phasellus accumsan metus id efficitur dapibus.  Morbi euismod nulla ut tempor aliquet.  Ut pulvinar nibh molestie posuere euismod.  Nullam consectetur diam tincidunt elit porta vestibulum.  Proin fringilla mi sit amet pretium lacinia.  Pellentesque sit amet odio ut sem maximus tincidunt at a dolor.");


  do
  {
    for (i=0;i<24;i++)
    {
    //interrupt(0x21,0,helpText+i,0,0);
    }

    interrupt(0x21,0,"Press q to quit, any other key to continue.\r\n");
    *c = interrupt(0x16,0,0,0,0); //read in cont char
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
