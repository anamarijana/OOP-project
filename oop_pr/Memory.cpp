#include "Memory.h"

Memory* Memory::Instance(){
	
	static Memory instance;
	return &instance;
}


