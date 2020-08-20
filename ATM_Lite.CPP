/*Made By Team Rogue: To be used only with Turbo C++.
Functions like random and randomize are incompatible with Dev C++.
Download Turbo C++ from: https://turboc7.blogspot.com
Extract and install the software.
Place this source file in C:/TC/bin folder and run it using turbo c++ app.
*/


#include<fstream.h>	//for file i/o
#include<stdio.h>	//for gets()
#include<iostream.h>	//for i/o functions
#include<stdlib.h>	//for system() function
#include<process.h>	//for using exit(0)
#include<string.h>	//for using string operations
#include<ctype.h>	//for using character operations


class user;
class account;
class transaction;
class current_acc;
class savings_acc;



class user
{
public:
char name[25];
int pass;
};

class account:public user
{
public:
int acno,bal;
char type;

void crtacc()
{
cout<<"\n\nEnter The Name of The account Holder:\t";
gets(name);
cout<<"\nEnter Type of The account (C/S):\t";
cin>>type;
type=toupper(type);
cout<<"\nEnter a password for your account:\t";
cin>>pass;
cout<<"\nEnter The Initial amount:\t\t ";
cin>>bal;
accno_gen();
cout<<"\nYour Account no is:"<<acno<<"\n\n\nPlease note it down for future refrence.";
cout<<"\n\n\nAccount Created..";}
void accno_gen();

int chkpass(int p)
{
	if(p==pass)
	return 1;
return 0;
}

void display()
{
cout<<"\nAccount No. : "<<acno;
cout<<"\nAccount Holder Name : ";
cout<<name;
cout<<"\nType of Account : "<<type;
cout<<"\nBalance amount : "<<bal;
}
};

void account::accno_gen()
{
randomize();
int a=0;
acno=0;
	for(int i=0;i<3;i++)
	{
	a=random(10);
	acno+=a;
	acno*=10;
	}
}



class current_acc:public account
{public:
friend transaction;
	int chk_min_bal(int num)
	{
		if((bal-num)>=1000)	//min balance to be maintained in current acc is 1000
		return 1;	//for true
	return 0;		//for false
	}
};

class savings_acc:public account
{public:
friend transaction;	
	int chk_min_bal(int num)
	{
		if(bal-num>=0)	//min balance to be maintained is 0, should not be -ve
		return 1;	//for true 
	return 0;		//for false
	}
};


class transaction:public account
{public:
	void withdraw(int amt)
	{
	current_acc c;
	savings_acc s;
	int flag=0;
		if(type=='c')	//if account type is current then check if amount is not going below 1000
		{
			if(c.chk_min_bal(amt)==1)
			flag=1;
		}
		else		//if account type is savings then check if amount is not going below 0
		{
			if(s.chk_min_bal(amt)==1)
			flag=1;
		}
		if(flag==1)
		{
		system("cls");
		bal-=amt;
		cout<<"Processing..."; 
		system("pause");
		}
		else
		{
		system("cls");
		cout<<"Insufficient Balance!!";
		system("pause");
		}
	}
	void deposit(int amt)
	{
	bal+=amt;
	cout<<"Processing"; 
	system("pause");
	}
};








void intro()	//Greeting system before the program starts
{
system("cls");
cout<<"Automated Teller Machine";
cout<<"\n\tMADE BY :Team Rogue\n";
system("pause");
}

void outro()	//Displays thanks on program exit
{
system("cls");
cout<<"\t\tThanks for using ATM\n";
system("pause");
exit(0);
}

void write_account()	//for creation of new account
{
account ac;
ofstream outFile;
outFile.open("account.dat",ios::binary|ios::app);
ac.crtacc();
outFile.write((char*)&ac, sizeof(account));
outFile.close();
}

void deposit_withdraw(int n, int option)	//for deposit or withdraw
{
int amt;
char found[]="false";
transaction ac;
fstream File;
File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
	cout<<"File could not be opened !! Press any Key...";
	return;
	}
	while(!File.eof() && strcmp(found,"false")==0)
	{
	File.read((char *)&ac, sizeof(account));
		if(ac.acno==n)
		{
		cout<<"\nEnter password:\t";
		int p;
		cin>>p;
			if(ac.chkpass(p)==1)
				{
				ac.display();
				if(option==1)
				{
				cout<<"\n\n\tTO DEPOSIT AMOUNT ";
				cout<<"\n\nEnter The amount to be deposited";
				cin>>amt;
				ac.deposit(amt);
				}
				if(option==2)
				{
				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\n\nEnter The amount to be withdraw";
				cin>>amt;
					if(amt>ac.bal)
					cout<<"Insufficient balance";
					else
					ac.withdraw(amt);
				}
			}
			else
			{
			cout<<"Wrong Password\n\nExiting to Main Menu ";
			system("pause");
			return;
			}
		int pos=(-1)*(int)(sizeof(ac));
		File.seekp(pos,ios::cur);
		File.write((char *)&ac, sizeof(account));
		cout<<"\n\n\t Record Updated";
		strcpy(found,"true");
		}
	}
File.close();
	if(strcmp(found,"false")==0)
	cout<<"\n\n Record Not Found ";
}

void display_sp(int n)	//display account details except password
{
account ac;
char flag[]="false";
ifstream inFile;
inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
	cout<<"File could not be opened !! Press any Key...";
	return;
	}
cout<<"\nBALANCE DETAILS\n";
	while(inFile.read((char*)&ac, sizeof(account)))
	{
		if(ac.acno==n)
		{
		cout<<"\nEnter password:\t";
		int p;
		cin>>p;
			if(ac.chkpass(p)==1)
			{
			ac.display();
			strcpy(flag,"true");
			}
			else
			{
			cout<<"Wrong Password\n\nExiting to Main Menu ";
			system("pause");
			inFile.close();
			return;
			}
		}
	}
inFile.close();
	if(strcmp(flag,"false")==0)
	cout<<"\n\nAccount number does not exist";
}


void main()
{
system("cls");		//clear any previous output on screen
char ch;		//for making choice input
int num;		//for account no. related operations inside the program
intro();		//Introduction before the program starts
	do
	{
	system("cls");	//clear any previous output on screen
	cout<<"\n\n\n\tMAIN MENU";
	cout<<"\n\n\t01. NEW ACCOUNT";
	cout<<"\n\n\t02. DEPOSIT AMOUNT";
	cout<<"\n\n\t03. WITHDRAW AMOUNT";
	cout<<"\n\n\t04. BALANCE ENQUIRY";
	cout<<"\n\n\t05. EXIT";
	cout<<"\n\n\tSelect Your Option (1-5) ";
	cin>>ch;
	system("cls");
		switch(ch)
		{
		case '1':write_account();
			 break;
		case '2':cout<<"\n\nEnter The account No. : "; cin>>num;
			 deposit_withdraw(num, 1);
			 break;
		case '3':cout<<"\n\nEnter The account No. : "; cin>>num;
			 deposit_withdraw(num, 2);
			 break;
		case '4':cout<<"\n\nEnter The account No. : "; cin>>num;
			 display_sp(num);
			 break;
		case '5':outro();
			 break;
		default :system("cls");
			 cout<<"Wrong Choice!!";
			 system("pause");
		}

	cin.ignore();
	system("pause");	//waits for a key to be pressed
	}while(ch!='5');
}


