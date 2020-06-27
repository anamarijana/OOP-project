#include"ElemenT.h"


/// proveravam komitovanje
Element::~Element() {

	for (Element* element : in_) {      // U svakoj iteraciji iz vektora 'in_' dohvata se jedan element (Element*) i dodeljuje iteratoru petlje 'element'
		delete element;
	} // vector<bool> in_values ima automatski destruktor
}

vector<Element*> Element::getIn() {
	return this->in_;
}

int Element::getOutValue()
{
	return this->out_value_;
}

Element_Type Element::getType()
{
	return this->type_;
}

vector<bool> Element::getInReady() {
	return this->in_ready_;
}

int Element::getDuration() {
	return this->duration;
}
int Element::getId()
{
	return this->id_;
}
void Element::setReady(bool ready){
	this->ready_ = ready;
}
void Element ::setDestination(char d) {
	this->destination = d;
}

void Operation::in_from_childred_out() {
	for (int i = 0; i < this->in_.size(); i++) {
		in_values_[i] = in_[i]->getOutValue();
	}
}


void Addition::in_to_out() {

	this->out_value_ = this->in_values_[0] + this->in_values_[1]; // kada budemo vrsili operaciju imacemo binarno stablo
}


void Multiplication::in_to_out() {

	this->out_value_ = in_values_[0] + in_values_[1];

}


void Exponentiation::in_to_out() {
	this->out_value_ = in_values_[0] ^ (in_values_[1]); // proveriti koji se stepenuje kojim
}

void Assignment::in_to_out() {
	this->out_value_ = in_values_.front(); // samo ima jedno dete koje prisvaja

}





