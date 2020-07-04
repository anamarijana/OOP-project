#include "Memory.h"
#include<fstream>


using namespace std;
Memory* Memory::Instance(){
	
	static Memory instance;
	return &instance;
}

void Memory::set(string varName, double val){
	this->final_destination_.insert({ varName, val });
}

double Memory::get(string varName)
{
	return this->final_destination_[varName];
}

void Memory::write(string file){
	//string ex_m_filename = file;
	string ex_m_filename = "pera_memorise.txt";
	fstream outputFile(ex_m_filename, ios::out);
	map<string, double>::iterator mile;
	for (mile = final_destination_.begin(); mile != final_destination_.end(); ++mile) {
		outputFile << '\t' << mile->first
			<< '=' << mile ->second << endl;
	}


	outputFile.close();




}



