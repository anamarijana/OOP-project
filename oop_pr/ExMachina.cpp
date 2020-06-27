#include "ExMachina.h"
#include "Event.h"
#include "Sched.h"
#include <fstream>
#include<iostream>

void ExMachina::elementOccured(int Id, int cur_shed_time){ //slusa vesti od notify
	
	writeOutput(cur_shed_time);
	availableElement(Id);
	elementOccured(Id, cur_shed_time);
	waitingtToProcessing();
}

void ExMachina::readCompilerFile(string filename){
	fstream inputFile(filename, ios::in);
	char buffer;
	Element* curr;
	while (inputFile.peek() != EOF) {
		int id;
		char operation;
		string operand1;
		string operand2;
		string destination;

		
		inputFile >> buffer;
		inputFile >> id;
		inputFile >> buffer;
		while (inputFile.peek() != '=') {
			char c;
			inputFile >> c;
			destination += c;
		}
		inputFile >> buffer;
		while (isalpha(inputFile.peek()) | isdigit(inputFile.peek())) {
			char c;
			inputFile >> c;
			destination += c;
		}
		inputFile >> operation;
		while (isalpha(inputFile.peek()) | isdigit(inputFile.peek())) {
			char c;
			inputFile >> c;
			destination += c;
		}
		inputFile >> buffer;
		if (operation == '+')
			curr = new Addition(ADDITION);
		else if (operation == '*')
			curr = new Multiplication(MULTIPLICATION);
		else if (operation == '^')
			curr = new Exponentiation(EXPONENTIATION);
		else
			curr = new Assignment(ASSIGNMENT);


		
		
	
	
	
	}


	inputFile.close();
}

ExMachina::ExMachina(){

}
ExMachina* ExMachina::Instance(){
		static ExMachina instance;
		return &instance;
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
	ITimedElement* targetElement;
	for (int i = 0; i < processing_.size(); i++) {
		//prodjemo kroz elemente u processingu i utvrdjujemo kog su tipa
		switch (processing_[i]->getType())
			case CONSTANT :{


		}
		
		create(targetElement, processing_[i]->getDuration(), i+1);
	}
}

void ExMachina::processingToCompleted(int id) {
	this->completed_.push_back(processing_[id]);
	this->processing_.erase(processing_.begin() + id);

}