#ifndef COMPILER_H
#define COMPILER_H
#include<vector>
#include"ElemenT.h"
#include"Configuration.h"
#include"Program.h"
#include"ExpressionTree.h"
class Compiler {
public:
	static Compiler* Instance(const string& filepath1, const string filepath2);
	~Compiler();

protected:
	Compiler(const string& filepath1,const string filepath2);
private:

	Configuration* Config;
	Program* Prog;
	
	vector <ExpressionTree*> forest_gump_;
	vector <Element*> operations_; 



};





#endif