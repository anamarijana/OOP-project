#ifndef CALC_TREE_H
#define CALC_TREE_H
#include "ElemenT.h"
#include <vector>
#include"Configuration.h"
class ExpressionTree {
public:


	ExpressionTree() {};
	~ExpressionTree();
	void binaryToNary();
	void calculate(const string& filepath);
	vector <Element*> getOps();
	void removeChild(Element* , Element*);
	//treba povezati medjusobno izraze 
	void inToPost(string*, int);
	void returnOp(char);
	void build();
	
	
	Element* getRoot();

protected:

private:
	string final_destination_;
	Element* root_; // uvek bi trebalo da bude operacija dodele
	vector<Element*> operations_; // ovde ce biti oznake za upisivanje i tokeni
	vector<Element*> postfix;
};

#endif
