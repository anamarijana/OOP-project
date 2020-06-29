#include "Compiler.h"

Compiler* Compiler::Instance(){
	static Compiler instance;
	return &instance;
}

Compiler::Compiler(const string& filepath1, const string filepath2){
	
}

