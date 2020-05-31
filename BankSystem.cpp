//
// BankSystem.cpp : This file contains the 'main' function. Program execution begins and ends there.
// http://www.cppforschool.com/project/banking-system-project.html
// http://www.cplusplus.com/doc/tutorial/files/
//

#include "pch.h"
#include <iostream>
#include "Header.h"

int main()
{
    std::cout << "Hello World!\n"; 
	int p = writeFile();
	int q = addToFile();
	int r = readFile();
}