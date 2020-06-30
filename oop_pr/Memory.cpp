#include "Memory.h"

Memory* Memory::Instance(){
	
	static Memory instance;
	return &instance;
}

void Memory::set(string varName, double val){
	this->final_destination_.insert(varName, val);
}

double Memory::get(string varName)
{
	return this->final_destination_[varName];
}



