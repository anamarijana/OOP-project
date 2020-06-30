#include "ExMachina.h"
#include "Event.h"
#include "Sched.h"
#include <fstream>
#include<iostream>


void ExMachina::eventOccured(int Id,int op_duration, int cur_shed_time){ //slusa vesti od notify
	writeOutput(Id, op_duration, cur_shed_time);
	waitingtToProcessing();
	processingToCompleted(Id);
}

const string& ExMachina::getCompFilename()
{
	return this->compiler_filename;
}

void ExMachina::readCompilerFile(const string& filename){
	fstream inputFile(filename, ios::in);
	char buffer;
	Element* curr;

	//[17]y = t1
	//[23]r = t1*t2

	while (inputFile.peek() != EOF) {
		string id;
		char operation;
		string operand1;
		string operand2;
		string destination;
		char assignment;
		
		char c;
		inputFile >> buffer;
		while (inputFile.peek() != ']') {
			inputFile >> c;
			id += c;
		}
		inputFile >> buffer; // za ]
		
		
		while (inputFile.peek() != '=') {
			char c;
			inputFile >> c;
			destination += c;
		}

		inputFile >> assignment;
		while (isalpha(inputFile.peek()) | isdigit(inputFile.peek())) {
			char c;
			inputFile >> c;
			operand1 += c;
		}
		inputFile >> buffer;
		if (buffer == '\n') {
			operation = assignment;
			continue;
		}
		operation = buffer;
		while (isalpha(inputFile.peek()) | isdigit(inputFile.peek())) {
			char c;
			inputFile >> c;
			destination += c;
		}
		inputFile >> buffer; //novi red
		if (operation == '+') {
			curr = new Addition(ADDITION,stoi(id));
			curr->setDuration(Configuration::returnInstance()->getAddTime());
		}
		else if (operation == '*') {
			curr = new Multiplication(MULTIPLICATION, stoi(id));
			curr->setDuration(Configuration::returnInstance()->getMultiTime());

		}
		else if (operation == '^') {
			curr = new Exponentiation(EXPONENTIATION,stoi(id));
			curr->setDuration(Configuration::returnInstance()->getExpTime());

		}
		else {
			curr = new Assignment(ASSIGNMENT, stoi(id));
			curr->setDuration(Configuration::returnInstance()->getExpTime());

		}
		if (curr) curr->setDestination(destination);
		
		this->everyone_.push_back(curr);
		this->waiting_.push_back(curr);
		bool has_operand1 = 0;
		bool has_operand2 = 0;
		for (int i = 0; i < everyone_.size(); i++) {
			if (everyone_[i]->getDestination() == operand1) {
				curr->getIn().push_back(everyone_[i]);
				has_operand1 = 1;
			}
			if (everyone_[i]->getDestination() == operand2) {
				curr->getIn().push_back(everyone_[i]);
				has_operand2 = 1;
			}
		}

		if (!operand2.empty() && has_operand2 == 0) {
			if (isdigit(operand2[0])) {
				curr = new Constant(CONSTANT);
				curr->setOutValue(stoi(operand2));
			}
			else {
				curr = new Variable(VARIABLE);
				curr->setDestination(operand2);
			}
			this->waiting_.back()->getIn().push_back(curr);
			this->everyone_.push_back(curr);
		}
		if (has_operand1 == 0) {
			if (isdigit(operand2[0])) {
				curr = new Constant(CONSTANT);
				curr->setOutValue(stoi(operand2));
			}
			else {
				curr = new Variable(VARIABLE);
				curr->setDestination(operand2);
			}
			this->waiting_.back()->getIn().push_back(curr);
			this->everyone_.push_back(curr);
		}
		
	}
	
	inputFile.close();
}

string ExMachina::compiler_filename;

ExMachina* ExMachina::Instance(const string& filename){
		static ExMachina instance(filename);
		compiler_filename = filename;
		return &instance;
		
	}

ExMachina* ExMachina::returnInstance(){
	
	return Instance(compiler_filename);
}

ExMachina::~ExMachina(){
}

ExMachina::ExMachina(const string& filename){
	readCompilerFile(filename);
	waitingtToProcessing();
	while (!(waiting_.empty())) {
		dealWithProcessing();
	}
}

//ispituje da li su nekoj operaciji obezbedjeni operandi

void ExMachina::waitingtToProcessing(){ //ovde cemo zasigurno imati binarno stablo
	
	for (int j = 0; j < waiting_.size();j++) {
		//proci kroz njegovu decu i utvditi da li su spremna za koriscenje
		bool flag = waiting_[j]->getInReady()[0] && waiting_[j]->getInReady()[0];
		if (flag) {
			processing_.push_back(waiting_[j]);
			waiting_.erase(waiting_.begin() + j);
		}
	
	}

}

void ExMachina::dealWithProcessing(){ 

	for (int i = 0; i < processing_.size(); i++) {
		Event::create(processing_[i], processing_[i]->getDuration(), processing_[i]->getId());
	}
	//kada se napuni skedzuler pokrenuti ga
	Scheduler::Instance()->processNow();
	
}

void ExMachina::writeOutput(int id, int op_duration, int cur_shed_time){
	string ex_m_filename = compiler_filename;
	fstream outputFile(ex_m_filename, ios::out);
	outputFile << "[" << id << "]" << " " << "(" << cur_shed_time - op_duration << ":" << cur_shed_time << ")" << endl;
	outputFile.close();
}

void ExMachina::processingToCompleted(int id) {
	this->completed_.push_back(processing_[id]);
	this->processing_.erase(processing_.begin() + id);

}
