#ifndef COMPILER_H
#define COMPILER_H
#include<vector>
#include"ElemenT.h"
#include"Configuration.h"
class Compiler {
public:
	static Compiler* Instance();
	~Compiler();

protected:
	Compiler(const string& filepath1,const string filepath2);
private:


	Configuration* Spec;
	vector <Element*> roots_;
	vector <Element*> operations_; //odavde saljemo masini



};





#endif