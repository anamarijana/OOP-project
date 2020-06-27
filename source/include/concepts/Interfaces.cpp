#include "Interfaces.h"
#include "../../../oop_pr/ExMachina.h"


void Final::notify(ID id){
	int Id = id;
	getMachina()->processingToCompleted(Id);

}
