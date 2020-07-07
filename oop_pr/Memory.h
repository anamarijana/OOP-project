#ifndef MEMORY_H
#define MEMORY_H
#include <map>
#include <string>


using namespace std;

class Memory {
public:
	
	
	Memory() {};
	void deleteForCheck();
	~Memory();
	Memory(const Memory&) = delete;
	Memory(Memory&&) = delete;
	
	//static Memory* Instance();
	friend void setM(string varName, double val, Memory* mem); 
	void set(string varName, double val);
	double get(string varName);
	void write(string file);

protected:

	
private:
	map<string, double> final_destination_; // podrazumevani destruktor
};


#endif
