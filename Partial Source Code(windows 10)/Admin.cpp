//ADMIN
//.mac general
//.cas -> vote storer && .map->candidate storer
//same encryption key


/*& [...]
command1 & command2
Use to separate multiple commands on one command line. Cmd.exe runs the first command, and then the second command.

&& [...]
command1 && command2
Use to run the command following && only if the command preceding the symbol is successful. Cmd.exe runs the first command, and then runs the second command only if the first command completed successfully.

|| [...]
command1 || command2
Use to run the command following || only if the command preceding || fails. Cmd.exe runs the first command, and then runs the second command only if the first command did not complete successfully (receives an error code greater than zero).

( ) [...]
(command1 & command2)
Use to group or nest multiple commands.

; or ,
command1 parameter1;parameter2
Use to separate command parameters.*/

/*To create a directory in MS-DOS or the Windows command line, use the md or mkdir MS-DOS command. For example, below we are creating a new directory called "hope" in the current directory.

mkdir hope

You can also create multiple new directories in the current directory by using the md command. In the next example, we are creating three new directories, called "user1", "user2", and "user3", in the current directory.

md user1 user2 user3

If you want to create a directory with spaces, you need to surround the directory name with quotes. In the example below, we are creating a directory called "my example directory" in the current directory.

md "my example directory"

To create a directory in the parent directory, without first moving into that directory, you can use the command below. This example moves back one directory to create the "example" directory.

md ..\example

To create a subdirectory in a different directory without moving into it, use a command similar to the example below, which creates a "test" directory in the hope directory.

mkdir hope\test

Tip: Once a directory has been created, you can use the cd command to change the directory and move into that directory.

To make a directory in another drive without moving into that drive you could use a command similar to the example below, which creates an "example" directory on the F: drive. The drive letter "f:" can be substituted from any drive letter.

md f:\example*/

/*MS-DOS users can delete files using the del command. See this page to get additional information and help with this command. Below is an example of how this command could be used.

del example.txt

As seen in the above example, when deleting a file, you need to enter the full file name including the file extension.*/


/*Name         | Value
             |
Black        |   0
Blue         |   1
Green        |   2
Cyan         |   3
Red          |   4
Magenta      |   5
Brown        |   6
Light Gray   |   7
Dark Gray    |   8
Light Blue   |   9
Light Green  |   10
Light Cyan   |   11
Light Red    |   12
Light Magenta|   13
Yellow       |   14
White        |   15*/



#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<mem.h>
#include<windows.h>
#include<signal.h>
//#include "resource.rc"

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

void gotoxy(short x,short y)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = {x,y};
	SetConsoleCursorPosition (h,position);
}

void setFontSize(int FontSize)
{
    CONSOLE_FONT_INFOEX info = {0};
    info.cbSize       = sizeof(info);
    info.dwFontSize.Y = FontSize; // leave X as zero
    info.FontWeight   = FW_NORMAL;
    wcscpy(info.FaceName, L"Lucida Console");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &info);
}

/*void setFontSize(int x, int y)
{
	PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();
	lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);
	GetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, lpConsoleCurrentFontEx);
	lpConsoleCurrentFontEx->dwFontSize.X = x;
	lpConsoleCurrentFontEx->dwFontSize.Y = y;
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, lpConsoleCurrentFontEx);
}*/

int signup(void);//To trigger SignUP i.e script.cpp[arguments nil]
int verify(char*);//To verify admin password(returns 1 for true && 0 for false)
void login(int,char*);//Login [arguments 1 -> pass non-zero integer if you want to skip the verification process, arguments 2-> if argument 1 is a non-zero int , then pass the ussername to be logged int oherwise pass an empty array]
void new_session(char*);//creat new session[argument 1=Username]
void result(char*);//view result[argument 1=Username]
void s_list(char*);//View session list from ses.mac file[argument 1=Username]
void changep(char*);//change password of user[argument 1=Username]
void reset_list(char*);//reset all sessions of a particular user[argument 1=Username]
void del(char*);//delete a session (file as well as from ses.mac)[argument 1=Username]
void enc(char*,char*);//encrypts with key=80[argument 1=string,argument 2=blank array(will store encrypted array)]
void dec(char*);//decrypts with key=80[argument 1=string(decrypts in array itself)]
void disable(char*);//Disables a particular account[argument 1=Username]
void user_list(void);//Shows list of users[arguments nil]
void info(void);//Displays information about MacEvm
void log(void);//To check wheather the user has logged out or not[arguments nil]
int get_string(char*);//will work like gets() but will also check for esc key[argument 1=array base address where string are to be stored]
//void exit_console(void);//to exit from console[arguments nil]

int choice()//it will check for esc key pressing and will return input character[arguments nil]
{
	char re[1000],c;
	register int i=0;
	
	while((c=getche())!='\r')//ascii code of cariage-return is 13
	{
		if(c==8)//for backspace
		{
			if(i>0)
			{
				printf(" \b");
				i--;
			}
			else
				gotoxy(19,10);
			continue;
		}
		else if(c==27)
		{
			//exit_console();
			return 0;
		}
		re[i++]=c;
	}
	re[i]='\0';
	i=0;
		
	if(strlen(re) > 1)
		return 0;
	else
	{
		i=re[0]-'0';
		return i;
	}
}



int main()
{
	/*BOOL WINAPI SetConsoleDisplayMode(//to start in fullscreen mode
  	HANDLE hConsoleOutput,
  	DWORD dwFlags,
  	PCOORD lpNewScreenBufferDimensions
	);*/
	
	COORD Coord; //Used to open Cosole in fullscreen mode
	SetConsoleDisplayMode( GetStdHandle( STD_OUTPUT_HANDLE ), CONSOLE_FULLSCREEN_MODE, &Coord);
	
	setFontSize(20);
	
	system("exec.bat && cls");//To create a folder in c drive
	//system("del temp.exe && cls && exit");//delete temp.exe permanently, after admin.exe executes for the first time
	//system("signup.exe && cls && exit");
	
	
	ClearConsoleToColors(-6,9);
	
	char ar[2];//empty array
	
	log();
		
	while(1)
	{
		system("cls");
		printf("\n************************************************************************************************************************************************************************");
		printf ("\n\t\t\t\t\t\tWELCOME TO MAC-EVM\n");
		printf("************************************************************************************************************************************************************************\n");
		int ch;
		printf ("\nEnter 1 to Login\nEnter 2 to Sign Up with a new account \nEnter 3 to View list of Active Users\nEnter 4 for additional info\n");
		printf ("\nEnter your choice :");
		ch=choice();
		switch(ch)
		{
			case 1:	login(0,ar);//passing 0 and an empty array base address
					system("cls");
					break;
			case 2:	signup();
					ClearConsoleToColors(-6,9);
					break;
			case 3:	user_list();
					system("cls");
					break;
			case 4: info();
					break;
			default: exit(0);
					 system("cls");
					 break;
		}
	}
}

void log(void)//acc.mac file will be checked
{
	FILE *fp=NULL;
	char name[1030],name1[1030];
	
	fp=fopen("c:\\macevm\\acc.mac","r");
	if(fp==NULL)
		return ;
		
	fscanf(fp,"%s",name);//storing the encrypted username
	
	if(name[0]=='\0')
	{
		fclose(fp);
		return ;
	}
	else
	{
		fclose(fp);
		dec(name);
		login(1,name);
	}
	
	fclose(fp);
	return ;
}

void info()
{
	ClearConsoleToColors(7,1);
	
	printf("\n\n********************************** Details *************************************\n");
	printf ("\n\n\n\t *MacEvm is dessigned for conduction of Autonomous Voting*\n");
	printf ("\n\t    *Now You can manage & Conduct your own election*\n");
	printf ("\n   *All the Votes casted, as well as account details are end-to-end encrypted*\n");
	printf ("\n      *For further information Contact me at ");
	SetColor(11);
	printf("mayukhchakrabarti99@gmail.com*\n");
	SetColor(7);
	printf("\n\n\n********************************************************************************\n");	

	getch();
	ClearConsoleToColors(-6,9);
	return ;
}


void user_list(void)
{
	ClearConsoleToColors(7,1);
	
	char name[1000];
	FILE *fp=NULL;
	memset(name,'\0',sizeof(name));
	
	fp=fopen("c:\\macevm\\zap.mac","r");//opening zap.mac
	
	if(fp==NULL)
	{
		printf("\n\t*******************List of Active Users*********************\n");
		printf ("\n\t\t\t*no Active User is present");
		printf("\n\n\t************************************************************\n");
		getch();
		return ;
	}
	
	printf("\n\t*******************List of Active Users*********************\n");
	
	fscanf(fp,"%s\n",name);
	
	if(name[0]=='\0')
		printf ("\n\t\t\t*no Active User is present");
	else
	{
		dec(name);
		printf ("\n\t\t\t%s",name);
	}
	
	while(fscanf(fp,"%s\n",name) != EOF)
	{
		dec(name);
		printf ("\n\t\t\t%s",name);
	}
	fclose(fp);
	
	printf("\n\n\t************************************************************\n");
	
	getch();
	
	ClearConsoleToColors(-6,9);
	
	return ;	
}

void login(int ggg,char* ald)
{
	system("cls");
	char ar[1000],ar_enc[1000];
	FILE *fp=NULL;
	int y;
	
	if(ggg==0)
	{
		while ((y=verify(ar)) != 1)
		{
			if(y==-1)
				return ;
			SetColor(12);
			printf ("\n\n\t\t\t*Wrong Username or password\n\n");
			SetColor(10);
			getch();
			system("cls");
		}
	}
	else
		strcpy(ar,ald);//username is copied to ar
		
	fp=fopen("c:\\macevm\\acc.mac","w");
	enc(ar,ar_enc);
	fprintf (fp,"%s",ar_enc);
	fclose(fp);
	
	system("cls");
	
	while(1)
	{
		printf ("\n\t...................Hello %s...................\n",ar);
		int ch;
		char c;
		printf ("\n\n\tEnter 1 to start a new session\n\tEnter 2 to excite vote.exe\n\tEnter 3 to view result\n\tEnter 4 to remove a session\n\tEnter 5 to view session list\n\tEnter 6 to change password\n\tEnter 7 to trigger reset\n\tEnter 8 to disable your account\n\tEnter 0 to Logout");
		printf ("\n\n\tEnter your choice : ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:	new_session(ar);
					system("cls");
					break;
			case 2:	system("vote.exe && cls && exit");
					system("cls");
					break;
			case 3:	SetColor(12);
					printf ("\n\t*warning:Vewing result will end the session\n");
					SetColor(10);
					printf ("\n\tWould you like to continue(y/n) : ");
					fflush(stdin);
					c=getchar();
					fflush(stdin);
					if((c=='y') || (c=='Y'))
						result(ar);
					system("cls");
					break;
			case 4:	del(ar);
					system("cls");
					break;
			case 5:	s_list(ar);
					system("cls");
					break;
			case 6:	changep(ar);
					system("cls");
					break; 
			case 7:	SetColor(12);
					printf ("\n\t*warning:This will reset the account and all stored data will be lost\n");
					SetColor(10);
					printf ("\n\tAre you sure (y/n) : ");
					fflush(stdin);
					c=getchar();
					fflush(stdin);
					if((c=='y') || (c=='Y'))
						reset_list(ar);
					system("cls");
					break;
			case 8:	SetColor(12);
					printf ("\n\t*warning:This will disable your account and all stored data will be lost\n");
					SetColor(10);
					printf ("\n\tAre you sure (y/n) : ");
					fflush(stdin);
					c=getchar();
					fflush(stdin);
					if((c=='y') || (c=='Y'))
						disable(ar);
					system("cls");
					return ;
					break;
			default : 	fp=fopen("c:\\macevm\\acc.mac","w");
						fclose(fp);	
						return ;
		}
	
	
	}
	
	
	
}

void disable(char *p)//username
{
	FILE *fp=NULL,*fs=NULL;
	char f[1000],temp1[1030],name[1000];
	
	fp=fopen("c:\\macevm\\acc.mac","w");
	fclose(fp);	
	
	strcpy(temp1,"RD /s /q ");
	strcat(temp1,"\"c:\\macevm\\");
	strcat(temp1,p);
	strcat(temp1,"\"");//prepairing the command to delete the username file with remove tree option
	
	system(temp1);//account disabled
	
	//Now we have to remove the account name from zap.mac
	
	fp=fopen("c:\\macevm\\zap.mac","r");//opening zap.mac
	fs=fopen("c:\\macevm\\temp.mac","w");//opening a temporary file
	
	while(fscanf(fp,"%s\n",f) != EOF)
	{
		dec(f);
		
		if(strcmp(f,p)==0)
			continue;
		else
		{
			enc(f,name);
			fprintf (fs,"%s\n",name);	
		}	
	}	
	
	fclose(fs);
	fclose(fp);
	
	remove("c:\\macevm\\zap.mac");//removing zap.mac
	rename("c:\\macevm\\temp.mac","c:\\macevm\\zap.mac");
	
	SetColor(14);
	printf ("\n\n\t************ Your account has been disabled ************\n");
	SetColor(10);
	getch();
	return ;
}

void reset_list(char *p)//Username
{
	FILE *fp=NULL;
	char temp[1030],p1[1000],temp1[1030];
	
	strcpy(temp,"c:\\macevm\\");
	strcat(temp,p);
	strcat(temp,"\\wap.mac");
	fp=fopen(temp,"r");//opening wap.mac
	if(fp==NULL)
	{
		SetColor(12);
		printf ("\n\t*Problem with files ERROR_507\n");
		SetColor(10);
		getch();
		return ;
	}
	
	fscanf(fp,"%s",p1);//taking encrypted password in p1
	fclose(fp);
	
	strcpy(temp1,"RD /s /q ");
	strcat(temp1,"\"c:\\macevm\\");
	strcat(temp1,p);
	strcat(temp1,"\"");//prepairing the command to delete the username file with remove tree option
	
	system(temp1);
	
	strcpy(temp1,"cd /d c:\\ && cd macevm && mkdir ");
	strcat(temp1,p);
	
	system(temp1);//creating username file again
	
	fp=fopen(temp,"w");
	
	fprintf (fp,"%s",p1);//again setting the password back to wap.mac
	fclose(fp);
	
	SetColor(14);
	printf ("\n\n\tYour account has been reset\n");
	SetColor(10);
	getch();
	return ; 
	
}

void changep(char *p)//username
{
	
	system("cls");
	char c,pas[1000],temp[1000],chkp[1000],np[1000],enp[1000],re[1000];
	int i=0;
	FILE *fp=NULL;
	
	printf ("\n\t...................Hello %s...................\n",p);
	
	printf ("\n\n\tEnter previous User Password: ");
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
	
	//password verification
	
	strcpy(temp,"c:\\macevm\\");
	strcat(temp,p);
	strcat(temp,"\\wap.mac");
	fp=fopen(temp,"r");
	if(fp==NULL)
	{
		SetColor(12);
		printf ("\n\t*problem with files ERROR_506\n");
		SetColor(10);
		getch();
		return ;
	}
	
	fscanf(fp,"%s",chkp);
	
	dec(chkp);
	
	if(strcmp(pas,chkp)!=0)
	{
		fclose(fp);
		SetColor(12);
		printf ("\n\t*Wrong Username or password\n\n");
		SetColor(10);
		getch();
		return ;
	}
	
	fclose(fp);
	
	while(1)
	{
		printf ("\n\n\tEnter New User Password: ");
	
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
			np[i++]=c;
			printf ("*");
		}
		np[i]='\0';
		i=0;
		
		printf ("\n\n\tConfirm your password: ");
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
			re[i++]=c;
			printf ("*");
		}
		re[i]='\0';
		i=0;
		
		if(strcmp(np,re)!=0)
		{
			SetColor(12);
			printf("\n\t*Password Confirmation Failed\n");
			SetColor(10);
			continue;
		}
		else
			break;
	}
	
	enc(np,enp);
	
	fp=NULL;
	fp=fopen(temp,"w");
	
	if(fp==NULL)
	{
		SetColor(12);
		printf ("\n\t*Problem with Files_ERROR 402");
		SetColor(10);
		getch();
		return ;
	}
	
	fprintf(fp,"%s",enp);
	fclose(fp);
	
	SetColor(14);
	printf ("\n\n\t************ Password Succssfully changed ************\n");
	SetColor(10);
	getch();
	return ;
}

void s_list(char *p)//username
{
	ClearConsoleToColors(7,1);
	
	char name[1000],temp[1030];
	FILE *fp=NULL;
	memset(name,'\0',sizeof(name));
	
	strcpy(temp,"c:\\macevm\\");
	strcat(temp,p);
	strcat(temp,"\\ses.mac");
	fp=fopen(temp,"r");//opening ses.mac
	
	if(fp==NULL)
	{
		printf("\n\t***********************Session List*************************\n");
		printf ("\n\t\t\t*no sessions created yet");
		printf("\n\n\t************************************************************\n");
		getch();
		ClearConsoleToColors(-6,9);
		return ;
	}
	
	printf("\n\t***********************Session List*************************\n");
	
	fscanf(fp,"%s\n",name);
	
	if(name[0]=='\0')
		printf ("\n\t\t\t*no sessions created yet");
	else
	{
		dec(name);
		printf ("\n\t\t\t%s",name);
	}
	
	while(fscanf(fp,"%s\n",name) != EOF)
	{
		dec(name);
		printf ("\n\t\t\t%s",name);
	}
	fclose(fp);
	
	printf("\n\n\t************************************************************\n");
	
	getch();
	
	ClearConsoleToColors(-6,9);
	
	return ;
}
	

void del(char *p)
{
	
	system("cls");
	
	char s[1000],temp1[1000],temp[1000],exp[12],exp1[]={"(expired)"},name[1000],n[1000],s1[1020];
	FILE *fm=NULL,*fc=NULL;
	
	printf ("\n\t...................Hello %s...................\n",p);
	
	printf ("\n\n\tEnter session name : ");
	fflush(stdin);
	gets(s);
	fflush(stdin);
	
	strcpy(temp1,"c:\\macevm\\");
	strcat(temp1,p);
	strcat(temp1,"\\");
	strcat(temp1,s);
	strcat(temp1,".map");
	
	fm=fopen(temp1,"r");
	if(fm==NULL)
	{
		SetColor(12);
		printf ("\n\n\t*No such session is present\n");
		SetColor(10);
		fclose(fm);
		getch();
		return ;
	}//.mac is not closed ->fm
	fclose(fm);
	
	SetColor(12);
	printf("\n\n\tDo you really want to delete \"%s\" session (y/n): ",s);
	SetColor(10);
	fflush(stdin);
	char flp=getchar();
	fflush(stdin);
	if((flp!='Y') && (flp!='y'))
		return ;
	
	remove(temp1);//removing .map
	
	strcpy(temp,"c:\\macevm\\");
	strcat(temp,p);
	strcat(temp,"\\");
	strcat(temp,s);
	strcat(temp,".cas");
	
	remove(temp);//removing .cas
	
	//removing encrypted data from ses.mac
	
	strcpy(temp,"c:\\macevm\\");
	strcat(temp,p);
	strcat(temp,"\\ses.mac");
	fm=fopen(temp,"r");//opening ses.mac
	if(fm==NULL)
	{
		SetColor(12);
		printf ("\n\n\t*Problem with files ERROR_307");
		getch();
		return ;
	}
	
	strcpy(temp1,"c:\\macevm\\");
	strcat(temp1,p);
	strcat(temp1,"\\tem.mac");
	fc=fopen(temp1,"w");//opening tem.mac
	if(fc==NULL)
	{
		SetColor(12);
		printf ("\n\n\t*Problem with files ERROR_308");
		getch();
		return ;
	}
	
	
	enc(exp1,exp);
	strcpy(s1,s);
	strcat(s1,exp1);
	
	while(fscanf(fm,"%s\n",name) != EOF)
	{
		dec(name);
		if((strcmp(s,name)==0) || (strcmp(s1,name)==0))
		{
			continue;
		}	
		else
		{
			enc(name,n);
			fprintf(fc,"%s\n",n);
		}
	}
	fclose(fc);
	fclose(fm);
	
	remove(temp);//removing ses.mac
	rename(temp1,temp);//renaming tem.mac to ses.mac
	
	SetColor(14);
	printf ("\n\n\t\"%s\" session has been deleted\n",s);
	SetColor(10);
	getch();
	return ;
	
}

void new_session(char *p)//username
{
	char ar[1000],c,enc_ar[1000],temp[1030];//ar=session name,C=STORES char,enc_ar=encrypted ar
	int i=0;
	system("cls");
	printf ("\n\t...................Hello %s...................\n",p);
	printf ("\n\n\tLet's start a new session:-\n");
	printf ("\n\n\tEnter session name (caution : use only digits and alphabets): ");
	
	fflush(stdin);
	while((c=getchar()) != '\n')//ascii code of line feed is 10
	{
		if(i>=1000)
			break;
		
		if((c>=48 && c<=57)||(c>=65 && c<=90)||(c>=97 && c<=122))
			ar[i++]=c;
		else
		{
			SetColor(12);
			printf ("\n\t*Warning: No spaces or special characters can be used\n");
			SetColor(10);
			printf ("\n\n\tRe-enter Session name (caution : use only digits and alphabets): ");
			i=0;
			fflush(stdin);
			continue;
		}
	}
	ar[i]='\0';
	i=0;
	
	//checking previous presence of this session
	FILE *check_f=NULL;
	
	strcpy(temp,"c:\\macevm\\");
	strcat(temp,p);
	strcat(temp,"\\");
	strcat(temp,ar);
	strcat(temp,".map");
	check_f=fopen(temp,"r");
	if(check_f != NULL)
	{
		fclose(check_f);
		SetColor(12);
		printf ("\n\t*This Session already exists");
		SetColor(10);
		return ;
	}
	
	enc(ar,enc_ar);//encrypting session
	
	//session names will be contained in ses.mac
	
	char des[1100];//stores file path
	strcpy(des,"c:\\macevm\\");
	strcat(des,p);
	strcat(des,"\\ses.mac");
	
	FILE *fp=NULL;
	fp=fopen(des,"a+");//opening sas.mac
	if(fp==NULL)
	{
		SetColor(12);
		printf ("\n\t*error_problem with files code_202");
		SetColor(10);
		exit(0);
	}
	
	fprintf (fp,"%s\n",enc_ar);
	fclose(fp);
	fp=NULL;
	
	strcpy(des,"c:\\macevm\\");
	strcat(des,p);
	strcat(des,"\\");
	strcat(des,ar);
	strcat(des,".map");
	fp=fopen(des,"a+");//to add the name of candidates in .map file
	
	
	system("cls");
	printf ("\n\t...................Hello %s...................\n",p);
	int k=1;
	char name[1000],name_enc[1000];
	memset(name,'\0',sizeof(name));
	
	printf ("\n\n\tAdd Candidate names");
	SetColor(12);
	printf ("(*Leave a name spot blank to stop addition process)(max_limit 9 candidates)");
	SetColor(10);
	printf (":-\n\n");
	int cou=0;
	name[0]=1;
	while((name[0]!='\0') && (cou<9))
	{
		printf ("\n\tCandidate no. %d : ",k);
		gets(name);
		fflush(stdin);
		k++;
		cou++;
		enc(name,name_enc);//encrypting
		fprintf (fp,"%s\n",name_enc);
	}
	fclose(fp);//closing .map
		
	SetColor(14);
	printf ("\n\n\t************ Session Succssfully created ************\n");
	SetColor(10);
	getch();
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

int get_string(char *ar)
{
	char c;
	register int i=0;
	
	while((c=getche()) != '\r')//ascii code of line feed is 10
	{
		if(i>=1000)
			break;
			
		if(c==27)
			return 0;//escape key has been pressed...unsuccessful
		if(c==8)
		{
			if(i>0)
			{
				printf(" \b");
				i--;
			}
			else
				gotoxy(35,16);
			continue;
		}
		
		ar[i++]=c;
		
	}
	ar[i]='\0';
	i=0;
	
	return 1;
}

int verify(char *ar)
{
	char chk[1000],pas[1000],chkp[1000],temp[1100],c;//ar=chk=User.N;pas=chkp=password;
	int i=0;
	FILE *fp=NULL;
	fflush(stdin);
	printf ("\n\n\n\n\n\n\n\n\n\n\t\t\t....................................................................\n");
	printf ("\n\t\t\tLogin to your Admin account:-\n");
	printf ("\n\n\n\t\t\tUsername : ");
	printf ("\n\n\n\n\n\t\t\tPassword : ");
	printf ("\n\n\n\n\n\t\t\t....................................................................\n");
	fflush(stdin);
	gotoxy(35,16);
	if(get_string(ar)==0)return -1;
	
	//printf ("\n\n\t\t\tPassword: ");
	gotoxy(35,21);
	
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
			return -1;
		
		pas[i++]=c;
		printf ("*");
	}
	pas[i]='\0';
	i=0;
	
	//printf ("\n\n\t\t\t....................................................................\n");
	//Verification starts
	strcpy(temp,"c:\\macevm\\");
	strcat(temp,ar);
	strcat(temp,"\\wap.mac");
	fp=fopen(temp,"r");
	
	if(fp==NULL)
		return 0;
		
	fscanf(fp,"%s",chkp);
	
	dec(chkp);
	
	if(strcmp(pas,chkp)==0)
	{
		fclose(fp);
		return 1;
	}
	else
	{
		fclose(fp);
		return 0;
	}
		
}

void result(char *p)//username
{
	ClearConsoleToColors(-6,9);
	
	
	printf ("\n\t...................Hello %s...................\n",p);
	
	char s[1000],exp[12],exp1[]={"(expired)"},temp1[1000],temp[1000],name[1000],n[1020],c;
	
	register unsigned long int **vote=(unsigned long int **)malloc(2*sizeof(unsigned long int*));
	
	register unsigned long int t=0,i,z,j,x=0,total=0;
	FILE *fm=NULL,*fc=NULL;
	
	printf ("\n\n\tEnter session name : ");
	fflush(stdin);
	gets(s);
	fflush(stdin);
	
	strcpy(temp1,"c:\\macevm\\");
	strcat(temp1,p);
	strcat(temp1,"\\");
	strcat(temp1,s);
	strcat(temp1,".map");
	
	fm=fopen(temp1,"r");
	if(fm==NULL)
	{
		SetColor(12);
		printf ("\n\n\t*No such session is present\n");
		SetColor(10);
		fclose(fm);
		getch();
		return ;
	}//.mac is not closed ->fm
	
	
	while(fscanf(fm,"%s\n",name) != EOF)
		t++;//counter of total no. of names present
	
	fclose(fm);//.mac closed
	
	
			//printf("\n\n\tTotal Names count Successfull\n");
	
	t++;//contains total no. of candidates incuding 1 extra for waste vote
	
	for(i=0;i<2;i++)
		vote[i]=(unsigned long int*)calloc(t,sizeof(unsigned long int));
	//memset(vote,'0',sizeof(vote));
	//if(vote[i]==NULL)printf("f");
	
			
			//printf("\n\n\t2d counter&storer formed and memseted to \'0\' and t=%d\n",t);
	
	for(i=0;i<t;i++)
	{
		vote[0][i]=i+1;
	}
		
			//printf("\n\n\tcandidate index stored in 2d Successfull\n");
	
	strcpy(temp,"c:\\macevm\\");
	strcat(temp,p);
	strcat(temp,"\\");
	strcat(temp,s);
	strcat(temp,".cas");
	
	
			//printf("\n\n\tFile Names formation Successfull .cas\n");
	
	fc=fopen(temp,"r");//opening .cas
	if(fc==NULL)
	{
		SetColor(12);
		printf ("\n\n\t*Session not yet started\n");
		SetColor(10);
		getch();
		return ;
	}
			printf("\n\n\t.cas opened Successfully\n");
	
	while((c=fgetc(fc)) != EOF)
	{
		c=c-80;//decrypting
		
		if(c==3)//checking for expiry -> 80+3
			continue;
			
		z=c-'0';
		if(z>t)
			z=t;
		z--;
		vote[1][z]++;
		total++;
	}
	fclose(fc);//all votes are stored in vote[] where 0 index of array represents candidate 1 and t-1 index represents wrong choice
	
	
			//printf("\n\n\tVote calculation Successfull\n");
	
	//performing bubble sort (descending order) leaving index t-1 in its original position

	for(i=2;i<=t-1;i++)//i=2 is given since we don't want to change the value of t-1 th index of  vote[]
	{
		for(j=0;j<t-i;j++)
		{
			if(vote[1][j]<vote[1][j+1])
			{
				vote[1][j]=vote[1][j]^vote[1][j+1];
				vote[1][j+1]=vote[1][j]^vote[1][j+1];
				vote[1][j]=vote[1][j]^vote[1][j+1];
				vote[0][j]=vote[0][j]^vote[0][j+1];
				vote[0][j+1]=vote[0][j]^vote[0][j+1];
				vote[0][j]=vote[0][j]^vote[0][j+1];
			}
		}
	}
	
	//bubble sort completed
	
			//printf("\n\n\tSorting Successfull\n");
	
	//system("cls");
	ClearConsoleToColors(5,11);
	
	
	fm=fopen(temp1,"r");
	i=j=0;
	
	if((t>2) && (vote[1][0]==vote[1][1]))
	{
		
		printf("\n\t**********************Election Details**********************\n");
		for(j=1;j<=t-1;j++)
		{
				//	printf ("\nLoop1");
			while(i!=vote[0][j-1])
			{
					//printf ("\nLoop2");
				fscanf(fm,"%s\n",name);
				i++;
			}
			rewind(fm);
			i=0;
			dec(name);
			printf("\n\t%s Secured %lu Votes",name,vote[1][j-1]);
			
		}
		printf("\n\tNOTA = %lu\n",vote[1][t-1]);
		printf("\n\tTotal votes Casted = %lu\n",total);
		printf("\n\n\t************************************************************\n\n");	
	
		x=vote[1][0];//storing the heighest vote in x
		register int f=0;
		i=0;
		
		printf("\n\n\t************************************************************\n");
		
		SetColor(13);
		
		printf ("\n\t\t\tThere has been a tie between :-\n");
		
		while((vote[1][f]==x) && (f<t-1))
		{
					//printf ("\nLoop3");
			while(i!=vote[0][f])
			{
					//printf ("\nLoop4");
				fscanf(fm,"%s\n",name);
				i++;
			}
			rewind(fm);
			i=0;
			f++;
			dec(name);
			printf("\n\t\t\t%s",name);
		}
		
		SetColor(5);
		
		printf("\n\n\t************************************************************\n");
	}
	else
	{
		printf("\n\t**********************Election Details**********************\n");
		for(j=1;j<=t-1;j++)
		{
					//printf ("\nLoop1");
			while(i!=vote[0][j-1])
			{
				//	printf ("\nLoop2");
				fscanf(fm,"%s\n",name);
				i++;
			}
			rewind(fm);
			i=0;
			dec(name);
			printf("\n\t%s Secured %lu Votes",name,vote[1][j-1]);
			
		}
		printf("\n\tNOTA = %lu\n",vote[1][t-1]);
		printf("\n\tTotal votes Casted = %lu\n",total);
		printf("\n\n\t************************************************************\n\n");
		
		while(i!=vote[0][0])
		{
			fscanf(fm,"%s\n",name);
			i++;
		}
		rewind(fm);
		i=0;
		dec(name);
		
		printf("\n\n\t************************************************************\n");
		
		SetColor(13);
		printf ("\t\t\t %s Won this election",name);	
		SetColor(5);
		
		printf("\n\t************************************************************\n\n");
	}
	fclose(fm);
	
	char op;
	fc=fopen(temp,"r");//opening .cas in r mode
	fseek(fc,-1,2);
	op=fgetc(fc);
	fclose(fc);
	
	if(op != 83)//checking if it is already expired
	{
		fc=fopen(temp,"a+");//opening .cas in a+ mode
		fputc(83,fc);//making it expired
		fclose(fc);
	}
	
	//final step->put "(expired)" on ses.mac onto that particular session
	
	strcpy(temp,"c:\\macevm\\");
	strcat(temp,p);
	strcat(temp,"\\ses.mac");
	fm=fopen(temp,"r");//opening ses.mac
	if(fm==NULL)
	{
		SetColor(12);
		printf ("\n\n\t*Problem with files ERROR_205");
		SetColor(12);
		getch();
		return ;
	}
	
	strcpy(temp1,"c:\\macevm\\");
	strcat(temp1,p);
	strcat(temp1,"\\tem.mac");
	fc=fopen(temp1,"w");//opening tem.mac
	if(fc==NULL)
	{
		SetColor(12);
		printf ("\n\n\t*Problem with files ERROR_206");
		SetColor(10);
		getch();
		return ;
	}
	
	
	enc(exp1,exp);
	
	while(fscanf(fm,"%s\n",name) != EOF)
	{
		dec(name);
		if(strcmp(s,name)==0)
		{
			enc(name,n);
			strcat(n,exp);
			fprintf(fc,"%s\n",n);	
		}	
		else
		{
			enc(name,n);
			fprintf(fc,"%s\n",n);
		}
	}
	fclose(fc);
	fclose(fm);
	
	remove(temp);
	rename(temp1,temp);
	
	getch();
	
	ClearConsoleToColors(-6,9);
	
	return ;
}
