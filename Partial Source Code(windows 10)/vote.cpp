//vote.exe is used as vote caster
//votes will be saved on .cas file
//votes will be end to end encrypted

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<string.h>


void SetColor(int ForgC)
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
} 

void enc(char*,char*);
void dec(char *);
//encryption key=80

int main()
{
	int i=0;
	char c,ar[1000],pas[1000],ses[1000],temp[1000],chkp[1000],temp1[1000];
	FILE *fp=NULL,*fs=NULL;
	
	ClearConsoleToColors(-6,9);
	
	printf ("\n\t...................WELCOME to MacEvm...................\n");
	printf ("\n\tLets start a session:-\n");
	printf ("\n\n\tEnter Username : ");
	fflush(stdin);
	gets(ar);
	fflush(stdin);
	
	printf ("\n\n\tEnter User Password: ");
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
		
		pas[i++]=c;
		printf ("*");
	}
	pas[i]='\0';
	i=0;
	
	//Verification starts
	strcpy(temp,"c:\\macevm\\");
	strcat(temp,ar);
	strcat(temp,"\\wap.mac");
	fp=fopen(temp,"r");
	
	if(fp==NULL)
	{
		SetColor(12);
		printf ("\n\t*Wrong Username or password\n\n");
		SetColor(10);
		getch();
		return 0;
	}
	
	fscanf(fp,"%s",chkp);
	
	dec(chkp);
	
	if(strcmp(pas,chkp) != 0)
	{
		fclose(fp);
		SetColor(12);
		printf ("\n\t*Wrong Username or password\n\n");
		SetColor(10);
		getch();
		return 0;
	}
	
	//session varification starts
	
	printf ("\n\n\tEnter Session name: ");
	fflush(stdin);
	gets(ses);
	fflush(stdin);
	
	//checking for presence of session
	strcpy(temp1,"c:\\macevm\\");
	strcat(temp1,ar);
	strcat(temp1,"\\");
	strcat(temp1,ses);
	strcat(temp1,".map");
	fs=fopen(temp1,"r");
	if(fs==NULL)
	{
		SetColor(12);
		printf ("\n\n\t*No such session is present\n");
		SetColor(10);
		fclose(fs);
		getch();
		return 0;
	}//.mac is not closed ->fs
		
	//checking session is new or old
	strcpy(temp,"c:\\macevm\\");
	strcat(temp,ar);
	strcat(temp,"\\");
	strcat(temp,ses);
	strcat(temp,".cas");
	fp=fopen(temp,"r");
	if(fp != NULL)
	{
		char check;
		SetColor(12);
		fseek(fp,-1,2);
		check=fgetc(fp);
		if(check==83)//if 80+3 is present at the end, then it has expired
		{
			printf ("\n\n\t*This session has already expired\n");	
			SetColor(10);
			getch();
			return 0;
		}
		rewind(fp);
		
		printf ("\n\n\twarning:This session is already in use\n");
		printf ("\n\tWould you like to continue (y/n): ");
		fflush(stdin);
		SetColor(10);
		c=getchar();
		fflush(stdin);
		if((c=='N') || (c=='n'))
		{
			fclose(fp);
			return 0;
		}
	}
	fclose(fp);
	fp=NULL;
	
	//system("cls");
	ClearConsoleToColors(-7,14);
	
	register int k=1;
	
	while(1)//using pas[] to collect candidate names from .map file through fs(F.pointer) 
	{
		printf ("\n\t...................WELCOME to MacEvm...................\n\n");
		while(fscanf(fs,"%s\n",pas) != EOF)
		{
			dec(pas);
			printf ("\n\t\t\tPress %d to vote for %s\n",k,pas);
			k++;
		}
		k=1;
		rewind(fs);
		
		printf ("\n\n\n\tCast your vote : ");
		fflush(stdin);
		c=getche();
		c=c+80;//encrypting vote
		fp=fopen(temp,"a+");
		
		if(fp==NULL)
		{
			SetColor(12);
			printf ("\n*FETAL ERROR_203");
			SetColor(-7);
			return 0;
		}
		
		fputc(c,fp);
		fclose(fp);
		printf ("\a");//ALERT for vote success
		fp=NULL;
		system("cls");
	}
	
	
}

void enc(char *p,char *s)
{
	while(*p != '\0')
	{
		(*s)=(*p)+80;
		p++;
		s++;
	}
	(*s)='\0';
	return ;
}

void dec(char *p)
{
	while(*p != '\0')
	{
		(*p)=(*p)-80;
		p++;	
	}
	return ;
}
