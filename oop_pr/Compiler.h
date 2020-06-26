#ifndef COMPILER_H
#define COMPILER_H
#include<vector>
#include"ElemenT.h"
class Compiler {
public:
	Compiler();
	~Compiler();

protected:
private:
	vector <Element*> roots_;
	vector <Element*> operations_; //odavde saljemo masini



};





#endif