#ifndef PROGRAM_H
#define PROGRAM_H

#include <iostream>
#include<map>
#include<string>

using namespace std;

class Program {
public:
	static Program* Instance();

	
	~Program();
	void read(const string&);
	map<int, string> getVarNameExp();
protected:
	
private:

	Program();
	
	map <int,string> var_name_expression; //varijable i njihovi izrazi
	
};

#endif


