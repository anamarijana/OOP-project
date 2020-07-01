#include "ExMachina.h"
#include "Compiler.h"
#include<fstream>
#include<iostream>
#include<string>

int main(){

	Compiler::Instance("config.txt", "test.txt");
	string ex_m_file = Compiler::Instance("config.txt", "test.txt")->giveMachinaFile();
	fstream inputFile(ex_m_file, ios::in);
	string line;
	while (getline(inputFile, line))
	{
		cout << line << '\n';
	}
	inputFile.close();

	ExMachina::Instance(ex_m_file);


	return 0;
}