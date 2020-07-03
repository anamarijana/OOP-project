#include "ExMachina.h"
#include "Event.h"
#include "Sched.h"
#include <fstream>
#include<iostream>


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
		for (int i = 0; i < everyone_.size(); i++) {
			if (isdigit(operand1[0])) {
				char* cstr1 = new char[operand1.length() + 1];
				strcpy(cstr1, operand1.c_str());
				if (everyone_[i]->getOutValue() == atof(cstr1)) {
					curr_op->setIn(everyone_[i]);
					has_operand1 = 1;
				}
			}
			else if (isalpha(operand1[0])) {
				if (everyone_[i]->getDestination() == operand1) {
					curr_op->setIn(everyone_[i]);
					has_operand1 = 1;

				}
			}
			if (isdigit(operand2[0])) {
				char* cstr2 = new char[operand2.length() + 1];
				strcpy(cstr2, operand2.c_str());
				if (everyone_[i]->getOutValue() == atof(cstr2)) {
					curr_op->setIn(everyone_[i]);
					has_operand2 = 1;
				}
			}
			else if (isalpha(operand2[0])) {
				if (everyone_[i]->getDestination() == operand2) {
					curr_op->setIn(everyone_[i]);
					has_operand2 = 1;
				}
			}
		}

		if (!operand2.empty() && has_operand2 == 0) {
			if (isdigit(operand2[0])) {
				curr = new Constant(CONSTANT);
				curr->setOutValue(stoi(operand2));
				curr->setDestination(operand2);
			}
			else {
				curr = new Variable(VARIABLE);
				curr->setDestination(operand2);
			}
			this->waiting_.back()->setIn(curr);
			this->everyone_.push_back(curr);
		}
		if (has_operand1 == 0) {
			if (isdigit(operand1[0])) {
				curr = new Constant(CONSTANT);
				curr->setOutValue(stoi(operand1));
				curr->setDestination(operand1);
			}
			else {
				curr = new Variable(VARIABLE);
				curr->setDestination(operand1);
			}
			this->waiting_.back()->setIn(curr);
			this->everyone_.push_back(curr);
		}
		
	}
	
	inputFile.close();
}




void ExMachina::exec(string file){
	compiler_filename = file;
	readCompilerFile(file);
	waitingtToProcessing();
	while (!(waiting_.empty()) || !(processing_.empty())) {
		dealWithProcessing();
	}

	//kada se sve zavrsi treba da se odstampa
	writeOutput();
	Memory::Instance()->write(compiler_filename);
	
	
}

ExMachina* ExMachina::Instance(){
	static ExMachina instance;
	return &instance;
}


ExMachina::~ExMachina(){
}

ExMachina::ExMachina(){}

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
		Event::create(processing_[i], processing_[i]->getDuration(), processing_[i]->getId());
	}
	//kada se napuni skedzuler pokrenuti ga
	Scheduler::Instance()->processNow();
	
}

void ExMachina::writeOutputString(int id, int op_duration, int cur_shed_time){
	
	string mica = "[" + to_string(id) + "]" + "     " + "(" + to_string(cur_shed_time - op_duration) + ":" + to_string(cur_shed_time) + ")" + "ns";
	output_string.push_back(mica);
}

void ExMachina::writeOutput(){
	//string ex_m_filename = compiler_filename;
	string ex_m_filename = "pera_retard.txt";
	fstream outputFile(ex_m_filename, ios::out);

	for (auto& segal : output_string){
		outputFile << segal << endl;
	
	}

	outputFile.close();
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
