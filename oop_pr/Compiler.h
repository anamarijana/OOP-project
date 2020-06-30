#ifndef COMPILER_H
#define COMPILER_H
#include<vector>
#include <fstream>
#include <iostream>

#include"ElemenT.h"
#include"Configuration.h"
#include"Program.h"
#include"ExpressionTree.h"
class Compiler {
public:
	static Compiler* Instance(const string& filepath1, const string filepath2);
	~Compiler();
	void catchOperation();
	void compile();
	void setRootsReady();
	const string& giveMachinaFile();
protected:
	Compiler(const string& filepath1,const string filepath2);
private:
	string filename;
	vector <ExpressionTree*> forest_gump_;
	vector<Element*> all_operations;
	bool roots_ready = 0;



};





#endif