#include <fstream>
#include<iostream>

#include "Event.h"
#include "Sched.h"

#include "ExMachina.h"
#include"Configuration.h"
#include"Memory.h"




void ExMachina::eventOccured(int Id,int op_duration, int cur_shed_time){ //slusa vesti od notify
	writeOutputString(Id, op_duration, cur_shed_time); 
	processingToCompleted(Id);
	waitingtToProcessing();
	
}


void ExMachina::readCompilerFile(const string& filename){
	/*
	fstream inputFile(filename, ios::in);
	string line;
	while (inputFile.eof())
	{
		inputFile >> line;
		cout << line << '\n';
	}
	inputFile.close();*/
	
	
	
	fstream inputFile(filename, ios::in);
	string operand1;
	string operand2;
	string destination;
	string id;

	char buffer = '\0';
	char operation = '\0';
	char c = '\0';
	
	//[2] = a t1
	//[3] ^ t1 x 3

	while (inputFile >> buffer) {
		
		operand1.clear();
		operand2.clear();
		destination.clear();
		id.clear();
		
		Element* curr = 0;
		Operation* curr_op = 0;
		
		while (1) {
			inputFile >> c;
			if (c == ']') break;
			id += c;
		}
	
		
		inputFile >> operation; 
		inputFile >> destination; 
		inputFile >> operand1;
	
		if (inputFile.peek() != '\n') inputFile >> operand2;
	
		if (operation == '+') {
			curr_op = new Addition(ADDITION,stoi(id), Configuration::Instance()->getAddTime());
			
		}
		else if (operation == '*') {
			curr_op = new Multiplication(MULTIPLICATION, stoi(id), Configuration::Instance()->getMultiTime());

		}
		else if (operation == '^') {
			curr_op = new Exponentiation(EXPONENTIATION,stoi(id), Configuration::Instance()->getExpTime());

		}
		else if (operation == '=') {
			curr_op = new Assignment(ASSIGNMENT, stoi(id), Configuration::Instance()->getAssTime());

		}
		if (curr_op) curr_op->setDestination(destination);
		
		this->everyone_.push_back(curr_op);
		this->waiting_.push_back(curr_op);
		bool has_operand1 = 0;
		bool has_operand2 = 0;
		
		if (isdigit(operand1[0]) || (operand1[0] == '-')) {
			for (int i = 0; i < everyone_.size(); i++) {
				char* cstr1 = new char[operand1.length() + 1];
				strcpy(cstr1, operand1.c_str());
				if (everyone_[i]->getOutValue() == atof(cstr1)) {
					curr_op->setIn(everyone_[i]);
					has_operand1 = 1;
				}
				delete[] cstr1;
				cstr1 = nullptr;
			}
		}
		else if (isalpha(operand1[0])) {
			for (int i = 0; i < everyone_.size(); i++) {
				if (everyone_[i]->getDestination() == operand1) {
					curr_op->setIn(everyone_[i]);
					has_operand1 = 1;

				}
			}
		}
		if (isdigit(operand2[0]) || (operand2[0] == '-')) {
			char* cstr2 = new char[operand2.length() + 1];
			strcpy(cstr2, operand2.c_str());
			for (int i = 0; i < everyone_.size(); i++) {
				if (everyone_[i]->getOutValue() == atof(cstr2)) {
					curr_op->setIn(everyone_[i]);
					has_operand2 = 1;
				}
			}
			delete[] cstr2;
			cstr2 = nullptr;
		}
		else if (isalpha(operand2[0])) {
			for (int i = 0; i < everyone_.size(); i++) {
				if (everyone_[i]->getDestination() == operand2) {
					curr_op->setIn(everyone_[i]);
					has_operand2 = 1;
				}
			}
		}
		
			
		

	
		if (has_operand1 == 0) {
			if (isdigit(operand1[0]) || (operand1[0] == '-')) {
				curr = new Constant(CONSTANT);
				char* cstr4 = new char[operand1.length() + 1];
				strcpy(cstr4, operand1.c_str());

				curr->setOutValue(atof(cstr4));
				curr->setDestination(operand1);
				delete[] cstr4;
				cstr4 = nullptr;
			}
			else { //Takodje
				curr = new Variable(VARIABLE);
				curr->setDestination(operand1);
			}
			this->waiting_.back()->setIn(curr);
			this->everyone_.push_back(curr);
		}
		if (!operand2.empty() && has_operand2 == 0) {
			if (isdigit(operand2[0]) || (operand2[0] == '-')) {
				curr = new Constant(CONSTANT);
				char* cstr3 = new char[operand2.length() + 1];
				strcpy(cstr3, operand2.c_str());
				curr->setOutValue(atof(cstr3));
				curr->setDestination(operand2);

				delete[] cstr3;
				cstr3 = nullptr;
			}
			else { //ne bi trebalo nikad da se napravi varijabla
				curr = new Variable(VARIABLE);
				curr->setDestination(operand2);
			}
			this->waiting_.back()->setIn(curr);
			this->everyone_.push_back(curr);
		}
		
	}
	
	inputFile.close();

}




void ExMachina::exec(string file){
	mem = new Memory();
	compiler_filename = file;
	readCompilerFile(file);
	waitingtToProcessing();
	while (!(waiting_.empty()) || !(processing_.empty())) {
		dealWithProcessing();
	}

	//kada se sve zavrsi treba da se odstampa
	writeOutput();
	mem->write(compiler_filename); // ona njoj daje imf fajl
	
	
}

ExMachina* ExMachina::Instance(){
	static ExMachina* instance = new ExMachina();
	return instance;
}


ExMachina::~ExMachina(){
	/*
	int elem_size;
	if (!everyone_.empty()) {
		elem_size = everyone_.size();
		for (int i = 0; i < elem_size; i++) {
			delete everyone_[i];
		}
		for (int i = 0; i < elem_size; i++) {
			everyone_.pop_back();
		}
	}
	elem_size = completed_.size();
	for (int i = 0; i < elem_size; i++) {
		completed_.pop_back();
	}
	if (!processing_.empty()) {
		elem_size = processing_.size(); // ovo vi vec trebalo da je prazno ali za svaki slucaj
		for (int i = 0; i < elem_size; i++) {
			processing_.pop_back();
		}
	}
	if (!waiting_.empty()) {
		elem_size = waiting_.size();
		for (int i = 0; i < elem_size; i++) {
			waiting_.pop_back();
		}
	}
	*/

}

void ExMachina::deleteFieldsForCheckEM() {
	int elem_size;
	if (!everyone_.empty()) {
		elem_size = everyone_.size();
		for (int i = 0; i < elem_size; i++) {
			delete everyone_[i];
		}
		everyone_.clear();
	}
	if (!completed_.empty()) {
		completed_.clear();
		if (!processing_.empty()) {
			processing_.clear();
		}
		if (!waiting_.empty()) {
			waiting_.clear();
		}

	}

	created_event_id.clear();
	output_string.clear();
	compiler_filename.clear();

	delete mem;
	mem = nullptr;
}

	

//ispituje da li su nekoj operaciji obezbedjeni operandi

void ExMachina::waitingtToProcessing(){ //ovde cemo zasigurno imati binarno stablo
	int nw = Configuration::Instance()->getMemoTime();
	int cur_w = 0;
	Element* child = 0;
	for (int i = 0; i < processing_.size(); i++) {
		if (processing_[i]->getType() == ASSIGNMENT)
			cur_w++;
	}

	for (int j = 0; j < waiting_.size();j++) {
		//proci kroz njegovu decu i utvditi da li su spremna za koriscenje


		bool flag1 = 1;
		for (int i = 0; i < waiting_[j]->getIn().size(); i++) {
			child = waiting_[j]->getIn()[i];
			flag1 = flag1 & child->getReady();
		}
		
		
		bool flag2 = waiting_[j]->getType() == ASSIGNMENT;
		
		
		if (flag1 & !flag2) {
			processing_.push_back(waiting_[j]);
			waiting_[j] = nullptr;
		}
			
		else if (flag1 && flag2 && (cur_w < nw)) {
			processing_.push_back(waiting_[j]);
			waiting_[j] = nullptr;
			cur_w++;

		}
	
	}
	//kad obidjemo ceo waiting otklanjamo one operacije koje su presle u procesing
	waiting_.erase(std::remove(waiting_.begin(), waiting_.end(), nullptr), waiting_.end());
}

void ExMachina::dealWithProcessing(){ 

	for (int i = 0; i < processing_.size(); i++) {
		bool created_event = false;
		int id_size = created_event_id.size();
		for (int j = 0; j < id_size; j++) {
			if (processing_[i]->getId() == created_event_id[j]) {
				created_event = true; break;
			}
			
		}
		if (!created_event){
			Event::create(processing_[i], processing_[i]->getDuration(), processing_[i]->getId());
			
			created_event_id.push_back(processing_[i]->getId());
		}
			
	}
	//kada se napuni skedzuler pokrenuti ga
	Scheduler::Instance()->processNow();
	
}

void ExMachina::writeOutputString(int id, int op_duration, int cur_shed_time){
	
	string mica = "[" + to_string(id) + "]" + "     " + "(" + to_string(cur_shed_time - op_duration) + "-" + to_string(cur_shed_time) + ")" + "ns";
	output_string.push_back(mica);
}

void ExMachina::writeOutput(){


	string new_file_name = compiler_filename;
	unsigned int len_without_txt = new_file_name.length() - 4;
	new_file_name.resize(len_without_txt);
	new_file_name.insert(len_without_txt, ".log");


	fstream outputFile(new_file_name, ios::out);

	for (auto& segal : output_string){
		outputFile << segal << endl;
	
	}

	outputFile.close();
}

void ExMachina::setMem(string varName, double val){
	setM(varName, val,mem);
}

void ExMachina::processingToCompleted(int id) {
	for (int i = 0; i < processing_.size(); i++) {
		if (processing_[i]->getId() == id) {
			this->completed_.push_back(processing_[i]);
			processing_[i] = nullptr;
		}
	}

	
	processing_.erase(std::remove(processing_.begin(), processing_.end(), nullptr), processing_.end());

}
