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
/* Signed:Aaron Tobias, Matt Stran, Molly Kendrick 						  */
/* Date:9/10/19         												  */
/*                                                                        */
/*                                                                        */
/* 3460:4/526 BlackDOS2020 kernel, Version 1.03, Fall 2019.               */

void handleInterrupt21(int,int,int,int);
void printLogo();

void main()
{
   makeInterrupt21();
   printLogo();
   interrupt(33,0,"Hello world from Matt Stran, Molly Kendrick, Aaron Tobias.\r\n\0",1,0);
   while(1);
}

void printString(char* c, int d)
{
   	while(*c) /*test for null-terminating char*/
	{
		char al = *c++; 	/*get deref'd char, and then inc*/
		char ah = 14;
		int ax = 3584 + al;  /*ah*256+al*/
		if (d!=1)   /* 1->print, 0->display */
		{
			interrupt(16, ax, 0, 0, 0);  /* display on screen*/
		}
		else
		{
			interrupt(23, al, 0,0,0); /*print out*/
		}
	}
   return;
}

void printLogo()
{
  interrupt(33,0,"       ___   `._   ____  _            _    _____   ____   _____ \r\n\0",0,0);
  interrupt(33,0,"      /   \\__/__> |  _ \\| |          | |  |  __ \\ / __ \\ / ____|\r\n\0",0,0);
  interrupt(33,0,"     /_  \\  _/    | |_) | | __ _  ___| | _| |  | | |  | | (___ \r\n\0",0,0);
  interrupt(33,0,"    // \\ /./      |  _ <| |/ _` |/ __| |/ / |  | | |  | |\\___ \\ \r\n\0",0,0);
  interrupt(33,0,"   //   \\\\        | |_) | | (_| | (__|   <| |__| | |__| |____) |\r\n\0",0,0);
  interrupt(33,0,"._/'     `\\.      |____/|_|\\__,_|\\___|_|\\_\\_____/ \\____/|_____/\r\n\0",0,0);
  interrupt(33,0," BlackDOS2020 v. 1.03, c. 2019. Based on a project by M. Black. \r\n\0",0,0);
  interrupt(33,0," Author(s): Molly Kendrick, Matt Stran, Aaron Tobias.\r\n\r\n\0",0,0);
}

/* MAKE FUTURE UPDATES HERE */
/* VVVVVVVVVVVVVVVVVVVVVVVV */



/* ^^^^^^^^^^^^^^^^^^^^^^^^ */
/* MAKE FUTURE UPDATES HERE */

void handleInterrupt21(int ax, int bx, int cx, int dx)
{
  switch(ax) {  
   case 0:  printString(bx,cx); //call printString with 
			break;
/*  case 1: 
	case 2: 
	case 3: 
	case 4: 
	case 5:
    case 6: 
	case 7: 
	case 8: 
	case 9: 
	case 10:
	case 11: 
	case 12: 
	case 13: 
	case 14: 
	case 15: 
*/
 default: printString("General BlackDOS error.\r\n\0"); 
  }  
}
