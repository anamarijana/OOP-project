#include <fstream>
#include <iomanip>
#include <iostream>
#include <stack>
#include"Configuration.h"
using namespace std;

/// provera
Konfiguracija::Konfiguracija(string filename) {
	// Otvaramo fajl u 'in' rezimu rada (samo citanje)
	fstream inputFile(filename, ios::in);


	// Metoda 'peek()' dohvata sledeci karakter koji bi se procitao ali ga ne cita

	while (inputFile.peek() != EOF) {
		int var_value = 0;
		char buffer;
		// Fajl tokove koristimo isto kao i ulaz/izlaz tokove
		int i = 0;
		string var_name = " ";
		while (inputFile.peek() != '=') {
			inputFile >> var_name[i++];
		}
		inputFile >> buffer;
		inputFile >> var_value;
		if (!var_name.compare(Ta))
			this->Ta = var_value;
		else if (!var_name.compare(Tm))
			this->Tm = var_value;
		else if (!var_name.compare(Te))
			this->Te = var_value;
		else if (!var_name.compare(Tw))
			this->Tw = var_value;
		else if (!var_name.compare(Nw))
			this->Nw = var_value;
		else if (!var_name.compare(compilation))
			this->compilation = var_value;

		inputFile >> buffer; //da bi presao u novi red


	}
	// Na kraju je bitno da zatvorimo fajl kako bismo izbrisali sve res
	inputFile.close();
}
