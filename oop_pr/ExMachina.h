#ifndef EXMACHINA_H
#define EXMACHINA_H
#include<vector>
#include<map>
#include "ElemenT.h"
class ExMachina {
public:
	static ExMachina* Instance();

	~ExMachina();

	void readCompilerFile(string);
	void waitingtToProcessing();
	void dealWithProcessing();
	void processingToCompleted(int id);
	void writeOutput(int cur_shed_time);
	void eventOccured(int Id, int cur_shed_time);
	void saveTokens(int, int);
	//void setWayStation(int, int);
protected:
	ExMachina() {};
private:
	vector <Element*> waiting_; //ovde su svi na pocetku
	vector <Element*> processing_; //odavde saljemo masini
	vector <Element*> completed_;
	vector <Element*> everyone_;
	map <int, int> way_station_; //pamti tokene
};





#endif