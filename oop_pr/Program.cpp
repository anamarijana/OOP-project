#include <fstream>
#include <iomanip>
#include <iostream>
#include <stack>
#include <cctype>
#include "Program.h"

using namespace std;
void ExpressionTree::inToPost(string* exp, int key) { // da bism ose otarasili mogucih zagrada i lakse sastavili sintaksno stablo
	string postfix;
	string infix = *exp;
	stack <char> s; //na steku ce biti samo operacije i zagrade
	int j = 0;

	int string_size = (*exp).length();
	for (int i = 0; i < string_size; i++) {
		if (infix[i] == ' ') continue;

		if (isdigit(infix[i]) | isalpha(infix[i])) //ako je operand stavi na stek
			postfix += infix[i];
		else if (infix[i] == '(') //oznacava pocetak deo izraza izdvojenog zagradom
			s.push(infix[i]);
		else if (infix[i] == ')') {
			while (s.top() != '(') {
				postfix[j++] = s.top();
				s.pop();
			}
			s.pop();
		}

		else if (infix[i] == '^') //jaca je od svih ostalih operacija, desno asocijativna ako naidje na ^ svakako se gura na stek
			s.push(infix[i]);

		// empty() daje tacno ako je stek prazan

		else if (infix[i] == '*') {
			if (s.empty())
				s.push(infix[i]);
			else if ((s.top() != '^') && (s.top() != '*')) //ako operator ima vecu prednost od onog na vrhu ili je na vrhu otovrena zagrada
				s.push(infix[i]);

			else { //ovde ulece ako je na topu ^ , * levo asocijativna operacija
				while ((s.top() == '^') && (s.top() == '*')) {
					postfix[j++] = s.top();
					s.pop();
				}
				s.push(infix[i]);
			}
		}
		else if (infix[i] == '+') { //on je slabiji od svih
			if (s.empty())
				s.push(infix[i]);
			else if ((s.top() != '^') && (s.top() != '*') && (s.top() != '+'))
				s.push(infix[i]);
			else {
				while ((s.top() == '^') && (s.top() == '*') && (s.top() == '+')) {
					postfix[j++] = s.top();
					s.pop();
				}
				s.push(infix[i]);
			}

		}
		else if (infix[i] == '=') {
			if (s.empty())
				s.push(infix[i]);
			else if ((s.top() != '^') && (s.top() != '*') && (s.top() != '+'))
				s.push(infix[i]);
			else {
				while ((s.top() == '^') && (s.top() == '*') && (s.top() != '+')) {
					postfix[j++] = s.top();
					s.pop();
				}
				s.push(infix[i]);
			}

		}

	}
	int s_size = s.size();
	for (int i = 0; i < s_size; i++) {
		postfix += s.top();
		s.pop();
	}

	this->var_name_expression[key] = postfix;
}


Program::~Program() {
}
void Program::read(const string& filename){
	fstream inputFile(filename, ios::in);
	int row_num = 0;

	string expression;

	while (getline(inputFile, expression)) {
		row_num++;
		var_name_expression.insert({ row_num, expression });
	}

	inputFile.close();
	//prebacujemo sve izraze y postfiks
	for (auto i = var_name_expression.begin(); i != var_name_expression.end(); i++) {
		string* express;
		express = &(i->second);
		inToPost(express, i->first);
	}

}

Program* Program::Instance() {
	static Program instance;
	return &instance;
}



Program::Program() {
}


map<int, string> Program::getVarNameExp(){
	return this->var_name_expression;
}



