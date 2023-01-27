// COMPILERSEX2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include <string>
using namespace std;
int returning_nonTerminal(string Array1[4], string x);
int returning_Terminal(string Array1[7], string x);

int main()
{


	string inputString;
	cout << "Please Give The Input String\n";
	cin >> inputString;
	cout << "\n";
	list<char> chars;

	list<char> stack;

	for (char c : inputString) {
		chars.push_back(c);
	}
	chars.push_back('$');
	stack.push_front('$');
	stack.push_back('G');

	cout << "\n";
	cout << "\n";
	
	cout << "STACK:";
	for (char y : stack) {
		cout << y;
	}
	cout<<"\n";
	cout << "STRING:";
	for (char y : chars) {
		cout << y;
	}
	cout << "\n\n";
	string Terminals[7] = { "(",")","a","b","*","+","-"};

	string NonTerminals[4] = { "G","M","Y","Z" };

	string LL1_TABLE[4][7] = { {"(M)","","","","","",""},
							   {"YZ","","YZ","YZ","","",""},
		                       {"G","","a","b","","",""},
		                       {"","e","","","*M","+M","-M"}
	};
	string SYNTAX_TREE[100][100];
	for (int i = 0; i <= 99; i++) {
		for (int j = 0; j <= 99; j++) {
			 SYNTAX_TREE[i][j]=" ";
		}
	}
	
	SYNTAX_TREE[0][50] = "G";
	string word, word1;

	word = stack.back();
	int level = 1;	
	int start1 = 25;
	int start2 = 50;
	int start3 = 75;
	string reading_string;
	bool flag = false;
	int backtracking = 0;
	while (word!=""&&!chars.empty()) {
		if (stack.back() == chars.front()) {
			stack.pop_back();
			chars.pop_front();
		}
		else {
			int x = returning_nonTerminal(NonTerminals, word);
			word1= chars.front();

			int y = returning_Terminal(Terminals, word1);
			if (x == -1 || y == -1) {
				break;
			}

			reading_string = stack.back();
			stack.pop_back();
			string newstring = LL1_TABLE[x][y];
			for (int i = 0; i <= 99; i++) {
				if (reading_string == SYNTAX_TREE[level - 1][i] && flag == false) {
					start1 = i - 1;
					start2 = i;
					start3 = i + 1;

				}
				else if (reading_string == SYNTAX_TREE[level - 1][i] && flag == true) {
					for (int j = i + 1; j <= i + 7; j++) {
						SYNTAX_TREE[level - 1][j] = "_";
					}
					start1 = i + 7;
					start2 = i + 8;
					start3 = i + 9;
					flag = false;
				}
			}
			if (newstring != "e")
			{
				for (int j = newstring.length()-1 ; j >= 0; j--)
				{
					stack.push_back(newstring[j]);
				}
				if (newstring.length() == 3 ) {
					SYNTAX_TREE[level][start1] = "/";
					SYNTAX_TREE[level][start2] = "|";
					SYNTAX_TREE[level][start3] = "\\";			
					level += 1;
					start1 -= 1;
					start3 += 1;
					SYNTAX_TREE[level][start1] = newstring[0];
					SYNTAX_TREE[level][start2] = newstring[1];
					SYNTAX_TREE[level][start3] = newstring[2];
					level += 1;
					start1 -= 1;
					start3 += 1;
				}
				else if (newstring.length() == 2  ) {
					SYNTAX_TREE[level][start1] = "/";
					SYNTAX_TREE[level][start3] = "\\";	
					
					level += 1;
					start1 -= 1;
					start3 += 1;
					SYNTAX_TREE[level][start1] = newstring[0];
					SYNTAX_TREE[level][start3] = newstring[1];
					level += 1;
					start1 -= 1;
					start3 += 1;
				}
				else if (newstring.length() == 1 ) {
					
					SYNTAX_TREE[level][start2] = "|";	
					
					level += 1;
					SYNTAX_TREE[level][start2] = newstring[0];
					if (newstring != "a" && newstring != "b") {
						level += 1;
					}
					else {
						level -= 1;
					}
				}
			}
			else{
					SYNTAX_TREE[level][start2] = "|";

					level += 1;
					SYNTAX_TREE[level][start2] = newstring[0];
					level = (backtracking*4)+5;
					flag = true;
					backtracking+=1;
					
			}
		}
		cout << "STACK:";
		for (char x : stack) {
			cout << x ;
		}
		cout<<"\n";
		
		cout << "STRING:";
		for (char y :chars ) {
			cout << y;
		}
		cout << "\n";
		cout << "\n";	
		if (!stack.empty()) {
			word = stack.back();
		}
	}
	if (word == "$" && chars.empty()) {
		cout << "The string has been recognised";
		cout << "\n\nThe syntax tree:\n";
		for (int i = 0; i <= 99; i++) {
			for (int j = 0; j <= 99; j++) {
				cout << SYNTAX_TREE[i][j];
			}
			cout << "\n";
		}
	}
	else {
		cout << "The string has not been recognised";
	}

	return 0;
}
int returning_Terminal(string Array1[7], string x) {
	int flag=-1;
	for (int i = 0; i < 7; i++) {
		if (x == Array1[i]) {
			flag = i;
		}
	}
	return flag;
}
int returning_nonTerminal(string Array1[4], string x) {
	int flag1=-1;
	for (int i = 0; i < 4; i++) {
		if (x == Array1[i]) {
			flag1 = i;
		}
	}
	return flag1;
}




