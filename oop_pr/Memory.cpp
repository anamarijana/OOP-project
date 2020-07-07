#include "Memory.h"
#include"Exception.h"
#include<fstream>


using namespace std;
void Memory::deleteForCheck(){
	if (!final_destination_.empty())
		final_destination_.clear();

}
Memory::~Memory(){
	
	if(!final_destination_.empty())
	final_destination_.clear();

}


void setM(string varName, double val, Memory* mem){

	mem->set(varName, val);
}

void Memory::set(string varName, double val){
	this->final_destination_.insert({ varName, val });
}

double Memory::get(string varName){
	if (final_destination_.count(varName) > 0) //vraca koliko puta se nalazi key u mapi
		return this->final_destination_[varName];
	throw VarNotAvailableException("Nema trazene promenljive u memoriji!");
}

void Memory::write(string file){
	string new_file_name = file;
	unsigned int len_without_txt = new_file_name.length() - 4;
	new_file_name.resize(len_without_txt);
	new_file_name.insert(len_without_txt, ".mem");

	fstream outputFile(new_file_name, ios::out);
	map<string, double>::iterator mile;
	for (mile = final_destination_.begin(); mile != final_destination_.end(); ++mile) {
		outputFile << '\t' << mile->first
			<< '=' << mile ->second << endl;
	}


	outputFile.close();




}

/*Memory* Memory::Instance(){
	
	static Memory* instance = new Memory();
	return instance;
}*/



