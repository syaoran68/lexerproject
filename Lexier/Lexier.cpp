// Lexier.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <list>
#include <cstring>
#include <string>
#include <vector>


using namespace std;

int letterChecker(char ch)
{
	int result = 0;


	// Alphabet checking condition
	// 1 = letter
	// 2 = number
	// 3 = special charc
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
	{
		result = 1;
	}
	else if (ch >= '0' && ch <= '9')
	{
		result = 2;
	}
	else
		result = 3;
	return result;
}

void tokenChecker(string &holder, vector<string> &identifierList, vector<string> &separatorList, char &c, bool &StateChange)
{

}

void stateChanger(char c, string &holder, int &state, vector<string> &identifierList, vector<string> &separatorList) // Initial State will essentially accept anything
{
	bool StateChange = false;
	int currentLetterStatus = letterChecker(c);
	switch (currentLetterStatus) {
	case 1:
		if (state == 4)
		{
			holder = holder + c;
			tokenChecker(holder, identifierList, separatorList, c, StateChange);
			state = 5;
			break;
		}
		else if (state == 5)
		{
			holder = holder + c;
			tokenChecker(holder, identifierList, separatorList, c, StateChange);
			break;
		}
		else
		{
			holder = holder + c;
			state = 2;
			tokenChecker(holder, identifierList, separatorList, c, StateChange);
			break;
		}
	case 3:
		if (state == 5)
		{
			tokenChecker(holder, identifierList, separatorList, c, StateChange);
			state = 1;
			break;
		}
		else
		{
			holder = holder + c;
			state = 4;
			tokenChecker(holder, identifierList, separatorList, c, StateChange);
			break;
		}
	case 4:
		holder = holder + c;
		tokenChecker(holder, identifierList, separatorList, c, StateChange);
		break;
		
		// nothing happens if its not a letter number or special character
	}
}

int main()
{
	//loading of the token list file
	ifstream token;
	token.open("D:\\Projects\\Lexier\\Lexier\\misc\\tokens.txt");
	if (!token)
	{
		cerr << "Unable to open file token.txt";
		exit(1);
	}
	
	vector<string> identifierList;
	vector<string> separatorList;
	string inputHolder;
	while (getline(token, inputHolder))
	{
		//getline(token, inputHolder);
		if (inputHolder == "IDENTIFIER")
		{
			while (getline(token, inputHolder))
			{
				if (inputHolder == "SEPARATOR")
					break;
				else
					identifierList.push_back(inputHolder);
			}
		}
		if (inputHolder == "SEPARATOR")
		{
			while (getline(token, inputHolder))
			{
				if (inputHolder == "ENDFILE")
					break;
				else
					separatorList.push_back(inputHolder);
			}
		}

		if (inputHolder == "OPERATOR")
		{
			while (getline(token, inputHolder))
			{
				if (inputHolder == "ENDFILE")
					break;
				else
					separatorList.push_back(inputHolder);
			}
		}
		
		if (inputHolder == "COMMENT")
		{
			while (getline(token, inputHolder))
			{
				if (inputHolder == "ENDFILE")
					break;
				else
					separatorList.push_back(inputHolder);
			}
		}
		break;
	} 
	token.close(); 

	//reading the file character by character to find
	ifstream file;
	file.open("D:\\Projects\\Lexier\\Lexier\\misc\\test.txt");
	if (!file)
	{
		cerr << "Unable to open file test.txt";
		exit(1);
	}
	char c;
	string holder;
	int state = 1;

	//visual helpers
	cout << "Token" << "\t" << "Lexeme" << endl;
	cout << "----------------------------------" << endl;

	while (file >> c)
	{
		stateChanger(c, holder, state, identifierList, separatorList);
	}


	system("pause");
}





//State numbers:
//initial state = 1
//second state = 2; this accepts any letter
//letter state = checks if it matches a token if such prints out.