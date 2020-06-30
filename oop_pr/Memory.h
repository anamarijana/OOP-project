#ifndef MEMORY_H
#define MEMORY_H
#include <map>
#include <string>
class Memory {
public:

	static Memory* Instance();
	void set(string varName, double val); 
	double get(string varName);
protected:
	Memory() {};
	
private:
	map<string, int> final_destination_;
};


#endif
