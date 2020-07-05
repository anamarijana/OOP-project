#include "Compiler.h"
#include"Configuration.h"
#include"Program.h"

Compiler* Compiler::Instance(){
	static Compiler instance;
	return &instance;
}

void Compiler::initiate(const string& filepath1, const string& filepath2){
	Configuration::Instance()->read(filepath1);
	Program::Instance()->read(filepath2);
	this->filename = filepath2;
	int j = 0;
	map<int, string> help = Program::Instance()->getVarNameExp();
	for (auto i = help.begin(); i != help.end(); i++) {
		string* expres = &(i->second);

		ExpressionTree* tree = new ExpressionTree();
		tree->inToPost(expres, i->first);
		tree->build();
		if (Configuration::Instance()->getComp() == true)
			tree->binaryToNary();

		this->forest_gump_.push_back(tree);
	}
	catchOperation();
	tieUp();
	if (Configuration::Instance()->getComp() == true)
		compileAdvanced();
	else { 
		compile();
	}
}

Compiler::~Compiler(){

	int elem_size = all_operations.size();
	
	for (int i = 0; i < elem_size; i++) {
		delete all_operations[i]; // izmeniti destruktor
	}

	for (int i = 0; i < elem_size; i++) {
		all_operations.pop_back();
	}

	elem_size = forest_gump_.size();
	for (int i = 0; i < elem_size; i++) {
		delete forest_gump_[i]; // izmeniti destruktor
	}

	for (int i = 0; i < elem_size; i++) {
		forest_gump_.pop_back();
	}
	

}

void Compiler::catchOperation(){
	for (int i = 0; i < forest_gump_.size(); i++) {
		
		for (int j = 0; j < forest_gump_[i]->getOps().size(); j++) {
			all_operations.push_back(forest_gump_[i]->getOps()[j]);
		}
	}
}
//ovde imamo narno stablo i ukoliko cvor zavisi od promenljive nju zamenjujemo cvorom dodele vrednosti toj promenljivoj
void Compiler:: tieUp() {
	Element* Assign = 0;
	Element* child = 0;
	int all_op_size = all_operations.size();
	
	for(int i=0 ; i<all_op_size;i++){
		int child_size = all_operations[i]->getIn().size();
		for (int j =0; j<child_size; j++){
			child = all_operations[i]->getIn()[j];
			if (child->getType() == VARIABLE){
				Assign = returnAss(child->getDestination());
				all_operations[i]->setInByIndex(j, Assign); //ovo ispraviti na setIn
				delete child; //ne bi trebalo da postoje viseci pokazivaci
				
			}
		}
		
	}
} //posle ove operacije ne bi trebalo da postoje cvorovi sa varijablama vec da je ceo fajl uvezan u stablo


Element* Compiler:: birth(Element* mother){ //fja koja treba da se poziva u okviru napredne kompilacije za cvorove od vise od troje dece
	Element* operand;
	stack <Element*> operands;
	Operation* newMother =0;
	vector <int> index;
	

	for (int j = 0; j <mother->getIn().size();j++){
		operand = mother->getIn()[j];
		if ((operand->getReady() == 1) && (operands.size() < 2)) {
			operands.push(operand);
			index.push_back(j);
		}
	}
	//ako je bila neuspesna misija, tj nije spremno par deteta
	if (operands.size() < 2) return newMother;;
	switch (mother->getType())
	{
	case(ADDITION): 
		newMother = new Addition(ADDITION); break; 
	case(MULTIPLICATION):
		newMother = new Multiplication(MULTIPLICATION); break;
	}
	newMother->setIn(operands.top()); //menja se redosled bolje que
	operands.pop();
	newMother->setIn(operands.top());
	operands.pop();


	
	mother->kickTheBabys(index);// ne moraju biti na kraju

	
		
	mother->setIn(newMother);

	return newMother;

}

void Compiler:: compileAdvanced(){
	string new_file_name = filename;
	
	unsigned int len_without_txt = new_file_name.length() - 4;
	new_file_name.resize(len_without_txt);
	new_file_name.insert(len_without_txt, ".imf");
	this->filename = new_file_name;
	
	fstream outputFile(new_file_name, ios::out);

	string toOutput;
	Element* pos_child;
	setRootsReady();
	vector<Element*> compiled_elemets;
	vector<Element*> pos_children;
	vector <Element*> not_yet = all_operations;

	while (this->roots_ready == 0) { //dok nisu sve promenljive upisane

		for (auto& pointer : not_yet) {
			//svaki put prolazi kroz operacije i upisuje one koje su
		   // trennutno spremni za izvrsavanje

			if (pointer->getIn().size() > 2) {
				pos_child = birth(pointer);
				if(pos_child)pos_children.push_back(pos_child);
				while ((pos_child) && (pointer->getIn().size() > 2)) {
					pos_child = birth(pointer);
					if (pos_child) pos_children.push_back(pos_child);
				}

			}


			else pos_children.push_back(pointer);
			//if (pos_child == nullptr)  continue;
			for (int k = 0; k < pos_children.size(); k++) {
				if (pos_children[k]->getReady() == 0) {
					toOutput.clear();
					compileOne(pos_children[k], toOutput);
					if (!toOutput.empty()) {
						compiled_elemets.push_back(pos_children[k]);
						outputFile << toOutput << endl;

					}
				}

			}
			pos_children.clear();
			
		}
	
		
		setElementsReady(compiled_elemets);
		setRootsReady();
		compiled_elemets.clear();
	}
	
	
	outputFile.close();

}

void Compiler::compileOne(Element* soon_printed, string& toOutput){
	
	
	int static id_ = 1;
	int static token_id = 1;
	Element* child1 = 0;
	Element* child2 = 0;
	child1  = soon_printed->getIn()[0];
	if (soon_printed->getIn().size() == 2) child2 = soon_printed->getIn()[1];
	string destination;
	char mother_operation;
	mother_operation = defineMotherOp(soon_printed);


	if (child2) {
		if (child1->getReady() & child2->getReady()) {
			toOutput = "[" + to_string(id_) + "]" + " " + mother_operation + " " + "t" + to_string(token_id) + " " +
				child2->getDestination() + " " + child1->getDestination();
			if(Configuration::Instance()->getComp() !=1 )soon_printed->setReady(1);
			destination = 't' + to_string(token_id++);
			soon_printed->setDestination(destination);
			id_++;

		}
	}
	else {
		if (child1->getReady()) {
			toOutput = "[" + to_string(id_) + "]" + " " + "=" + " " + soon_printed->getDestination() + " "
				+ child1->getDestination();
			if (Configuration::Instance()->getComp() != 1)soon_printed->setReady(1);
			id_++;
		}
	}
	
}

void Compiler::kickTheOp ( Element* op, vector<Element*>& not_yet){

	
		for (int i = 0; i < not_yet.size(); i++) {

			if (not_yet[i] == op) {
				rotate(not_yet.begin(), not_yet.begin() + i, not_yet.end());
				not_yet.pop_back();
				return;
			}
		}

		
	
}

Element* Compiler:: returnAss(string destination){
	for (int i = 0; i<all_operations.size(); i++){
		if (all_operations[i]->getDestination() == destination)
			return all_operations[i];
	}
}

void Compiler::compile(){
	string new_file_name = filename;

	unsigned int len_without_txt = new_file_name.length() - 4;
	new_file_name.resize(len_without_txt);
	new_file_name.insert(len_without_txt, ".imf");
	this->filename = new_file_name;
	fstream outputFile(new_file_name, ios::out);

	string toOutput;
	//ofstream outputFile;// an output file stream object!
	//outputFile.open("new_file_name");
							 // open the file named "input_da
	setRootsReady();
	
	
	while (this->roots_ready == 0) {
		for (int i = 0; i < all_operations.size(); i++) {
			compileOne(all_operations[i],toOutput);
			outputFile << toOutput << endl;
			toOutput.clear();
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

void Compiler::setElementsReady(vector<Element*>& compiled_elements){
	for (int i = 0; i < compiled_elements.size(); i++)
		compiled_elements[i]->setReady(1);

}

const string& Compiler::giveMachinaFile(){
	return this->filename;
}

char Compiler::defineMotherOp(Element* mother){

	Element_Type type = mother->getType();

	switch (type)
	{

	case ADDITION:
		return '+'; break;
	case MULTIPLICATION:
		return '*'; break;
	case EXPONENTIATION:
		return '^'; break;
	case ASSIGNMENT:
		return '='; break;

	}
	
}



