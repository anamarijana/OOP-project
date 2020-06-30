#ifndef EXMACHINA_H
#define EXMACHINA_H
#include<vector>
#include "ElemenT.h"
#include"Configuration.h"
class ExMachina {
public:
	static ExMachina* Instance(const string&);
	static ExMachina* returnInstance();
	~ExMachina();

	void readCompilerFile(const string&);
	void waitingtToProcessing();
	void dealWithProcessing();
	void processingToCompleted(int id);
	void writeOutput(int id, int op_duration, int cur_shed_time);
	void eventOccured(int Id,int op_duration, int cur_shed_time);
	
	const string& getCompFilename();
	//void setWayStation(int, int);
protected:
	ExMachina(const string&);
private:
	static string compiler_filename;
	vector <Element*> waiting_; //ovde su svi na pocetku
	vector <Element*> processing_; //odavde saljemo masini
	vector <Element*> completed_;
	vector <Element*> everyone_;
	
};





#endif