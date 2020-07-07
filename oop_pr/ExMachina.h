#ifndef EXMACHINA_H
#define EXMACHINA_H
#include<vector>
#include "ElemenT.h"



class ExMachina {
public:
	
	

	static ExMachina* Instance();
	
	~ExMachina();
	void deleteFieldsForCheckEM();
	
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
	ExMachina() {};
private:
	vector <int> created_event_id;
	vector<string>	output_string;
	string compiler_filename;
	
	vector <Operation*> waiting_; //ovde se nalaze sve operacije na pocetku
	vector <Operation*> processing_; //odavde saljemo Schedu
	vector <Operation*> completed_;
	
	vector <Element*> everyone_; // ovde se nalaze apsolutno svi elementi
	
};





#endif