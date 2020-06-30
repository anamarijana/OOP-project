#include "Compiler.h"

Compiler* Compiler::Instance(const string& filepath1, const string filepath2){
	static Compiler *instance = new Compiler(filepath1,filepath2);
	return instance;
}

void Compiler::catchOperation(){
	for (int i = 0; i < forest_gump_.size(); i++) {
		all_operations.insert(all_operations.end(), forest_gump_[i]->getOp().begin(), forest_gump_[i]->getOp().end());

	}
}

void Compiler::compile(){
	setRootsReady();
	int id = 1;
	string new_file_name = this->filename;
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

Compiler::Compiler(const string& filepath1, const string filepath2){
	this->Config = new Configuration(filepath1);
	this->Prog = new Program(filepath2);
	this->filename = filepath2;
	for (int i = 0; i < this->Prog->getExpNum(); i++) {
		this->forest_gump_[i] = new ExpressionTree(this->Prog->getVarNameExp()[i],*(this->Config));
	}
	catchOperation();
}

