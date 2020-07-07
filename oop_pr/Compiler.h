#ifndef COMPILER_H
#define COMPILER_H
#include<vector>
#include <fstream>
#include <iostream>
#include<stack>

#include"ElemenT.h"
#include"ExpressionTree.h"

class Compiler {
public:
	void deleteForCheck();
	static Compiler* Instance();
	void initiate(const string& filepath1, const string& filepath2);
	~Compiler();
	Compiler(const Compiler&) = delete;
	Compiler(Compiler&&) = delete;
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
	void kickTheOp(Element*, vector<Element*>&); 
protected:
	Compiler() {};
private:
	string filename;
	
	vector <ExpressionTree*> forest_gump_; // nije dobro brisati odavde jer su operacije medjusobno ispovezane
	vector<Element*> all_operations;
	bool roots_ready = 0;


	//destruktor 
	// da se ne bi operacije brisale dva puta teba obrisati vektor svih operacija
	//onda uci u stabla i obrisati samo konstante  jer su varijable vec obrisane 


};





#endif
