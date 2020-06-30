#include"ExpressionTree.h"
#include <stack>


ExpressionTree::ExpressionTree(string *expression) {
	//pravimo jednostavno binarno stablo od postorder izraza // simple compilation
	stack <Element*> s;
	Element* curr = 0;
	int children_number;
	string exp = *expression;
	
	string final_destination;
	string destination;
	int constant;

	for (int i = 0; i < exp.size(); i++) {

		if (isdigit(exp[i])) {
			curr = new Constant(CONSTANT);
			s.push(curr);
			constant = exp[i];
			curr->setOutValue(constant);
		}
		else if (isalpha(exp[i])) {
			curr = new Variable(VARIABLE);
			s.push(curr);
			destination = exp[i];
			curr->setDestination(destination);

		}
		else {
			if (exp[i] == '+') {
				curr = new Addition(ADDITION);
				curr->setDuration(Configuration::returnInstance()->getAddTime());
			}
			else if (exp[i] == '*') {
				curr = new Multiplication(MULTIPLICATION);
				curr->setDuration(Configuration::returnInstance()->getMultiTime());
			}
			else if (exp[i] == '^') {
				curr = new Exponentiation(EXPONENTIATION);
				curr->setDuration(Configuration::returnInstance()->getExpTime());
			}
			else {
				curr = new Assignment(ASSIGNMENT);
				curr->setDuration(Configuration::returnInstance()->getAssTime());
				final_destination = exp[++i];//posle jednako ide var za nju ne pravimo node
				
			}
			Element* child = 0;

			if (exp[i] == '=') children_number = 1;
			else children_number = 2;
			for (int j = 0; j < children_number; j++) {
				
				child = s.top();
				curr->getIn().push_back(child);
				s.pop();
				
			}
			s.push(curr);
		
			this->operations_.push_back(curr);
		}

	}

	this->root_ = s.top(); //na kraju na steku ostaje samo koreni cvor
	this->root_->setDestination(final_destination);
}
ExpressionTree::~ExpressionTree(){
}
//distributivnost
//samo operacije koje imaju asocijativnost +* smemo da grupisemo u narno stablo
//stepenovanje ne smemo da diramo
//distributivnost!! samo ako imamo zagrade??
void ExpressionTree::binaryToNary(){
	
}

void ExpressionTree::birth(Element*){
}


void ExpressionTree::calculate(const string& filepath){
}

vector<Element*> ExpressionTree::getOp(){
	return this->operations_;
}

Element* ExpressionTree::getRoot(){
	return this->root_;
}
