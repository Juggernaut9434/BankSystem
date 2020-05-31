//
// BankSystem.cpp : This file contains the 'main' function. Program execution begins and ends there.
// http://www.cppforschool.com/project/banking-system-project.html
// http://www.cplusplus.com/doc/tutorial/files/
//

#include "pch.h"
#include <iostream>
#include "Header.h"
#include <fstream>
#include<cctype>
#include<iomanip>
using namespace std;

// *******************************************
// Class for Account definition
// *******************************************

class account 
{
	int acno;	// account number
	char name[50];	// account name
	int deposit;
	char type;

public:
	// by adding const to the end of function, it is cached for later

	//withdraw money (int n), subtract from blance
	void withdraw(int);
	//deposit money (int n)
	void dep(int);
	//create account
	void create_account();
	//show account details CONST
	void show_account() const;
	//modify account
	void modify();
	//report - show data in tabular format CONST
	void report() const;
	//getAccountNumber CONST
	int getAcNo() const;
	//get balanceAmount CONST
	int getBal() const;
	//getAccountType CONST
	char getAcType() const;
};

// *******************************************
// Class methods definitions
// *******************************************
void account::create_account()
{
	// show / direct user to enter details
	cout << "\nEnter the account No. :";
	cin >> acno;
	cout << "\nEnter account Holder Name :";
	cin.ignore();
	cin.getline(name, 50);	// sets size of input to 50 characters
	cout << "\nEnter Type of Account (Checking/Saving) as C or S :";
	cin >> type;
	type = toupper(type);
	cout << "\nEnter Inital amount(>= 500 for Saving and >=1000 for checking) :";
	cin>>deposit;
	cout << "\n\nAccount Created...";
}
void account::show_account() const
{
	cout << "\nAccount No. : " << acno;
	cout << "\nAccount Holder Name : " << name;
	cout << "\nType of Account : " << type;
	cout << "Balance amount : " << deposit;
}
void account::modify()
{
	cout << "\nAccount No. :" << acno;
	cout << "\nEnter account Holder Name :";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\nModify Type of Account (C/S) :";
	cin >> type;
	type = toupper(type);
	cout << "\nModify Balance amount :";
	cin >> deposit;
}
void account::withdraw(int n)
{
	deposit += n;
}
void account::dep(int n)
{
	deposit -= n;
}
void account::report() const
{
	//setw(int) is set width
	cout << acno << setw(10) << " " << name << setw(10) << " " << type << setw(6) << deposit << endl;
}
int account::getAcNo() const
{
	return acno;
}
int account::getBal() const
{
	return deposit;
}
char account::getAcType() const
{
	return type;
}

// *******************************************
// function declaration
// *******************************************
void write_account();
void display_sp(int);	// specific record
void modify_account(int);
void delete_account(int);
void display_all();
void deposit_withdraw(int, int);
void intro();

// *******************************************
// File Operation Functions
// *******************************************
void write_account()
{
	// need account
	account ac;
	//output to file, binary, append
	ofstream outFile;
	outFile.open("account.dat", ios::binary | ios::app);
	// call account's create_account();
	ac.create_account();
	// put into file
	// We need to cast because write expects char
	outFile.write(reinterpret_cast<char *>(&ac), sizeof(account));
	//close file
	outFile.close();
}
void display_sp(int n)
{
	// display specific record, n as acno, using show_account()
	account ac;
	bool exist_flag;	// account exists flag, defualt 0 or false
	ifstream inFile;
	inFile.open("account.dat", ios::binary);
	
	// make sure file exists
	if (!inFile)
	{
		cout << "File could not open !! Press any Key...";
		return;
	}
	cout << "\nBALANCE DETIALS\n";

	// Read the file using .eof()
	while (!inFile.eof())
	{
		if (ac.getAcNo == n)
		{
			ac.show_account();
			exist_flag = true;
		}
	}
	inFile.close();
	if (!exist_flag)	//exist_flag is false
		cout << "\n\nAccount Number does not exist";
}
void modify_account(int n)
{
	account ac;
	bool found_flag;
	fstream File;
	File.open("account.dat", ios::binary | ios::in || ios::out);
	if (!File)
	{
		cout << "File could not open !! Press any Key...";
		return;
	}
	while (!File.eof() && !found_flag)
	{
		// read file contents
		File.read(reinterpret_cast<char *>(&ac), sizeof(account));
		if (ac.getAcNo == n)
		{
			ac.show_account();
			cout << "\n\nEnter the New Details of account" << endl;
			ac.modify();
			// have a pointer at the start of the account
			int pos = (-1) * static_cast<int>(sizeof(account));
			// goes to the line before data entry
			File.seekp(pos, ios::cur);
			// writes over old data
			File.write(reinterpret_cast<char *>(&ac), sizeof(account));
			
			cout << "\n\n\t Record Updated";
			found_flag = true;
		}
	}
	File.close();
	if (!found_flag)
		cout << "\n\nRecord Not Found";
}
void delete_account(int n)
{
	bool found;
	//account declare
	account ac;
	//open 2 files, one as input, one as output
	ifstream inFile;
	inFile.open("account.dat", ios::binary);
	ofstream outFile;
	outFile.open("temp.dat", ios::binary | ios::out);

	if (!inFile)
	{
		cout << "File could not open !! Press any Key...";
		return;
	}

	//read file line by line starting at begining
	inFile.seekg(0, ios::beg);
	while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(account)))
	{
		// everything but the account number
		if (ac.getAcNo != n)
		{
			outFile.write(reinterpret_cast<char *>(&ac), sizeof(account));
			found = true;
		}
	}

	//close both files
	inFile.close();
	outFile.close();
	//delete one file
	remove("account.dat");
	//rename temp as original
	rename("temp.dat", "account.dat");
	cout << "\n\n\tRecord Deleted ...";
}
void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat", ios::binary);

	if (!inFile)
	{
		cout << "File could not open !! Press any Key...";
		return;
	}

	cout << "\n\n\tACCOUNT HOLDER LIST\n\n";
	cout << "====================================================\n";
	cout << "A/c no.      NAME           Type  Balance\n";
	cout << "====================================================\n";
	while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}
void deposit_withdraw(int n, int option)
{
	int amt;
	bool found;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary | ios::out | ios::in);

	if (!File)
	{
		cout << "File could not open !! Press any Key...";
		return;
	}

	while (File.eof() && !found)
	{
		File.read(reinterpret_cast<char *>(&ac), sizeof(account));
		if (ac.getAcNo == n)
		{
			ac.show_account();
			if (option == 1)
			{
				cout << "\n\n\tTO DEPOSIT AMOUNT ";
				cout << "\n\nEnter The amount to be deposited";
				cin >> amt;
				ac.dep(amt);
			}
			if (option == 2)
			{
				cout << "\n\n\tTO WITHDRAW AMOUNT ";
				cout << "\n\nEnter The amount to be withdraw";
				cin >> amt;
				int bal = ac.getBal() - amt;
				if ((bal < 500 && ac.getAcType() == 'S') || (bal < 1000 && ac.getAcType() == 'C'))
					cout << "Insufficience balance";
				else
					ac.withdraw(amt);
			}
			// modify account in file
			int pos = (-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout << "\n\n\t Record Updated";
			found = true;
		}
	}
	File.close();
	if (!found)
		cout << "\n\n Record Not Found ";
}



// *******************************************
//
// *******************************************

int main()
{
    std::cout << "Hello World!\n"; 
	int p = writeFile();
	int q = addToFile();
	int r = readFile();
}