#include "ExMachina.h"
#include "Compiler.h"
#include"Memory.h"
#include"Program.h"
#include<fstream>
#include<iostream>
#include<string>

//NAPOMENE
//sortirati strignove za vremena
// sortirati kompajler fajl * kojino unapredjenje




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
	Memory::Instance()->deleteForCheck();
	ExMachina::Instance()->deleteFieldsForCheckEM();
	Program::Instance()->deleteForCheck();
	Compiler::Instance()->deleteForCheck();


	return 0;
}