#include "ExMachina.h"
#include "Compiler.h"
#include<fstream>
#include<iostream>
#include<string>

int main(){

	Compiler::Instance()->initiate("config.txt", "test.txt");
	string ex_m_file = Compiler::Instance()->giveMachinaFile();
	/*
	fstream inputFile(ex_m_file, ios::in);
	string line;
	while (getline(inputFile, line))
	{
		cout << line << '\n';
	}
	inputFile.close();
	*/
	ExMachina::Instance()-> exec(ex_m_file) ;


	return 0;
}