#include "ExMachina.h"
#include "Event.h"

ExMachina::ExMachina(){

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
		
		Event* ev  = Event(targetElement, processing_[i]->getDuration(), i+1);
	}
}

void ExMachina::processingToCompleted(int id) {
	this->completed_.push_back(processing_[id]);
	this->processing_.erase(processing_.begin() + id);

}

