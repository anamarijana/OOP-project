#include "Compiler.h"

Compiler* Compiler::Instance(){
	static Compiler instance;
	return &instance;
}
