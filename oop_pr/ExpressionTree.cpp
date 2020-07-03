#include"ExpressionTree.h"
#include <stack>


//minus moze biti unarni i binarni 
//ako je char pre minusa bila operacija onda unaran

// izraz a^b^c cita se kao a^(b^c)
void ExpressionTree::inToPost(string* exp, int key) { // da bism ose otarasili mogucih zagrada i lakse sastavili sintaksno stablo
	
	string infix = *exp;
	stack <char> s; //na steku ce biti samo operacije i zagrade
	int j = 0;

	Element* curr = 0;
	string destination;
	string pos_double;
	double value;

	int string_size = (*exp).length();
	for (int i = 0; i < string_size; i++) {
		if (infix[i] == ' ') continue;

		if (isalpha(infix[i])) {
			//ako je operand stavi na stek
			curr = new Variable(VARIABLE);
			postfix.push_back(curr);
			destination = infix[i];
			curr->setDestination(destination);

		}
		if (isdigit(infix[i])) {
			while ((infix[i] == '.') || isdigit(infix[i]))
				pos_double += infix[i++];
			char* cstr = new char[pos_double.length() + 1];
			strcpy(cstr, pos_double.c_str());
			value = atof(cstr);
			curr = new Constant(CONSTANT);
			postfix.push_back(curr);
			curr->setOutValue(value);
			destination = pos_double;
			curr->setDestination(destination);
		}


		else if (infix[i] == '(') //oznacava pocetak deo izraza izdvojenog zagradom
			s.push(infix[i]);
		else if (infix[i] == ')') {
			while (s.top() != '(') {
				returnOp(s.top());
				s.pop();
			}
			s.pop(); //(
		}

		else if (infix[i] == '^') //jaca je od svih ostalih operacija, desno asocijativna ako naidje na ^ svakako se gura na stek
			s.push(infix[i]);

		// empty() daje tacno ako je stek prazan

		else if (infix[i] == '*') {
			if (s.empty())
				s.push(infix[i]);
			else if ((s.top() != '^') && (s.top() != '*')) //ako operator ima vecu prednost od onog na vrhu ili je na vrhu otovrena zagrada
				s.push(infix[i]);

			else { //ovde ulece ako je na topu ^ , * levo asocijativna operacija
				while ((s.top() == '^') && (s.top() == '*')) {
					returnOp(s.top());
					s.pop();
				}
				s.push(infix[i]);
			}
		}
		else if (infix[i] == '+') { //on je slabiji od svih
			if (s.empty())
				s.push(infix[i]);
			else if ((s.top() != '^') && (s.top() != '*') && (s.top() != '+'))
				s.push(infix[i]);
			else {
				while ((s.top() == '^') && (s.top() == '*') && (s.top() == '+')) {
					returnOp( s.top());
					s.pop();
				}
				s.push(infix[i]);
			}

		}
		else if (infix[i] == '-') { 
			if ((infix[i-1] == '=')|| (infix[i-1] == '(') ) { //ispitujemo da li je minus unaran
				pos_double += infix[i++];

				while ((infix[i] == '.') || isdigit(infix[i]))
					pos_double += infix[i++];
				char* cstr = new char[pos_double.length() + 1];
				strcpy(cstr, pos_double.c_str());
				value = atof(cstr);
				curr = new Constant(CONSTANT);
				postfix.push_back(curr);
				curr->setOutValue(value);
				destination = pos_double;
				curr->setDestination(destination);

			}

			else {
				if (s.empty())
					s.push(infix[i]);
				else if ((s.top() != '^') && (s.top() != '*') && (s.top() != '+'))
					s.push(infix[i]);
				else {
					while ((s.top() == '^') && (s.top() == '*') && (s.top() == '+')) {
						returnOp(s.top());
						s.pop();
					}
					s.push(infix[i]);
				}
			}
		}

		else if (infix[i] == '=') {
			if (s.empty())
				s.push(infix[i]);
			else if ((s.top() != '^') && (s.top() != '*') && (s.top() != '+'))
				s.push(infix[i]);
			else {
				while ((s.top() == '^') && (s.top() == '*') && (s.top() != '+')) {
					returnOp(s.top());
					s.pop();
				}
				s.push(infix[i]);
			}

		}

	}
	int s_size = s.size();
	for (int i = 0; i < s_size; i++) {
		returnOp(s.top());
		s.pop();
	}

	//trebalo bi da imamo vektor elemenata u postfiksnom zapisu
}
void ExpressionTree:: returnOp(char s_top) {

	Element* curr_op = 0;

	if (s_top == '+') {
		curr_op = new Addition(ADDITION);
		curr_op->setDuration(Configuration::Instance()->getAddTime());
	}
	else if (s_top == '*') {
		curr_op = new  Multiplication(MULTIPLICATION);
		curr_op->setDuration(Configuration::Instance()->getMultiTime());
	}
	else if (s_top == '^') {
		curr_op = new Exponentiation(EXPONENTIATION);
		curr_op->setDuration(Configuration::Instance()->getExpTime());
	}
	else if (s_top == '-') {
		curr_op = new  Subtraction(MULTIPLICATION);
		//curr_op->setDuration(Configuration::Instance()->getMultiTime());
	}

	else {
		curr_op = new Assignment(ASSIGNMENT);
		curr_op->setDuration(Configuration::Instance()->getAssTime());
	}
	postfix.push_back(curr_op);
	




}




ExpressionTree::ExpressionTree(string *expression) {
	//pravimo jednostavno binarno stablo od postorder izraza // simple compilation
	stack <Element*> s;
	Element* curr = 0;
	Operation* curr_op = 0;
	int children_number;
	string exp = *expression;
	
	string final_destination ;
	string destination;
	int constant;

	final_destination += exp[0];//za prvog ne pravimo node
	for (int i = 1; i < exp.size(); i++) {

		if (isdigit(exp[i])) {
			curr = new Constant(CONSTANT);
			s.push(curr);
			constant = exp[i];
			curr->setOutValue(constant);
			destination = exp[i];
			curr->setDestination(destination);
		}
		else if (isalpha(exp[i])) {
			curr = new Variable(VARIABLE);
			s.push(curr);
			destination = exp[i];
			curr->setDestination(destination);

		}
		else {//CONSTANT, VARIABLE, ADDITION, MULTIPLICATION, EXPONENTIATION, ASSIGNMENT 
			if (exp[i] == '+') {
				curr_op = new Addition(ADDITION);
				curr_op->setDuration(Configuration::Instance()->getAddTime());
			}
			else if (exp[i] == '*') {
				curr_op = new  Multiplication(MULTIPLICATION);
				curr_op->setDuration(Configuration::Instance()->getMultiTime());
			}
			else if (exp[i] == '^') {
				curr_op = new Exponentiation(EXPONENTIATION);
				curr_op->setDuration(Configuration::Instance()->getExpTime());
			}
			else {
				curr_op = new Assignment(ASSIGNMENT);
				curr_op->setDuration(Configuration::Instance()->getAssTime());

				
			}
			Element* child = 0;

			if (exp[i] == '=') children_number = 1;
			else children_number = 2;
			for (int j = 0; j < children_number; j++) {
				
				child = s.top();
				curr_op->setIn(child);
				s.pop();
				
			}
			s.push(curr_op);
		
			this->operations_.push_back(curr_op);
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
	
	Element* child = 0;
	Element* grand_child1 = 0;
	Element* grand_child2 = 0;
	for (int i = 0; i<operations_.size();i++){
		if((operations_[i]->getType() != EXPONENTIATION) && (operations_[i]->getType() != ASSIGNMENT)){
			for (int j = 0; j<2;j++){
				child = operations_[i]->getIn()[j];
				if(operations_[i]->getType()== child->getType()){
					
					//cuvamo decu te iste operacije
					grand_child1 = child->getIn()[0];
					grand_child2 = child->getIn()[1];
					
					removeChild(grand_child1, grand_child2);

					operations_[i]->setIn(grand_child1);
					operations_[i]->setIn(grand_child2);

				}
			}
				
		
		}
	}
}

void ExpressionTree::removeChild(Element* GrandChild1, Element* GrandChild2){
	for (auto& pointer : operations_)
	{
		if ((pointer->getIn()[0]==GrandChild1)&& (pointer->getIn()[1] == GrandChild2))
		{
			delete pointer;
			pointer = nullptr;
		}
	}
	operations_.erase(std::remove(operations_.begin(), operations_.end(), nullptr), operations_.end());
	

}


void ExpressionTree::calculate(const string& filepath){
}

vector<Operation*> ExpressionTree::getOps(){
	return this->operations_;
}

Element* ExpressionTree::getRoot(){
	return this->root_;
}
