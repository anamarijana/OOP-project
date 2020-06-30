#include "Compiler.h"

Compiler* Compiler::Instance(const string& filepath1, const string filepath2){
	static Compiler *instance = new Compiler(filepath1,filepath2);
	return instance;
}

void Compiler::catchOperation(){
	for (int i = 0; i < forest_gump_.size(); i++) {
		
		for (int j = 0; j < forest_gump_[i]->getOp().size(); j++) {
			all_operations.push_back(forest_gump_[i]->getOp()[j]);
		}
	}
}

void Compiler::compile(){
	setRootsReady();
	int id = 1;
	string new_file_name = this->filename + ".imf";
	fstream outputFile(new_file_name, ios::out);
	
	while (this->roots_ready == 0) {
		for (int i = 0; i < all_operations.size(); i++) {
			Element* child1 = all_operations[i]->getIn()[0];
			Element* child2 = all_operations[i]->getIn()[1];
			string destination;
			if (child2) {
				if (child1->getReady() & child2->getReady()) {
					outputFile << "[" << id++ << "]" << " " << "t" << id << "=" <<
						child1->getDestination() << all_operations[i]->getOp() << child2->getDestination();
					all_operations[i]->setReady(1);
					destination = 't' + id;
					all_operations[i]->setDestination(destination);
					id++;
				}
			}
			else {
				if (child1->getReady()) {
					outputFile << "[" << id++ << "]" << " " << all_operations[i]->getDestination()
						<< "=" << child1->getDestination();
					all_operations[i]->setReady(1);
				}
			}
		}
		setRootsReady();
	}
	outputFile.close();
}

void Compiler::setRootsReady(){
	this->roots_ready = 1;
	for (int i = 0; i < forest_gump_.size(); i++) {
		this-> roots_ready = this->roots_ready & this->forest_gump_[i]->getRoot()->getReady();
	}
}

const string& Compiler::giveMachinaFile(){
	return this->filename + ".imf";
}

Compiler::Compiler(const string& filepath1, const string filepath2){
	Configuration::Instance(filepath1);
	Program::Instance(filepath2);
	this->filename = filepath2;
	int j = 0;
	map<int, string> help = Program::returnInstance()->getVarNameExp();
	for (auto i = help.begin(); i != help.end(); i++) {
		string* expres = &(i->second);
		 ExpressionTree* tree = new ExpressionTree(expres);
		 this->forest_gump_.push_back(tree);
	}
	catchOperation();
	compile();
}

