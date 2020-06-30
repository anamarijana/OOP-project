#include"ExpressionTree.h"
#include <stack>


ExpressionTree::ExpressionTree(string *expression,const Configuration& Conf) {
	//pravimo jednostavno binarno stablo od postorder izraza // simple compilation
	stack <Element*> s;
	Element* curr = 0;
	int children_number;
	string exp = *expression;
	Configuration* pConf;
	*pConf = Conf;
	for (int i = 0; i < exp.size(); i++) {

		if (isdigit(exp[i])) {
			curr = new Constant(CONSTANT);
			s.push(curr);
		}
		else if (isalpha(exp[i])) {
			curr = new Variable(VARIABLE);
			s.push(curr);
		}
		else {
			if (exp[i] == '+') {
				curr = new Addition(ADDITION);
				curr->setDuration(pConf->getAddTime());
			}
			else if (exp[i] == '*') {
				curr = new Multiplication(MULTIPLICATION);
				curr->setDuration(pConf->getMultiTime());
			}
			else if (exp[i] == '^') {
				curr = new Exponentiation(EXPONENTIATION);
				curr->setDuration(pConf->getExpTime());
			}
			else {
				curr = new Assignment(ASSIGNMENT);
				curr->setDuration(pConf->getAssTime());
			}
			Element* child = 0;

			if (exp[i] == '=') children_number = 1;
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

Element* ExpressionTree::getRoot(){
	return this->root_;
}
