#include"ExpressionTree.h"
#include"Configuration.h"
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
	this->final_destination_ = infix[0]; //za prvi se ne pravi node
	int string_size = (*exp).length();
	for (int i = 1; i < string_size; i++) {
		if (infix[i] == ' ') continue;

		if (isalpha(infix[i])) {
			//ako je operand stavi na stek
			curr = new Variable(VARIABLE);
			postfix.push_back(curr);
			destination = infix[i];
			curr->setDestination(destination);

		}
		if (isdigit(infix[i])) {
			pos_double.clear();
			while ((infix[i] == '.') || isdigit(infix[i]))
				pos_double += infix[i++];
			i--;
			char* cstr = new char[pos_double.length() + 1];
			strcpy(cstr, pos_double.c_str());
			value = atof(cstr);
			curr = new Constant(CONSTANT);
			postfix.push_back(curr);
			constants_.push_back(curr);
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
				while ((s.top() == '^') || (s.top() == '*')) {
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
				while ((s.top() == '^') || (s.top() == '*') || (s.top() == '+')) {
					returnOp( s.top());
					s.pop();
				}
				s.push(infix[i]);
			}

		}
		else if (infix[i] == '-') { 
			if ((infix[i-1] == '=')|| (infix[i-1] == '(') || (infix[i - 2] == '=')) { //ispitujemo da li je minus unaran
				pos_double += infix[i++];

				while ((infix[i] == '.') || isdigit(infix[i]))
					pos_double += infix[i++];
				i--;
				char* cstr = new char[pos_double.length() + 1];
				strcpy(cstr, pos_double.c_str());
				value = atof(cstr);
				curr = new Constant(CONSTANT);
				constants_.push_back(curr);
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
					while ((s.top() == '^') || (s.top() == '*') || (s.top() == '+')) {
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
				while ((s.top() == '^') || (s.top() == '*') || (s.top() == '+')) {
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
	this->postfix.push_back(curr_op);
	




}

void ExpressionTree::build(){
	//pravimo jednostavno binarno stablo od postorder izraza // simple compilation
	stack <Element*> s;
	int children_number;
	string destination;


	for (int i = 0; i < postfix.size(); i++) {

		if (postfix[i]->getType() == CONSTANT) {

			s.push(postfix[i]);
		}
		else if (postfix[i]->getType() == VARIABLE) {

			s.push(postfix[i]);


		}
		else {//CONSTANT, VARIABLE, ADDITION, MULTIPLICATION, EXPONENTIATION, ASSIGNMENT 

			Element* child = 0;

			if (postfix[i]->getType() == ASSIGNMENT) children_number = 1;
			else children_number = 2;
			for (int j = 0; j < children_number; j++) {

				child = s.top();
				postfix[i]->setIn(child);
				s.pop();

			}
			s.push(postfix[i]);

			this->operations_.push_back(postfix[i]);
		}


	}

	this->root_ = s.top(); //na kraju na steku ostaje samo koreni cvor

	this->root_->setDestination(this->final_destination_);

}





ExpressionTree::~ExpressionTree(){
	//postfiks sadrzi sve elemente dovoljno je da njih unistimo

	int elem_size = constants_.size();
	for (int i = 0; i < elem_size; i++) {
		delete constants_[i];
	}
	for (int i = 0; i < elem_size; i++) {
		constants_.pop_back();
	}

	elem_size = postfix.size();
	for (int i = 0; i < elem_size; i++) {
		postfix.pop_back();
	}
	
	elem_size = operations_.size();
	for (int i = 0; i < elem_size; i++) {
		operations_.pop_back();
	}
	root_ = nullptr;


}
//distributivnost
//samo operacije koje imaju asocijativnost +* smemo da grupisemo u narno stablo
//stepenovanje ne smemo da diramo
//distributivnost!! samo ako imamo zagrade??
void ExpressionTree::binaryToNary(){
	
	Element* child = 0;
	
	vector<Element*> grand_children;
	for (int i = 0; i < operations_.size(); i++) {
		// dali smo ga vec izbrisali 
		if (operations_[i]) {
			if ((operations_[i]->getType() != EXPONENTIATION) && (operations_[i]->getType() != ASSIGNMENT)) {
				int children_number = operations_[i]->getIn().size(); //uvek biti 2
				for (int j = 0; j < children_number; j++) {
					child = operations_[i]->getIn()[j];
					int grand_children_number = child->getIn().size();
						if (operations_[i]->getType() == child->getType()) {

							//cuvamo decu te iste operacije // moze da ima vise dece
							grand_children.clear();
							for (int k = 0; k < grand_children_number; k++)
								grand_children.push_back(child->getIn()[k]);
							

							
							operations_[i]->kickTheBaby(j); // ne mora ta operacija da bude na poslednjem mestu
							for (int k = 0; k < grand_children_number; k++)
								operations_[i]->setIn(grand_children[k]);

							removeChild(grand_children);

						}
				}


			}
		}
	}
	// na kraju sve uzemljene obrisemo
	operations_.erase(std::remove(operations_.begin(), operations_.end(), nullptr), operations_.end());
}

//unutar pretvaranja binarnog u narno
void ExpressionTree::removeChild(vector <Element*>& grand_children ){
	bool blagoje = 0;
	for (auto& pointer : operations_){
		
		if (pointer) {

			if (grand_children.size() == pointer->getIn().size()) {
				blagoje = 1;
				for (int m = 0; m < grand_children.size(); m++) {
					if (grand_children[m] != pointer->getIn()[m])
						blagoje = 0;

				}


			}

			if (blagoje){	
				int bound = pointer->getIn().size();
				for(int m =0; m<bound ; m++)
					pointer->popIn();
			
				delete pointer;
				pointer = nullptr;
				return;
			}
		}
	}
	
	

}




vector<Element*> ExpressionTree::getOps(){
	return this->operations_;
}

Element* ExpressionTree::getRoot(){
	return this->root_;
}
