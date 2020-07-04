#ifndef EXMACHINA_H
#define EXMACHINA_H
#include<vector>
#include "ElemenT.h"



class ExMachina {
public:
	
	static ExMachina* Instance();
	
	~ExMachina();

	void exec(string file);
	void readCompilerFile(const string&);
	void waitingtToProcessing();
	void dealWithProcessing();
	void processingToCompleted(int id);
	void eventOccured(int Id, int op_duration, int cur_shed_time);
	void writeOutputString(int id, int op_duration, int cur_shed_time);
	void writeOutput();
	

	//void setWayStation(int, int);
protected:
	ExMachina();
private:
	vector <int> created_event_id;
	vector<string> output_string;
	string compiler_filename;
	vector <Operation*> waiting_; //ovde su svi na pocetku
	vector <Operation*> processing_; //odavde saljemo masini
	vector <Operation*> completed_;
	
	vector <Element*> everyone_;
	
};





#endif