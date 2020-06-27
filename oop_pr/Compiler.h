#ifndef COMPILER_H
#define COMPILER_H
#include<vector>
#include"ElemenT.h"
class Compiler {
public:
	static Compiler* Instance();
	~Compiler();

protected:
	Compiler();
private:



	vector <Element*> roots_;
	vector <Element*> operations_; //odavde saljemo masini



};





#endif