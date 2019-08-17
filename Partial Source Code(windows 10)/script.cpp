//used for Sign Up
//creates file named zap.mac && wap.mac
//encryption key=+80

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<windows.h>


/*void SetColor(int ForgC)
 {
 WORD wColor;

  HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;

                       //We use csbi for the wAttributes word.
 if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
 {
                 //Mask out all but the background attribute, and add in the forgournd color
      wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
      SetConsoleTextAttribute(hStdOut, wColor);
 }
 return;
}




void ClearConsoleToColors(int ForgC, int BackC)
{
 WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
               //Get the handle to the current output buffer...
 HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
                     //This is used to reset the carat/cursor to the top left.
 COORD coord = {0, 0};
                  //A return value... indicating how many chars were written
                    //   not used but we need to capture this since it will be
                      //   written anyway (passing NULL causes an access violation).
 DWORD count;

                               //This is a structure containing all of the console info
                      // it is used here to find the size of the console.
 CONSOLE_SCREEN_BUFFER_INFO csbi;
                 //Here we will set the current color
 SetConsoleTextAttribute(hStdOut, wColor);
 if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
 {
                          //This fills the buffer with a given character (in this case 32=space).
      FillConsoleOutputCharacter(hStdOut, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);

      FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count );
                          //This will set our cursor position for the next print statement.
      SetConsoleCursorPosition(hStdOut, coord);
 }
 return;
} */
void SetColor(int ForgC);
void ClearConsoleToColors(int ForgC, int BackC);
void gotoxy(short x,short y);
void setFontSize(int);

int signup(void)
{
	char ar[1000],p[1000],c,cpy[1100],enc[1000],re[1000];
	int i=0,j=0;
	FILE *fp=NULL,*fs=NULL;
	
	ClearConsoleToColors(-6,9);
	
	SetColor(14);
	printf ("\n\n\n\n\n\n\n\n\n\n\t\t\t....................................................................\n");
	printf ("\n\t\t\tSign up with a new account:-\n");
	SetColor(10);
	printf ("\n\n\n\t\t\tUsername (caution : use only digits and alphabets): ");
	printf ("\n\n\n\n\t\t\tEnter password: ");
	printf ("\n\n\n\n\t\t\tConfirm your password: ");
	SetColor(14);
	printf ("\n\n\n\n\n\t\t\t....................................................................\n");
	SetColor(10);
	fflush(stdin);
	
	gotoxy(76,16);
	while((c=getche()) != '\r')//ascii code of line feed is 10
	{
		if(i>=1000)
			break;
			
		if(c==27)
			return 0;
		if(c==8)
		{
			if(i>0)
			{
				printf(" \b");
				i--;
			}
			else
				gotoxy(76,16);
			continue;
		}
		
		if((c>=48 && c<=57)||(c>=65 && c<=90)||(c>=97 && c<=122))
			ar[i++]=c;
		else
		{
			system("cls");
			
			SetColor(14);
			printf ("\n\n\n\n\n\n\n\n\n\n\t\t\t....................................................................\n");
			printf ("\n\t\t\tSign up with a new account:-\n");
			SetColor(10);
			printf ("\n\n\n\t\t\tUsername (caution : use only digits and alphabets): ");
			printf ("\n\n\n\n\t\t\tEnter password: ");
			printf ("\n\n\n\n\t\t\tConfirm your password: ");
			SetColor(14);
			printf ("\n\n\n\n\n\t\t\t....................................................................\n");
			
			SetColor(12);
			gotoxy(24,17);
			printf ("*Warning: No spaces or special characters can be used");
			SetColor(10);
			gotoxy(24,16);
			printf ("Username (caution : use only digits and alphabets): ");
			i=0;
			gotoxy(76,16);
			fflush(stdin);
			continue;
		}
	}
	ar[i]='\0';
	i=0;
	
	while((c=ar[i++])!='\0')//encrypting username of zap.mac with +80
		enc[j++]=(c+80);
	enc[j]='\0';
	j=0;
	i=0;
	
	
	while(1)
	{
		//gotoxy(24,20);
		//printf ("Enter password: ");
		system("cls");
		SetColor(14);
		
		gotoxy(24,10);
		
		printf ("....................................................................\n");
		printf ("\n\t\t\tSign up with a new account:-\n");
		SetColor(10);
		printf ("\n\n\n\t\t\tUsername (caution : use only digits and alphabets): %s",ar);
		printf ("\n\n\n\n\t\t\tEnter password: ");
		printf ("\n\n\n\n\t\t\tConfirm your password: ");
		SetColor(14);
		printf ("\n\n\n\n\n\t\t\t....................................................................\n");
		SetColor(10);
		
		gotoxy(40,20);
		while((c=getch())!='\r')//ascii code of cariage-return is 13
		{
			if(c==8)
			{
				if(i>0)
				{
					printf("\b");
					printf(" ");
					printf("\b");
					i--;
				}
				continue;
			}
			else if(c==27)
				return 0;
			p[i++]=c;
			printf ("*");
		}
		p[i]='\0';
		i=0;
		
		//gotoxy(24,24);
		//printf ("Confirm your password: ");
		gotoxy(47,24);
		while((c=getch())!='\r')//ascii code of cariage-return is 13
		{
			if(c==8)
			{
				if(i>0)
				{
					printf("\b");
					printf(" ");
					printf("\b");
					i--;
				}
				continue;
			}
			else if(c==27)
				return 0;
			re[i++]=c;
			printf ("*");
		}
		re[i]='\0';
		i=0;
		
		if(strcmp(p,re)!=0)
		{
			SetColor(12);
			printf("\n\t\t\t*Password Confirmation Failed\n");
			SetColor(10);
			getch();
			continue;
		}
		else
			break;
	}
	//checking the presence of username
	
	strcpy(cpy,"c:\\macevm\\");
	strcat(cpy,ar);
	strcat(cpy,"\\wap.mac");//wap.txt file contains password
	
	fs=fopen(cpy,"r");//checking if this file previously exists
	if(fs != NULL)
	{
		SetColor(12);
		printf ("\n\n\t\t\t*This Username is already in use_error 103\n");
		SetColor(10);
		fclose(fs);
		getch();
		return 0;
	}
	fclose(fs);
	fs=NULL;
	
	fp=fopen("c:\\macevm\\zap.mac","a+");//zap.mac will store user name(opened in write mode since it executes only once)
	if(fp==NULL)
	{
		SetColor(12);
		printf ("\n\n\tFetal Error (error: 101)\n");
		SetColor(0);
		exit(0);
	}
	fprintf(fp,"%s\n",enc);
	fclose(fp);
	
	strcpy(cpy,"cd /d c:\\ && cd macevm && mkdir ");
	strcat(cpy,ar);
	
	system(cpy);//creating a folder named username
	
	strcpy(cpy,"c:\\macevm\\");
	strcat(cpy,ar);
	strcat(cpy,"\\wap.mac");
	
	/*fs=fopen(cpy,"r");//checking if this file previously exists
	if(fs != NULL)
	{
		SetColor(12);
		printf ("\n\t*This Username is already in use_error 103\n");
		SetColor(10);
		fclose(fs);
		getch();
		exit(0);
	}
	fclose(fs);
	fs=NULL;*/
	
	fs=fopen(cpy,"w");
	if(fs==NULL)
	{
		SetColor(12);
		printf ("\n\tFetal Error (error: 102)\n");
		SetColor(0);
		getch();
		exit(0);
	}
	
	while((c=p[i++]) != '\0')
	{
		c=c+80;//Encrypting
		fputc(c,fs);
	}
	fclose(fs);
	SetColor(14);
	printf ("\n\n\t************ Account Succssfully created ************\n");
	getch();
	SetColor(0);
	return 0;
}

