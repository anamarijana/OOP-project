#include <fstream>
#include <iomanip>
#include <iostream>
#include <stack>
#include <cctype>
#include "Program.h"

using namespace std;


Program::~Program() {
}

Program* Program::Instance(const string& filename) {
	static Program instance(filename);
	filename_ = filename;
	return &instance;
}

Program* Program::returnInstance() {
	return Instance(filename_);
}

Program::Program(const string &filename) {
	// Otvaramo fajl u 'in' rezimu rada (samo citanje)
	fstream inputFile(filename, ios::in);


	// Metoda 'peek()' dohvata sledeci karakter koji bi se procitao ali ga ne cita

	while (inputFile.peek() != EOF) {
		
		char buffer;
		int j = 0;
		string expression;
		while (inputFile.peek() != '\n') {
			char c;
			inputFile>>c;
			expression += c;

		}

		*var_name_expression[j++] = expression ;
		inputFile>>buffer; // da bi pokupio znak za novi red


	}
	inputFile.close();
	//prebacujemo sve izraze y postfiks
	int count = 0;
	string* curr = var_name_expression[0];
	while ( curr!=nullptr) {
			inToPost(curr);
			curr++;
			count++;

	}
	this->expression_num = count + 1;
}

// izraz a^b^c cita se kao a^(b^c)
const string& Program::inToPost(string *exp) { // da bism ose otarasili mogucih zagrada i lakse sastavili sintaksno stablo
	string postfix;
	string infix = *exp;
	stack <char> s; //na steku ce biti samo operacije i zagrade
	int j = 0;
	for (int i = 0; i < sizeof(exp); i++) {

		if (isdigit(infix[i]) | isalpha(infix[i])) //ako je operand stavi na stek
			s.push(infix[i]);
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
			if ((s.top() != '^')&&(s.top() != '*')) //ako operator ima vecu prednost od onog na vrhu ili je na vrhu otovrena zagrada
				s.push(infix[i]);

			else { //ovde ulece ako je na topu ^ , * levo asocijativna operacija
				while ((s.top() == '^') && (s.top() == '*'))  {
					postfix[j++] = s.top();
					s.pop();
				}
				s.push(infix[i]);
			}
		}
		else if (infix[i] == '+') { //on je slabiji od svih
			if ((s.top() != '^') && (s.top() != '*') && (s.top() != '+'))
				s.push(infix[i]);
			else {
				while ((s.top() == '^') && (s.top() == '*') && (s.top() == '+')){
					postfix[j++] = s.top();
					s.pop();
				}
				s.push(infix[i]);
			}

		}
		else if (infix[i] == '=') {
			if ((s.top() != '^') && (s.top() != '*') && (s.top() != '+'))
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

}

int Program::getExpNum(){
	return this->expression_num;
}

string** Program::getVarNameExp(){
	return this->var_name_expression;
}

