// project:Attendance system
//********************************HEADER FILES***************************
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<iomanip.h>
#include<fstream.h>
#include<conio.h>
#include<iostream.h>
#include<string.h>
#include<dir.h>
#include<dos.h>
#include<graphics.h>
#include<bios.h>
#include<time.h>
#include<process.h>
#define UP_ARROW      72
#define DOWN_ARROW    80

//***********************************************************************
//*********************************USER FUNCTIONS************************

void passwordmenu  ();
void get_password();
void change_password();
int menu();
void drawMenu (int, int, int);
void finish();
void Intro();
void G();
void about_us();
void show_header();
void help();
void *p;
size_t area;

//**********************************************************************
class attendenceout;			    // forward declaration

//*********************INPUT FUNCTIONS*********************************

class info				    // Base class
{
protected:
    char  depcode[7],subcode[8],lecno[6];
    int no,year,month;
    int day;

public:
	int hr,min,sec;
    void roll(void)
    {
     cout<<depcode<<no;
     }
    void dayset(void);
    void timeset()
      {
		struct time b;
		gettime(&b);
		hr=b.ti_hour;
		min=b.ti_min;
		sec=b.ti_sec;
		cout<<hr<<":"<<min<<":"<<sec<<endl;
	  }
};

void info::dayset(void)				// sets the current day
	{
	  struct date a;
	  getdate(&a);
	  year=a.da_year;
	  month=a.da_mon;
	  day=a.da_day;
	  cout<<day<<"."<<month<<"."<<year<<endl;
	 }

class attendencein:virtual public info             // derived class
	{
	  char filename[15];
	  char folnam[15] ;
	  int tot, flag[120];
	  public:
	  void input(void);
	  void attend(void);
	  void folder(void);
	  void file(void);
	  void crefilename(int);
	  void sinfile(int pa);

	} ;

void attendencein::folder(void)
	{
	strcpy(folnam,depcode);			//copy depcode to folnam
	mkdir(folnam);				//make directory of folnam
	strcat(folnam,"\\");			//concatinates
	  }
// input data from user
void attendencein::input(void)
	{

closegraph();
	cout<<endl<<"ATTENDENCE SHEET"<<endl;
	cout<<"\n Enter the batch code and department code:(example 7003): ";
	cin>>depcode ;
	cout<<"\n Input subject code : ";
	 cin>>subcode;
	cout<<"\n Input class number : ";
	cin>>lecno;
	cout<<"\n Total student      : ";
	cin>>tot ;
	attend();
	file();
	clrscr();


	   }

// sets filename (filename is (subcode+lecno).txt)
void attendencein::crefilename(int i)
	 {
	  if(i==1)
	    {
	     strcpy(filename,depcode);
	    }
	else  if(i==0)
	    {
	 strcpy(filename,subcode);
	 strcat(filename,lecno);
	 strcat(filename,".txt");
	 sinfile(tot);
	    }

	 }

// saves data taken from user
void attendencein::file(void)
{
     char y,n;
     dayset();
     fstream k;
     crefilename(0);
     k.open(filename,ios::out);
     k<<"\tATTENDENCE SHEET\n\t----------------\n\n";
     k<<"\ndate"<<day<<"\\"<<month<<"\\"<<year<<endl ;
     k<<"\nBatch Code and Departmental Code : ";
     k<<depcode;
     k<<"\nSubject Code : ";
     k<<subcode;
     k<<"\nCLASS NO : ";
     k<<lecno;
     k<<"\n\nROLL NO\t\t\tATTENDENCE\n";
     int i=1;
     while(i<=(no-1))
     {
	k.fill(48);
	k<<"\n"<<depcode<<setw(2)<<i<<"\t\t\t";
	if(flag[i]==0)
	    k<<"absent";
	else
	    k<<"present";
	i++;
    }

    k.close();
}

// input absent or present
void attendencein::attend(void)
 {
 flushall();
    dayset();
    no=1;
    int t=tot;
    char a[4];
    strcpy(a,depcode);
    cout<<"\n(*if absent press 'TAB' and if present press any key if postponed operation press ""ESC"")\n";
    getch();
    clrscr();
    folder();
    cout<<"date"<<day<<"\\"<<month<<"\\"<<year<<endl ;
    cout<<"\nROLL NO\t\tATTENDENCE\n";

    while(no<=t)
     {
       flushall();
       cout.fill(48);
       cout<<"\n"<<a<<setw(2)<<no<<"\t\t";		// setw sets the width
       char c=getch();
	   if(c==9)
	 {
	  flag[no]=0;

	textcolor(2);
	cprintf("absent");
	  sinfile(0);
	  }
      else  if(c==27)
	  {
	  for(;no<=t;no++)
	      {
	       flag[no]=1;
	       sinfile(1);
	      }
	   break;
	  }
      else  if(c!=9)
	   {
	    flag[no]=1;
	    textcolor(5);
	    cprintf("present");
	    textcolor(5);
	    sinfile(1);
	    }
	no++;
	if(no==125)
	break;
	}
	getch();
}

//individual file setting part
void attendencein::sinfile(int pa)
{
    fstream x;
    char nam[10],name[20],*tmp;
    itoa(no,nam,10);
    strcpy(name,depcode);
    strcat(name,nam);
    tmp=new char[strlen(folnam)+strlen(name)+4];
    strcpy(tmp,folnam);
    strcat(strcat(tmp,name),".txt");
    x.open(tmp,ios::app);
    x<<pa;
    x.close();
    delete [] tmp;
}
//*********************************END OF INPUT FUNCTIONS********************

//**********************************OUTPUT FUNCTIONS*************************

class attendenceout:virtual attendencein,virtual info		//multiple class
	    {
	      int no;
	      public:
	      char filename[12];
	      void outputfile(void);
	      void outstfile(void);
	      void output(void);
	      void getdata(void);
	      void gettotal(void);
	      void getrollno(void)
		{
		cout<<"\n\ninput the roll no of student(exp 1 or 12)";
		cin>>no;
		}
	      void classdata(void);
	      void studentdata(void);
	      void table(void);
	    };
// input data
void attendenceout::getdata(void)
	       {
	       clrscr();
	       cout<<"\n Enter the batch code and department code: \n\n";
	       cout<<"\n BATCHCODE and DEPARTMENTAL CODE  : ";
	       cin>>depcode;
	       cout<<"\n Input subject code : ";
	       cin>>subcode;
	       cout<<"\n Input class number : ";
	       cin>>lecno;
	       }
// displays classdata
void attendenceout::outputfile(void)
	{
	 int i=0;

	 char p;
	 fstream u;
	 strcpy(filename,subcode);
	 strcat(filename,lecno);
	 strcat(filename,".txt");
	 u.open(filename,ios::in);
	 flushall();
	 if(!u)
	   {
	    cout<<"file error"<<filename;
	    exit(0);
	   }
	 clrscr();
	 cout<<"\n\nTHE CLASS PARTICIPATION SHEET IS BELOW :\n\n\n" ;
	 while(u)
	     {  if(i==660)
	       {
	     i=0;
	     getch();
	     clrscr();
	    }
	    delay(20);
	      u.get(p);
	      cout<<p;
	      i++;
	     }
	  u.close();
	 getch();

		}
//Choose class or student data to display
void attendenceout::output(void)
	    {
	    closegraph();
	    flushall();
	      while(1)
	      {
	     cout<<"\nENTER YOUR OPTION\n";
	     cout<<"TO SHOW CLASS ATTENDANCE RECORD(press enter)\nTO SHOW PRESEENT ATTENDANCE(press A)\nTO SHOW STUDENTWISE RECORD(press space)\nTO back press ESC\n";
	     char i;
	     i=getch();
	     if(i==65)
	     {
	    classdata();
	    exit(0);
	    }
	    else if(i==32)
	     {
	     studentdata();
	     exit(0);
	     }
	     else if(i==13)
	     {
	     table();
	     delay(100);
	     //exit();
	     }
	     else if(i==27)
	     exit(0);
	    }
	    getch();
	   }

void attendenceout::classdata(void)
	       {
		getdata();
		outputfile();
		getch();
	       }

void attendenceout::studentdata(void)
	    {
	     getdata();
	     getrollno();
	     outstfile();
	     getch();
	    }

void attendenceout::table(void)
	{
	int total;
	flushall();
	getdata();
     //	gettotal();
	cout<<"\n Input total student:";
	cin>>total;
	clrscr();
	cout<<"\n\t\t\t STUDENT ATTENDANCE RECORD \n" ;
	cout<<"\t\t\t _________________________\n\n";
	cout<< "ROLL NUMBER\tTOTAL CLASS\tPRESENT\t    ABSENT\t\tSTATUS % ";
       //	cout<<"\t"<<setw(3)<<"total \t"<<setw(3);
	cout<<"\n______________________________________________________________________________";

	float sum=0;
	for(int i=1;i<=total;i++)
	 {
	crefilename(1);
	    ifstream st;
	int ab=0,cl=0,pre=0;
	//int sum=0;
	char nam[10],name[20],file[20],ch;
	itoa(i,nam,10);
	strcpy(file,depcode);
	strcat(file,"\\");
	strcpy(name,depcode);
	strcat(name,nam);
	strcat(file,name);
	strcat(file,".txt") ;
	st.open(file);
	while(st)
	{
	st.get(ch);
	 if(ch==48)
	   ab++;
	 if(ch==49)
	   pre++;
	 }
	st.close();
	cl=ab+pre;
	float per=(pre*100/cl) ;
	sum=sum+per;

	cout<<endl<<depcode<<i<<"\t\t"<<  cl<<" \t\t"<<pre<<"\t\t"<<ab<<"\t\t"<<per;
	}
	cout<<"\n\nAVERAGE CLASS PERFORMANCE :  " <<(sum/total);
	getch();
	}

// displays student data
void attendenceout::outstfile(void)
	   {
	    crefilename(1);
	    ifstream st;
	int ab=0,cl=0,pre=0;
	char nam[10],name[20],file[20],ch;
	flushall();
	itoa(no,nam,10);
	strcpy(file,depcode);
	strcat(file,"\\");
	strcpy(name,depcode);
	strcat(name,nam);
	strcat(file,name);
	strcat(file,".txt") ;
	st.open(file);
	while(st)
	{
	st.get(ch);
	 if(ch==48)
	   ab++;
	 if(ch==49)
	   pre++;
	 }
	st.close();
	cl=ab+pre;
	float per=(pre*100/cl) ;

	cout<<"\nStudent data\n\n" ;
	cout<<"ROLL NUMBER :";
	delay(50);
	cout<<no <<"\n";
	cout<<"TOTAL CLASS :";
	delay(50) ;
	cout<<cl<<"\n";
	cout<<"PRESENT  :";
	delay(50);
	cout<<pre<<"\n";
	cout<<"ABSENT   :";
	delay(50);
	cout<<ab<<"\n";
	cout<<"TOTAL CLASS PERSENTAGE:";
	delay(150);
	cout<<per<<endl;
       //	return 1;
	getch();
	}
//*****************************END OF OUTPUT FUNCTION**********************************

//**************************MAIN FUNCTION*************************************

void  main()
    {
    eee:
     int g = DETECT , d;
     initgraph ( &g , &d , "..\\bgi" );
      G();
     Intro();
     cleardevice();
     info obj;
     gotoxy(34,8);
     cout<<"DATE:";
     obj.dayset();
     gotoxy(34,9);
     cout<<"TIME:";
     obj.timeset();
    // attendencein x;
passwordmenu();
get_password();


getch();
}

//*********************************GRAPHICS DESIGN*************************
// starting graphics
void Intro()
{
   int i;
   char pattern[8] ={0xfe,0xbc,0xda,0xe4,0xe2,0xc0,0x88,0x00};
   setfillpattern(pattern,1);
   bar(0,0,640,480);
   settextstyle(1,0,3);
   outtextxy(30,200,"WELCOME TO ATTENDANCE MANAGEMENT SYSTEM");
   settextstyle(1,0,5);
   setcolor(10);
   getch();
   setcolor(0);
   for(i=0;i<=320;i++)
   {
   rectangle(0+i,0,640-i,480);
   delay(5);
   }

}
// starting graphics
void G()
{
   int gdriver = DETECT, gmode, errorcode;
   initgraph(&gdriver, &gmode, "..\\bgi");
   errorcode = graphresult();
   if (errorcode != grOk)
   {
      printf("Graphics error: %s", grapherrormsg(errorcode));
      exit(1);
   }
   area=imagesize(150,70,240,180);
   p=malloc(area);
   if(p==NULL)
   {
   closegraph();
   exit(1);
   }
}
// display menu graphics
void drawMenu ( int selected , int defCol , int selCol )
{
int x = 250;
int y = 100;
int width = 190;
int height = 30;
int i;
int TotalOptions = 6;
char menu_option[6][65]= {
"   INPUT RECORD    ",
"  DISPLAY RECORD  ",
"  CHANGE PASSWORD  ",
"       HELP    ",
"     ABOUT US       ",
"       EXIT          "
};
setcolor ( WHITE );
settextstyle(1,0,1.1);
for ( i = 1; i <= TotalOptions; i++ )
{
if ( i == selected )
setfillstyle ( 1 , selCol );
else
setfillstyle ( 1 , defCol );
bar ( x-5 , y , x + width , y + height );
rectangle ( x-5 , y , x + width , y + height );
outtextxy ( x , y , menu_option[i - 1] );
y = y + height + 30;
}
}
// display menu screen
int menu()
{
int ch;
int selected = 1;
int TotalOptions = 6;
settextstyle(1,0,3);
outtextxy(155,40,"ATTENDANCE MANAGEMENT SYSTEM");
//printf("ATTENDENCE MANAGEMENT SYSTEM");
gotoxy(20,5);
printf("___________________________________________________");
gotoxy(32,29);
//printf("USE UP or DOWN ARROW TO SELECT");

setbkcolor(BLUE);
do
{
ch = getch();
if ( ch == DOWN_ARROW )
{
selected = selected >= TotalOptions ? 1 : selected + 1;
drawMenu ( selected , RED , GREEN );
}
else if ( ch == UP_ARROW )
{
selected = selected < 2 ? TotalOptions : selected - 1;
drawMenu ( selected , RED , GREEN );
}

}while ( ch != 13 );

return selected;
}
// display finish graphics
void finish()
{
   setbkcolor(1);
   for(int i=0;i<=220;i++)
   {
   rectangle(0+i,0+i,640-i,480-i);
   delay(10);
   }
   for(i=0;i<=220;i++)
   {
   rectangle(100+i,100,540-i,380);
   delay(8);
   }
   closegraph();
}

//***********************************PASSWORD FUNCTIONS************************
// checks password & display menu.
void get_password()
{
   fstream st;
	char ch;
	char pass[10];
    char temp_passP[25];
    int i=0;
    gotoxy(25,18);
     while(1)
    {
	    temp_passP[i]=getch();
	    if(temp_passP[i]==13)
	    break;
	    else if(temp_passP[i]==8)
	    {
		if(i!=0)
		{
		printf("\b \b");
		i--;
		} else {
		printf("\a");
		}
	    }
	    else
	    {
		printf("*");
		*(pass+i) = temp_passP[i];
		i++;
	    }
	     *(pass+i)='\0';
     }
	st.open("password.txt",ios::in);
	int m=0;
	char n[10];
	while(st)
	{
	st.get(ch);
	n[m]=ch;
	m++;
	}
	n[m-1]=NULL;
	if(strcmp(n,pass)==0)
	{
	flushall();
	cleardevice();
	 int selected=1;
	 attendencein a;
	 attendenceout b;
	drawMenu ( selected , RED , GREEN );
	int selected_option;
	Start:          // goto label
	flushall();
	selected_option=menu();
	switch ( selected_option )    //***********RUNNING THE SYSTEM********
	{
	case 1:
	 a.input();
	 goto Start;

	case 2:
	 b.output();
	 goto Start;
	 case 3:
	 change_password();
	 break;
	 case 4:
	 help();
	 goto Start;
	// break;
	 case 5:
	 about_us();
	 goto Start;
      //	 break;
	default:
	 finish();
	 gotoxy(18,13);
	 printf("THANK YOU FOR USING ATTENDENCE SOFTWARE");
	  break;
	}
	goto Start;
	}
	else
	{
	cleardevice();
	char c;
	cout<<"\nHave y forget u'r password \nPress y to Try Again \nPress n to Quit";
	scanf("%c",&c);
	if(c=='y' || c=='Y')
	{

	cleardevice();
	passwordmenu();
	get_password();
	}
	else
	{
	exit(0);
	}
	}
       cleardevice();
       st.close();
}
//  sets password graphics
void passwordmenu ( )
{
int x = 150;
int y = 150;
int width = 380;
int height = 60;
char passname[20];
char menu_option[50]= {" ENTER PASSWORD "};
setcolor ( WHITE );

for (int i = 1; i < 2; i++ )
{
setfillstyle ( 1 , RED );
bar ( x , y , x + width , y + height );
rectangle ( x , y , x + width , y + height );
outtextxy ( x -1 , y + 10 , menu_option );
y = y + height ;
gotoxy(25,20);
cout<<"______________________________";
}
}
// to change password
void change_password()
{  cleardevice();
   fstream x;
	char pass[20];
    char temp_passP[25];
    int i=0;
    gotoxy(30,11);
    cout<<"ENTER NEW PASSWORD";
    gotoxy(30,12);
     while(1)
    {
	    temp_passP[i]=getch();
	    if(temp_passP[i]==13){break;}
	    else if(temp_passP[i]==8)
	    {
		if(i!=0) {
		printf("\b \b");
		i--;
		} else {printf("\a");}
	    }
	    else
	    {
		printf("*");
		*(pass+i) = temp_passP[i];
		i++;
	    }
	     *(pass+i)='\0';
     }
    gotoxy(30,13);
    cout<<"NEW PASSWORD SUCCESSFULLY ADDED";
    delay(400);
    x.open("password.txt",ios::out);
    x<<pass;
    x.close();
}
//***********************END OF PASSWORD FUNCTIONS*************************
// shows heading on the top
void show_header()
{
setcolor ( RED );
settextstyle (1, 0 , 3 );
outtextxy ( 62 , 46 , " ATTENDENCE MANAGEMENT SYSTEM " );
setcolor ( YELLOW );
outtextxy ( 60 , 48 , " ATTENDENCE MANAGEMENT SYSTEM " );
}
//*****************************DELETE FUNCTION******************************
// deleting file
void help()
{
cleardevice();
//setbkcolor(1);
show_header();
cout<<"*************************** USER MANUAL *************************************";
cout<<"\n-NO DUPLICATIONS OF FILES ARE ALLOWEDED";
cout<<"\n-USE UP AND DOWN ARROW TO SCROLL\n-TO SELECT PRESS ENTER";
cout<<"\n-ENTER BATCH CODE AND DEPARTMENT CODE (eg.7003),WHERE 70 IS BATCH CODE  AND 03 IS DEPARTMENT CODE";
cout<<"\n-ENTER SUBJECT NAME OR CODE, EG. MATHEMATICS OR 120";
cout<<"\n-ENTER ROOM NUMBER";
cout<<"\n-THE ATTENDANCE RECORDS ARE STORED IN TEXT FILE UNDER THE FOLDER NAME OF BATCH AND DEPARTMENT CODE IN HARD DISK DRIVE";
cout<<"\n-RECORDED DATA ARE DIFFER FROM INDIVIDUAL SUBJECT NAME OR CODE";
getch();
exit(0);
}
//*********************************INFORMATION MODULE***************
// display on screen: about us
void about_us()
{
cleardevice();
setbkcolor(1);
show_header();
setcolor (RED);
cout<<"\n";
cout<<"*************************** ABOUT US ********************************\n";
cout<<"\nSUPERVISER: SHRIRAM KHAITU\n\n";
cout<<"CREATED BY:\n";
cout<<" SHIVA SHRESTHA\n SURESH TYATA\n SANJAY SHAKYA\n SHREE KRISHNA PRAJAPATI";
cout<<"\n\n";
getch();
exit(0);
}