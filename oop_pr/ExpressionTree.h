#ifndef CALC_TREE_H
#define CALC_TREE_H
#include "ElemenT.h"
#include <vector>




class ExpressionTree {
public:


	ExpressionTree() {};
	~ExpressionTree();
	ExpressionTree(const ExpressionTree&) = delete;
	ExpressionTree(ExpressionTree&&) = delete;
	void binaryToNary();
	
	vector <Element*> getOps();
	void removeChild(vector <Element*> &);
	
	//treba povezati medjusobno izraze 
	void inToPost(string*, int);
	void returnOp(char);
	void build();
	
	
	Element* getRoot();

protected:

private:
	string final_destination_;
	Element* root_ =0; // uvek bi trebalo da bude operacija dodele
	vector<Element*> operations_; // ovde ce biti oznake za upisivanje i tokeni
	vector<Element*> postfix;
	vector<Element*> constants_;
};

#endif
