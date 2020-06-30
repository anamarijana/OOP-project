#include "Compiler.h"

Compiler* Compiler::Instance(const string& filepath1, const string filepath2){
	static Compiler *instance = new Compiler(filepath1,filepath2);
	return instance;
}

Compiler::Compiler(const string& filepath1, const string filepath2){
	this->Config = new Configuration(filepath1);
	this->Prog = new Program(filepath2);
	for (int i = 0; i < this->Prog->getExpNum(); i++) {
		this->forest_gump_[i] = new ExpressionTree(this->Prog->getVarNameExp()[i],*(this->Config));
	}
}

