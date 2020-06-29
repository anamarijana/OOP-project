#include "Memory.h"

Memory* Memory::Instance(){
	
	static Memory instance;
	return &instance;
}

void Memory::enterFinalDestination(char var_name, int var_value ){
	this->final_destination_.insert(var_name, var_value);

}


