#ifndef ELEMENT_H
#define ELEMENT_H
#include <vector>
#include<string>
#include<Interfaces.h>
#include <math.h>
//	AKO U SKEDZULERU POSTOJI VESI IVENTOVA I NEKI DUZE TRAJE OD OSTALIH OSTACE U SKEDZULERU NAKON PROCESS NOW


using namespace std;
enum Element_Type { CONSTANT, VARIABLE, ADDITION, MULTIPLICATION, EXPONENTIATION, ASSIGNMENT,SUBTRACTION }; //znaci ce kod treanformacije binarnog u n-arno stablo

//KLASA ELEMENT
//sadrzi variablu u koju upisuje
//vrednost varijable
//operaciju koju izvrsava +*^ = 
// ulazne portove portove

class Element : public ITimedElement {

public:

	Element(const Element_Type& type, int id = 0, double duration = 0, bool ready = 0) : type_(type),
		duration_(duration), id_(id),ready_(ready){}
	
	~Element();


	virtual void in_to_out() = 0;
	virtual void in_from_childred_out() = 0;
	
	virtual vector<Element*> getIn(); // treba videti da li vracati po referenci ili ne
	double getOutValue();		
	Element_Type getType();
	vector<bool> getInReady();
	
	
	string getDestination();
	bool getReady();
	
	void setDestination(string);

	void setReady(bool);
	
	void setOutValue(double);// ispraviti sve na double
	void setIn(Element*);
	void setInByIndex(int index, Element* insert_el);

	void popIn();
	void kickTheBaby(int); // izbacuje odredjeno dete (ulaz)
	
	double getDuration();
	int getId();
	void setDuration(double);
	virtual void notify(ID id) override;


	

protected:
	Element_Type type_;
	bool ready_;//da li je cvor smpreman za obradu
	
	
	string destination_; //token ili varijabla
	double out_value_ = 0; //vrednost tog cvora

	
	vector<Element*> in_; // deca 
	vector<bool> in_ready_; // spremnost ulaza 
	vector<double> in_values_;
	double duration_ = 0; //postavlja konfiguracija ///polje koje koristi samo operacija//exMachina
	int id_; // stampanje // potrebno samo operacijama /exMachina
	
};

//the value of a variable can only be set in an initialization list of a constructor belonging to the same class as the variable.

class Operation : public Element {

public:
	Operation(const Element_Type& type, int id = 0, int duration = 0, bool ready = 0): Element(type,id,duration,ready) 
		{};
	virtual void in_to_out() override = 0;
	virtual void in_from_childred_out() override;

	

protected:
	
private:
};


class Addition : public Operation {

public:
	Addition(const Element_Type& type, int id = 0, int duration = 0, bool ready = 0) : Operation(type,id,duration,ready) {} // treba da za podrazumevani broj pinova uzme 2
	~Addition() {}; // destruktor osnovne klase se sam poziva a nemamo nova polja u odnosu a osnovnu klasu
	virtual void in_to_out() override;
protected:
private:

};

class Subtraction : public Operation {

public:
	Subtraction(const Element_Type& type, int id = 0, int duration = 0, bool ready = 0) : Operation(type, id, duration, ready) {} // treba da za podrazumevani broj pinova uzme 2
	~Subtraction() {}; // destruktor osnovne klase se sam poziva a nemamo nova polja u odnosu a osnovnu klasu
	virtual void in_to_out() override;
protected:
private:

};

class Multiplication : public Operation {

public:

	Multiplication(const Element_Type& type, int id = 0, int duration = 0, bool ready = 0) : Operation(type, id, duration, ready) {} // treba da za podrazumevani broj pinova uzme 2
	~Multiplication() {};
	virtual void in_to_out() override;
protected:
private:


};

class Exponentiation : public Operation {

public:
	Exponentiation(const Element_Type& type, int id = 0, int duration = 0, bool ready = 0) : Operation(type, id, duration, ready) {} // treba da za podrazumevani broj pinova uzme 2
	~Exponentiation() {};
	virtual void in_to_out() override;
protected:
private:
};

class Assignment : public Operation {

public:
	Assignment(const Element_Type& type, int id = 0, int duration = 0, bool ready = 0) : Operation(type, id, duration, ready) {} // treba da za podrazumevani broj pinova uzme 2
	~Assignment() {};
	virtual void in_to_out() override;
protected:
private:
};



class Variable : public Element {

public:
	Variable(const Element_Type& type, int id = 0, int duration = 0, bool ready = 1) : Element(type, id, duration, ready) {}
	~Variable() {};
	virtual void in_to_out() override {};
	virtual void in_from_childred_out() override {};
	//virtual void notify(ID id) override {};
protected:
private:
	
};

class Constant : public Element {

public:
	Constant(const Element_Type& type, int id = 0, int duration = 0, bool ready = 1) : Element(type, id, duration, ready) {}
	~Constant() {};
	virtual void in_to_out() override {};
	virtual void in_from_childred_out() override {};
	//virtual void notify(ID id) override {};
protected:
private:

};
#endif
//dodatnim poljima izvedenim klasama ne moze dapristupimo preko pokazivaca na element
//elementi koji imaju dodatna polja su sonde i generatore
//treba praviti pokazivace za konkretno te elemente