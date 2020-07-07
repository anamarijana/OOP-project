#include <fstream>
#include <iomanip>
#include <iostream>
#include <stack>
#include <cctype>
#include "Program.h"

using namespace std;


Program::~Program(){
	

}

void Program::read(const string& filename){
	fstream inputFile(filename, ios::in);
	

	string expression;

	while (getline(inputFile, expression)) {
		
		var_name_expression.push_back(expression);
	}

	inputFile.close();

}

void Program::deleteForCheck(){
	if (!var_name_expression.empty())
		var_name_expression.clear();

}

Program* Program::Instance() {
	static Program* instance = new Program();
	return instance;
}



Program::Program() {
}


vector<string> Program::getVarNameExp(){
	return this->var_name_expression;
}



