#ifndef EXMACHINA_H
#define EXMACHINA_H
#include<vector>
#include "ElemenT.h"
class ExMachina {
public:
	ExMachina();
	~ExMachina();
	void setWaiting(const vector<Element*>& operations_); //When a vector is passed to a function, a copy of the vector is created.
	void waitingtToProcessing();
	void dealWithProcessing();
protected:
private:
	vector <Element*> waiting_; //ovde su svi na pocetku
	vector <Element*> processing_; //odavde saljemo masini
	vector <Element*> complited_;


};





#endif