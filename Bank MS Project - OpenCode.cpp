//***************************************************************
//                   HEADER FILE USED IN PROJECT - OpenCode
//****************************************************************

// input/output library refers to a family of class templates and supporting functions in the C++ Standard Library that implement stream-based input/output capabilities
#include<iostream>

//Input/output stream class to operate on files
#include<fstream>

//header file of the C Standard Library declares several functions that are useful for testing and mapping characters
#include<ctype.h>

//Header providing parametric manipulators (like setw() in line 78)
#include<iomanip>

//The C programming language provides many standard library functions for file input and output.
#include<stdio.h>

using namespace std;

//****************************************************************
//                   CLASS USED IN PROJECT - OpenCode
//****************************************************************

class account
{
	int acno;
	char name[50];
	int deposit;
	char type;
public:
	void create_account(int accno)
	{
		acno = accno;
		cout<<"\nEnter The Name of The account Holder : ";
		cin.ignore();
		gets(name);
		cout<<"\nEnter Type of The account (C/S) : ";
		cin>>type;
		type=toupper(type);
		cout<<"\nEnter The amount: ";
		cin>>deposit;
		cout<<"\n\n\n === Account Created... ===";
	}	//function to get data from user

	void show_account()
	{
		cout<<"\nAccount No. : "<<acno;
		cout<<"\nAccount Holder Name : ";
		cout<<name;
		cout<<"\nType of Account : "<<type;
		cout<<"\nBalance amount : "<<deposit;
	}	//function to show data on screen

	void modify()
	{
		cout<<"\nThe account No."<<acno;
		cout<<"\n\nEnter The Name of The account Holder : ";
		cin.ignore();
		gets(name);
		cout<<"\nEnter Type of The account (C/S) : ";
		cin>>type;
		type=toupper(type);
		cout<<"\nEnter The amount : ";
		cin>>deposit;
	}   //function to get new data from user

	void dep(int x){	//function to accept amount and add to balance amount
		deposit+=x;
	}

	void draw(int x){	//function to accept amount and subtract from balance amount
		deposit-=x;
	}

	void report(){	//function to show data in tabular format
		cout<<acno<<setw(14)<<name<<setw(15)<<type<<setw(10)<<deposit<<endl;
	}

	int retacno(){	//function to return account number
		return acno;
	}

	int retdeposit(){	//function to return balance amount
		return deposit;
	}

	char rettype(){	//function to return type of account
		return type;
	}

};         //class ends here


//***************************************************************
//    	function declaration - OpenCode
//****************************************************************
void write_account();	//function to write record in binary file
void display_sp(int);	//function to display account details given by user
void modify_account(int);	//function to modify record of file
void delete_account(int);	//function to delete record of file
void display_all();		//function to display all account details
void deposit_withdraw(int, int); // function to desposit/withdraw amount for given account
void intro();	//introductory screen function

//***************************************************************
//    	THE MAIN FUNCTION OF PROGRAM - OpenCode
//****************************************************************


int main()
{
	int num, ch;

	intro();
	do
	{
		cout<<endl;
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. NEW ACCOUNT                     --              EJAD HESAB .01";
		cout<<"\n\n\t02. DEPOSIT AMOUNT                  --              SEPORDE(AFZAYESH) VAJH .02";
		cout<<"\n\n\t03. WITHDRAW AMOUNT                 --              BARDASHT(KAHESH) VAJH .03";
		cout<<"\n\n\t04. BALANCE ENQUIRY                 --              ESTELAM MOJODI .04";
		cout<<"\n\n\t05. ALL ACCOUNT HOLDER LIST         --              FEHREST HESAB HA .05";
		cout<<"\n\n\t06. CLOSE AN ACCOUNT                --              BASTAN HESAB .06";
		cout<<"\n\n\t07. MODIFY AN ACCOUNT               --              ESLAH HESAB .07";
		cout<<"\n\n\t08. EXIT                            --              Khoroj .08";
		cout<<"\n\n\n\tSelect Your Option (1-8) ";
		cin>>ch;
		cout<<endl;

		switch(ch)
		{
		case 1:
			write_account();
			break;

		case 2:
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 1);
			break;

		case 3:
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 2);
			break;

		case 4:
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			display_sp(num);
			break;

		case 5:
			display_all();
			break;

		case 6:
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			delete_account(num);
			break;

		case 7:
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			modify_account(num);
			break;

		case 8:
			cout<<"\n\n\tThanks for using bank management system";
			break;

		default:
		    cout<<"Select Your Option (1-8): ";
            break;
		}

		cout << "\n\n" << "--------------------------" <<endl;
		system("Pause");

		system("CLS");

	}while(ch!=8);


	system("CLS");
	cout << "Learn to Code with OpenCode";
	return 0;
}


//***************************************************************
//    	function to write in file - OpenCode
//****************************************************************

void write_account()
{

	account ac;
	fstream inFile;
	bool flag = true;
	int ac_number;

	inFile.open("account.dat", ios::binary | ios::in);

	cout << "Enter Your Account Number: ";
	cin >> ac_number;

	while(inFile.read((char *) &ac, sizeof(account)))
	{
		if(ac.retacno() == ac_number)
			flag = false;
	}

	inFile.close();

	fstream outFile;
	outFile.open("account.dat", ios::binary | ios::out | ios::app);

	if(flag){
		account new_ac;

		new_ac.create_account(ac_number);
		outFile.write((char *) &new_ac, sizeof(account));
	}else
		cout << "\n\nAccount number exist..." << endl;

	outFile.close();

}

//***************************************************************
//    	function to read specific record from file - OpenCode
//****************************************************************

void display_sp(int n)
{
	account ac;
	int flag=0;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";
	while(inFile.read((char *) &ac, sizeof(account)))
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			flag=1;
		}
	}
	inFile.close();
	if(flag==0)
		cout<<"\n\nAccount number does not exist";
}


//***************************************************************
//    	function to modify record of file - OpenCode
//****************************************************************

void modify_account(int n)
{
	int found=0;
	account ac;
	fstream File;
	File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(File.read((char *) &ac, sizeof(account)) && found==0)
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			cout<<"\n\nEnter The New Details of account"<<endl;
			ac.modify();
			int pos=(-1)*sizeof(account);
			File.seekp(pos,ios::cur);
			File.write((char *) &ac, sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=1;
		}
	}
	File.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
}

//***************************************************************
//    	function to delete record of file - OpenCode
//****************************************************************


void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read((char *) &ac, sizeof(account)))
	{
		if(ac.retacno()!=n)
		{
			outFile.write((char *) &ac, sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\n\tRecord Deleted ..";
}

//***************************************************************
//    	function to display all accounts deposit list - OpenCode
//****************************************************************

void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.      NAME            Type    Balance\n";
	cout<<"====================================================\n";
	while(inFile.read((char *) &ac, sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}

//***************************************************************
//    	function to deposit and withdraw amounts - OpenCode
//****************************************************************

void deposit_withdraw(int n, int option)
{
	int amt=0;
	int found=0;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(File.read((char *) &ac, sizeof(account)) && found==0)
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\n\n\tTO DEPOSITE AMOUNT ";
				cout<<"\n\nEnter The amount to be deposited";
				cin>>amt;
				ac.dep(amt);
			}
			if(option==2)
			{
				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\n\nEnter The amount to be withdraw";
				cin>>amt;
                ac.draw(amt);
			}
			int pos=(-1)* sizeof(ac);
			File.seekp(pos,ios::cur);
			File.write((char *) &ac, sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=1;
	       }
	}
	File.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
}


//***************************************************************
//    	INTRODUCTION FUNCTION - OpenCode
//****************************************************************


void intro()
{
	cout<<"\n\t\t BANK MANAGEMENT SYSTEM - Created by OpenCode\n\n";
}

//***************************************************************
//    			END OF PROJECT - OpenCode
//***************************************************************
