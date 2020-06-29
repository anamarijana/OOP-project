#include"ExpressionTree.h"
#include <stack>


ExpressionTree::ExpressionTree(const map<string, string>& var_name_expression) {
	this->final_destitantion_ = final_destination;
	//pravimo jednostavno binarno stablo uz pomoc steka // simple compilation
	stack <Element*> s;
	Element* curr = 0;
	int children_number;
	for (int i = 0; i < postfix.size(); i++) {

		if (isdigit(postfix[i])) {
			curr = new Constant(CONSTANT);
			s.push(curr);
		}
		else if (isalpha(postfix[i])) {
			curr = new Variable(VARIABLE);
			s.push(curr);
		}
		else {
			if (postfix[i] == '+')
				curr = new Addition(ADDITION);
			else if (postfix[i] == '*')
				curr = new Multiplication(MULTIPLICATION);
			else if (postfix[i] == '^')
				curr = new Exponentiation(EXPONENTIATION);
			else
				curr = new Assignment(ASSIGNMENT);
			Element* child = 0;

			if (postfix[i] == '=') children_number = 1;
			else children_number = 2;
			for (int j = 0; j < children_number; j++) {
				if (s.top()->getType() == CONSTANT) {
					child = s.top();
					curr->getIn().push_back(child);
					s.pop();
				}
				else {
					child = s.top();
					curr->getIn().push_back(child);
					s.pop();

				}
			}

		}

	}

	this->root_ = s.top(); //na kraju na steku ostaje samo koreni cvor
	this->root_->setDestination(final_destination);
}
ExpressionTree::~ExpressionTree()
{
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
