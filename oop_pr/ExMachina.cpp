#include "ExMachina.h"
#include "Event.h"
#include "Sched.h"
#include <fstream>
#include<iostream>


void ExMachina::eventOccured(int Id, int cur_shed_time){ //slusa vesti od notify
	
	writeOutput(cur_shed_time);
	eventOccured(Id, cur_shed_time);
	waitingtToProcessing();
}

void ExMachina::saveTokens(int token_id, int token_value){
	this->way_station_.insert(pair<int, int>(token_id, token_value));
}

void ExMachina::readCompilerFile(string filename){
	fstream inputFile(filename, ios::in);
	char buffer;
	Element* curr;

	//[17]y = t1
	//[23]r = t1*t2

	while (inputFile.peek() != EOF) {
		int id;
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
			operation = buffer;
			continue;
		}
		inputFile >> operation;
		while (isalpha(inputFile.peek()) | isdigit(inputFile.peek())) {
			char c;
			inputFile >> c;
			destination += c;
		}
		inputFile >> buffer; //novi red
		if (operation == '+')
			curr = new Addition(ADDITION);
		else if (operation == '*')
			curr = new Multiplication(MULTIPLICATION);
		else if (operation == '^')
			curr = new Exponentiation(EXPONENTIATION);
		else
			curr = new Assignment(ASSIGNMENT);
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
			if (isdigit(operand2[0]))
				curr = new Constant(CONSTANT);
			else
				curr = new Variable(VARIABLE);
			this->waiting_.back()->getIn().push_back(curr);
			this->everyone_.push_back(curr);
		}
		if (has_operand1 == 0) {
			if (isdigit(operand2[0]))
				curr = new Constant(CONSTANT);
			else
				curr = new Variable(VARIABLE);
			this->waiting_.back()->getIn().push_back(curr);
			this->everyone_.push_back(curr);
		}
		
	}
	
	inputFile.close();
}


ExMachina* ExMachina::Instance(){
		static ExMachina instance;
		return &instance;
	}

ExMachina::~ExMachina(){
}

//smestamo sve operacije u bazen za cekanje
void ExMachina::setWaiting(const vector<Element*>& operations_){
	this->waiting_ = operations_;
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
//CONSTANT, VARIABLE, ADDITION, MULTIPLICATION, EXPONENTIATION, ASSIGNMENT
void ExMachina::dealWithProcessing(){ 
	Tattletale* targetElement;
	for (int i = 0; i < processing_.size(); i++) {
		Event::create(processing_[i], processing_[i]->getDuration(), processing_[i]->getId());
	}
}

void ExMachina::writeOutput(int cur_shed_time){
}

void ExMachina::processingToCompleted(int id) {
	this->completed_.push_back(processing_[id]);
	this->processing_.erase(processing_.begin() + id);

}
