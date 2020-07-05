#include <fstream>
#include <iomanip>
#include <iostream>
#include <stack>
#include <cctype>
#include "Program.h"

using namespace std;


void Program::read(const string& filename){
	fstream inputFile(filename, ios::in);
	int row_num = 0;

	string expression;

	while (getline(inputFile, expression)) {
		row_num++;
		var_name_expression.insert({ row_num, expression });
	}

	inputFile.close();

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



