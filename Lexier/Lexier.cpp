#include "pch.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <ctype.h>

using namespace std;

int check_letter(char c)
{
	if (isalpha(c))
	{
		return 1;
	}
	else if (isdigit(c))
	{
		return 2;
	}
	else if (ispunct(c))
	{
		return 3;
	}
	else
	{
		return 0;
	}
}

void check_state(char c, int &state, string &temp, vector<string> keywords, vector<string> tokens, ofstream& myfile)
{
	switch (state)
	{
	case 2:
		for (int i = 0; i < keywords.size(); i++)
		{
			if (temp == keywords[i])
			{
				cout << fixed << left << setw(15) << tokens[0] << "\t" << temp << endl;
				myfile << fixed << left << setw(15) << tokens[0] << "\t" << temp << endl;

				state = 0;
				temp = "";
				break;
			}
		}
		if (ispunct(c))
		{
			if (c == '$')
			{
				temp.push_back(c);
				cout << fixed << left << setw(15) << tokens[1] << "\t" << temp << endl;
				myfile << fixed << left << setw(15) << tokens[1] << "\t" << temp << endl;

				state = 0;
				temp = "";
			}
			else
			{
				cout << fixed << left << setw(15) << tokens[1] << "\t" << temp << endl;
				myfile << fixed << left << setw(15) << tokens[1] << "\t" << temp << endl;
				temp = "";
				state = 4;
				check_state(c, state, temp, keywords, tokens, myfile);
			}
		}
		break;
	case 3:
		if (ispunct(c))
		{
			cout << fixed << left << setw(15) << tokens[2] << "\t" << temp << endl;
			myfile << fixed << left << setw(15) << tokens[2] << "\t" << temp << endl;

			temp = "";
			state = 4;
			check_state(c, state, temp, keywords, tokens, myfile);
		}
		if (isalpha(c))
		{
			cout << fixed << left << setw(15) << tokens[2] << "\t" << temp << endl;
			myfile << fixed << left << setw(15) << tokens[2] << "\t" << temp << endl;

			temp = "";
			temp.push_back(c);
			state = 2;
			check_state(c, state, temp, keywords, tokens, myfile);
		}
		break;
	case 4:
		temp.push_back(c);
		vector<char> operators = { '+', '-', '*', '/', '<', '>', '=' };
		for (int i = 0; i < operators.size(); i++)
		{
			if (c == operators[i])
			{
				cout << fixed << left << setw(15) << tokens[4] << "\t" << temp << endl;
				myfile << fixed << left << setw(15) << tokens[4] << "\t" << temp << endl;

				temp = "";
				state = 0;
				return;
			}
		}
		cout << fixed << left << setw(15) << tokens[3] << "\t" << temp << endl;
		myfile << fixed << left << setw(15) << tokens[3] << "\t" << temp << endl;

		temp = "";
		state = 0;
		break;
	}
}


void state_change(char c, int &state, string &temp, vector<string> keywords, vector<string> tokens, ofstream& myfile)
{
	int CL = check_letter(c);
	switch (CL)
	{
	case 0:
		if (state != 0) { state_change(c, state, temp, keywords, tokens, myfile); }
		break;
	case 1:
		if (state == 0 || state == 2) { temp.push_back(c); state = 2; }
		check_state(c, state, temp, keywords, tokens, myfile);
		break;
	case 2:
		if (state == 0 || state == 3) { temp.push_back(c); state = 3; }
		check_state(c, state, temp, keywords, tokens, myfile);
		break;
	case 3:
		if (state == 0 || state == 4) { state = 4; }
		check_state(c, state, temp, keywords, tokens, myfile);
		break;
	}
}

int main()
{
	char c;
	int state = 0; // Initial state
	bool change_state = false;
	string temp = "";

	string token_display = "Token";
	string lexeme_display = "Lexeme";

	ofstream myfile("output.txt");

	

	cout << fixed << left << setw(15) << token_display << "\t" << lexeme_display << endl;
	myfile << fixed << left << setw(15) << token_display << "\t" << lexeme_display << endl;
	cout << "============================" << endl;
	myfile << "============================" << endl;


	vector<string> keywords = { "function", "return", "int", "compound", "assign", "if", "print", "scan", "while" };
	vector<string> tokens = { "Keyword", "Identifier", "Integer", "Separator", "Operator" };

	fstream file;
	file.open("C:\\projects\\Lexer\\Lexier\\misc\\test.txt", ios::in);
	if (file.is_open())
	{
		while (file >> c)
		{
			if (c == '!')
			{
				while (file >> c, c != '!') { continue; }
				continue;
			}
			state_change(c, state, temp, keywords, tokens, myfile);
		}
		myfile.close();
	}
	else
	{
		cerr << "Cannot open test.txt" << endl;
	}
	return 0;
}
