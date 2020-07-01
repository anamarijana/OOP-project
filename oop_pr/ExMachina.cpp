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

const string& ExMachina::getCompFilename(){
	return this->compiler_filename;
}

void ExMachina::readCompilerFile(const string& filename){
	fstream inputFile(filename, ios::in);
	string line;
	while (inputFile.eof())
	{
		inputFile >> line;
		cout << line << '\n';
	}
	inputFile.close();
	
	
	/*
	fstream inputFile(filename, ios::in);
	string operand1;
	string operand2;
	string destination;
	string id;
	
	//[2] = a t1
	//[3] ^ t1 x 3

	while (inputFile.peek() != EOF) {
		operand1.clear();
		operand2.clear();
		destination.clear();
		id.clear();
		
		char buffer;
		char operation;
		char assignment;
		char c;
		
		Element* curr = 0;
		Operation* curr_op = 0;


		inputFile >> buffer;
		while (1) {
			inputFile >> c;
			if (c == ']') break;
			id += c;
		}
		cout << buffer;
		cout << c;
		
		inputFile >> operation; cout << operation<<endl;
		inputFile >> destination; if (inputFile.peek() == EOF) break;
		inputFile >> operand1;

		if (inputFile.peek() != '\n') inputFile >> operand2;
	
		if (operation == '+') {
			curr_op = new Addition(ADDITION,stoi(id), Configuration::returnInstance()->getAddTime());
			
		}
		else if (operation == '*') {
			curr_op = new Multiplication(MULTIPLICATION, stoi(id), Configuration::returnInstance()->getMultiTime());

		}
		else if (operation == '^') {
			curr_op = new Exponentiation(EXPONENTIATION,stoi(id), Configuration::returnInstance()->getExpTime());

		}
		else if (operation == '=') {
			curr_op = new Assignment(ASSIGNMENT, stoi(id), Configuration::returnInstance()->getAssTime());

		}
		if (curr_op) curr_op->setDestination(destination);
		
		this->everyone_.push_back(curr_op);
		this->waiting_.push_back(curr_op);
		bool has_operand1 = 0;
		bool has_operand2 = 0;
		for (int i = 0; i < everyone_.size(); i++) {
			if (isdigit(operand1[0])) {
				if (everyone_[i]->getOutValue() == stoi(operand1)) {
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
				if (everyone_[i]->getOutValue() == stoi(operand2)) {
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
	
	inputFile.close();*/
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
