#include "ExMachina.h"
#include "Compiler.h"

int main(){

	Compiler::Instance("config.txt", "test.txt");
	string ex_m_file = Compiler::Instance("config.txt", "test.txt")->giveMachinaFile();
	ExMachina::Instance(ex_m_file);


	return 0;
}