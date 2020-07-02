#ifndef EXMACHINA_H
#define EXMACHINA_H
#include<vector>
#include "ElemenT.h"
#include"Configuration.h"
class ExMachina {
public:
	
	static ExMachina* Instance();
	
	~ExMachina();

	void exec(string file);
	void readCompilerFile(const string&);
	void waitingtToProcessing();
	void dealWithProcessing();
	void processingToCompleted(int id);
	void writeOutput(int id, int op_duration, int cur_shed_time);
	void eventOccured(int Id,int op_duration, int cur_shed_time);
	

	//void setWayStation(int, int);
protected:
	ExMachina();
private:
	
	string compiler_filename;
	vector <Operation*> waiting_; //ovde su svi na pocetku
	vector <Operation*> processing_; //odavde saljemo masini
	vector <Operation*> completed_;
	
	vector <Element*> everyone_;
	
};





#endif