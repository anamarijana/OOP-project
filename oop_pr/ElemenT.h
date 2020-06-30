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

	Element(const Element_Type& type, int id) : type_(type), id_(id) {}
	
	~Element();


	virtual void in_to_out() = 0;
	virtual void in_from_childred_out() = 0;
	
	virtual vector<Element*> getIn(); // treba videti da li vracati po referenci ili ne
	int getOutValue();		
	Element_Type getType();
	vector<bool> getInReady();
	int getDuration();
	
	string getDestination();
	bool getReady();
	int getId();
	char getOp();

	void setDestination(string);
	void setReady(bool);
	void setDuration(int);
	void setOutValue(int);// ispraviti sve na double
	void setIn(Element*);
	virtual void notify(ID id) override;


protected:
	Element_Type type_;
	
	int duration = 0;
	bool ready_;
	
	int id_; // stampanje
	char operation;
	string destination_; //token ili varijabla
	int out_value_ = 0;

	
	vector<Element*> in_; // deca 
	vector<bool> in_ready_; // spremnost ulaza 
	vector<int> in_values_;
	
	
};


class Operation : public Element {

public:
	Operation(const Element_Type& type, int id, bool ready_ = 0): Element(type,id) {};
	virtual void in_to_out() override = 0;
	virtual void in_from_childred_out() override;
	
protected:
	
private:
};


class Addition : public Operation {

public:
	Addition(const Element_Type& type, int id = 0,char operation = '+') : Operation(type, id) {} // treba da za podrazumevani broj pinova uzme 2
	~Addition() {}; // destruktor osnovne klase se sam poziva a nemamo nova polja u odnosu a osnovnu klasu
	virtual void in_to_out() override;
protected:
private:

};

class Multiplication : public Operation {

public:

	Multiplication(const Element_Type& type, int id = 0, char operation = '*') : Operation(type, id) {} // treba da za podrazumevani broj pinova uzme 2
	~Multiplication() {};
	virtual void in_to_out() override;
protected:
private:


};

class Exponentiation : public Operation {

public:
	Exponentiation(const Element_Type& type, int id =0, char operation = '^') : Operation(type, id) {} // treba da za podrazumevani broj pinova uzme 2
	~Exponentiation() {};
	virtual void in_to_out() override;
protected:
private:
};

class Assignment : public Operation {

public:
	Assignment(const Element_Type& type, int id = 0, char operation = '=') : Operation(type, id) {} // treba da za podrazumevani broj pinova uzme 2
	~Assignment() {};
	virtual void in_to_out() override;
protected:
private:
};



class Variable : public Element {

public:
	Variable(const Element_Type& type, int id = 0, bool ready_ = 1, char operation = '/0') : Element(type, id) {}
	~Variable() {};
	virtual void in_to_out() override {};
	virtual void in_from_childred_out() override {};

protected:
private:
	
};

class Constant : public Element {

public:
	Constant(const Element_Type& type, int id= 0, bool ready_ = 1, char operation = '/0') : Element(type,id) {}
	~Constant() {};
	virtual void in_to_out() override {};
	virtual void in_from_childred_out() override {};

protected:
private:

};
#endif
//dodatnim poljima izvedenim klasama ne moze dapristupimo preko pokazivaca na element
//elementi koji imaju dodatna polja su sonde i generatore
//treba praviti pokazivace za konkretno te elemente