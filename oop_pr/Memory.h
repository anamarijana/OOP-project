#ifndef MEMORY_H
#define MEMORY_H
#include <map>
#include <string>


using namespace std;

class Memory {
public:
	~Memory();
	Memory(const Memory&) = delete;
	Memory(Memory&&) = delete;
	
	static Memory* Instance();
	void set(string varName, double val); 
	double get(string varName);
	void write(string file);

protected:
	Memory() {};
	
private:
	map<string, double> final_destination_; // podrazumevani destruktor
};


#endif
