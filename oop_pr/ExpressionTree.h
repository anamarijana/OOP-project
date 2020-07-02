#ifndef CALC_TREE_H
#define CALC_TREE_H
#include "ElemenT.h"
#include <vector>
#include"Configuration.h"
class ExpressionTree {
public:


	ExpressionTree(string *var_name_expression);
	~ExpressionTree();
	void binaryToNary();
	void calculate(const string& filepath);
	vector <Operation*> getOps();
	void removeChild(Element* , Element*);
	//treba povezati medjusobno izraze 
	
	
	Element* getRoot();

protected:

private:
	Element* root_; // uvek bi trebalo da bude operacija dodele
	vector<Operation*> operations_; // ovde ce biti oznake za upisivanje i tokeni
};

#endif
