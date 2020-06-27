#include "Interfaces.h"
#include "../../../oop_pr/ExMachina.h"
#include "Sched.h"

void Tattletale ::notify(ID id){
	int Id = id;
	
	ExMachina::Instance()->elementOccured(Id,Scheduler::Instance()->getCurTime());
	}
