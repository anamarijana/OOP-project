#ifndef COMPILER_H
#define COMPILER_H
#include<vector>
#include <fstream>
#include <iostream>
#include<stack>

#include"ElemenT.h"
#include"Configuration.h"
#include"Program.h"
#include"ExpressionTree.h"
class Compiler {
public:
	static Compiler* Instance(const string& filepath1, const string& filepath2);
	~Compiler() {};
	void catchOperation();
	void compile();
	void setRootsReady();
	const string& giveMachinaFile();
	char defineMotherOp(Operation*);
	void tieUp();
	Operation* returnAss(string destination);
	Operation* birth(Operation*);
	void compileAdvanced();
	void compileOne(Operation*, string&);
protected:
	Compiler(const string& filepath1,const string& filepath2);
private:
	string filename;
	
	vector <ExpressionTree*> forest_gump_;
	vector<Operation*> all_operations;
	bool roots_ready = 0;



};





#endif
