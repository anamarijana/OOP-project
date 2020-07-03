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
	static Compiler* Instance();
	void initiate(const string& filepath1, const string& filepath2);
	~Compiler() {};
	void catchOperation();
	void compile();
	void setRootsReady();
	void setElementsReady(vector<Element*>& compiled_elements);
	const string& giveMachinaFile();
	char defineMotherOp(Element*);
	void tieUp();
	Element* returnAss(string destination);
	Element* birth(Element*);
	void compileAdvanced();
	void compileOne(Element*, string&);
protected:
	Compiler() {};
private:
	string filename;
	
	vector <ExpressionTree*> forest_gump_;
	vector<Element*> all_operations;
	bool roots_ready = 0;



};





#endif
