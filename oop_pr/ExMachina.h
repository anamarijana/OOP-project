#ifndef EXMACHINA_H
#define EXMACHINA_H
#include<vector>
#include "ElemenT.h"
class ExMachina {
public:
	static ExMachina* Instance();

	~ExMachina();
	void setWaiting(const vector<Element*>& operations_); //When a vector is passed to a function, a copy of the vector is created.
	void waitingtToProcessing();
	void processingToCompleted(int id);
	void dealWithProcessing();
	void writeOutput(int cur_shed_time);
	void availableElement(int Id);
	void eventOccured(int Id, int cur_shed_time);
	void readCompilerFile(string);
protected:
	ExMachina();
private:
	vector <Element*> waiting_; //ovde su svi na pocetku
	vector <Element*> processing_; //odavde saljemo masini
	vector <Element*> completed_;
	vector<Element*> everyone_;

};





#endif