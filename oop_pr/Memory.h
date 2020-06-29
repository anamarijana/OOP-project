#ifndef MEMORY_H
#define MEMORY_H
#include <map>

class Memory {
public:

	static Memory* Instance();
	void enterFinalDestination(char, int); //promenljiva moze biti samo char // promeniti posle za string
protected:
	Memory() {};
	
private:
	map<char, int> final_destination_;
};


#endif
