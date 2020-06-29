#ifndef ELEMENT_H
#define ELEMENT_H
#include <vector>
#include<string>
#include<Interfaces.h>
//	AKO U SKEDZULERU POSTOJI VESI IVENTOVA I NEKI DUZE TRAJE OD OSTALIH OSTACE U SKEDZULERU NAKON PROCESS NOW


using namespace std;
enum Element_Type { CONSTANT, VARIABLE, ADDITION, MULTIPLICATION, EXPONENTIATION, ASSIGNMENT }; //znaci ce kod treanformacije binarnog u n-arno stablo

//KLASA ELEMENT
//sadrzi variablu u koju upisuje
//vrednost varijable
//operaciju koju izvrsava +*^ = 
// ulazne portove portove

class Element : public ITimedElement {

public:

	Element(const Element_Type& type, int number_inputs) : type_(type),number_inputs_(number_inputs){}
	Element(int id, const Element_Type& type) : type_(type) , id_(id) {};
	~Element();


	virtual void in_to_out() = 0;
	virtual void in_from_childred_out() = 0;
	
	virtual vector<Element*> getIn(); // treba videti da li vracati po referenci ili ne
	int getOutValue();
	Element_Type getType();
	vector<bool> getInReady();
	int getDuration();
	int getId();
	string getDestination();

	void setDestination(string);
	void setReady(bool);
	
	virtual void notify(ID id) override;


protected:
	Element_Type type_;
	int id_; // stampanje
	int duration = 0;
	bool ready_;
	
	string destination_; //token ili varijabla
	int out_value_ = 0;

	int number_inputs_;
	vector<Element*> in_; // deca 
	vector<bool> in_ready_; // spremnost ulaza 
	vector<int> in_values_;
	
};


class Operation : public Element {

public:
	Operation(const Element_Type& type, int number_inputs) :Element(type, number_inputs) {};
	virtual void in_to_out() override = 0;
	virtual void in_from_childred_out() override;

protected:
	bool ready_ = 0;
	int id = 0;

};


class Addition : public Operation {

public:
	Addition(const Element_Type& type, int number_inputs = 2) : Operation(type, number_inputs) {} // treba da za podrazumevani broj pinova uzme 2
	~Addition() {}; // destruktor osnovne klase se sam poziva a nemamo nova polja u odnosu a osnovnu klasu
	virtual void in_to_out() override;
protected:
private:

};

class Multiplication : public Operation {

public:

	Multiplication(const Element_Type& type, int number_inputs = 2) : Operation(type, number_inputs) {} // treba da za podrazumevani broj pinova uzme 2
	~Multiplication() {};
	virtual void in_to_out() override;
protected:
private:


};

class Exponentiation : public Operation {

public:
	Exponentiation(const Element_Type& type, int number_inputs = 2) : Operation(type, number_inputs) {} // treba da za podrazumevani broj pinova uzme 2
	~Exponentiation() {};
	virtual void in_to_out() override;
protected:
private:
};

class Assignment : public Operation {

public:
	Assignment(const Element_Type& type, int number_inputs = 1) : Operation(type, number_inputs) {} // treba da za podrazumevani broj pinova uzme 2
	~Assignment() {};
	virtual void in_to_out() override;
protected:
private:
};



class Variable : public Element {

public:
	Variable(const Element_Type& type, int number_inputs = 0) : Element(type, number_inputs) {}int out_value_ = 0;
	~Variable() {};
	virtual void in_to_out() override {};
	virtual void in_from_childred_out() override {};

protected:
private:
	bool ready_ = 1; //spreman da se da operaciji
};

class Constant : public Element {

public:
	Constant(const Element_Type& type, int number_inputs = 0) : Element(type, number_inputs) {}
	~Constant() {};
	virtual void in_to_out() override {};
	virtual void in_from_childred_out() override {};

protected:
private:
	bool ready_ = 1; // signalizira da je spreman da se da operaciji

};
#endif
//dodatnim poljima izvedenim klasama ne moze dapristupimo preko pokazivaca na element
//elementi koji imaju dodatna polja su sonde i generatore
//treba praviti pokazivace za konkretno te elemente