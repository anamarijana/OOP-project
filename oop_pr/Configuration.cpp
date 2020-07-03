#include <fstream>
#include <iomanip>
#include <iostream>
#include <stack>
#include"Configuration.h"
using namespace std;


string Configuration::config_file_name;//deklarisemo staticku varijablu
Configuration* Configuration::Instance(){
	static Configuration instance;
	return &instance;
	
}

void Configuration::read(const string& filepath){
	fstream inputFile(filepath, ios::in);

	while (inputFile.peek() != EOF) {
		int var_value = 0;
		char buffer;
		int i = 0;
		string var_name;
		char help;
		string comp_value;
		while (1) {
			inputFile >> help;
			if (help == '=') break;
			var_name += help;
		}



		if (!(var_name.compare("Ta"))) {
			inputFile >> var_value;
			this->Ta = var_value;
		}
		else if (!var_name.compare("Tm")) {
			inputFile >> var_value;
			this->Tm = var_value;
		}
		else if (!var_name.compare("Te")) {
			inputFile >> var_value;
			this->Te = var_value;
		}
		else if (!var_name.compare("Tw")) {
			inputFile >> var_value;
			this->Tw = var_value;
		}
		else if (!var_name.compare("Nw")) {
			inputFile >> var_value;
			this->Nw = var_value;
		}
		else if (!var_name.compare("compilation")) {
			while (inputFile.peek() != EOF) {
				inputFile >> help;
				comp_value += help;
			}

			if (!comp_value.compare("simple")) {
				this->compilation = 0;
			}
			else
				this->compilation = 1;


		}




	}
	// Na kraju je bitno da zatvorimo fajl kako bismo izbrisali sve res
	inputFile.close();
}


int Configuration::getMultiTime(){
	return this->Tm;
}
int Configuration::getAddTime() {
	return this->Ta;
}
int Configuration::getExpTime() {
	return this->Te;
}
int Configuration::getAssTime() {
	return this->Tw;
}
int Configuration::getMemoTime() {
	return this->Nw;
}
bool Configuration::getComp() {
	return this->compilation;
}


Configuration::Configuration() {}
	
