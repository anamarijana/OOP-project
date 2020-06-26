#ifndef PROGRAM_H
#define PROGRAM_H

#include <iostream>

using namespace std;

class Program {
public:

	Program(string);

	const string& inToPost(string);

private:
	string variables; // cuva imena promenljivima
	string* var_exp; // cuva njihove izraze
};

#endif


