#ifndef PROGRAM_H
#define PROGRAM_H

#include <iostream>
#include<map>
using namespace std;

class Program {
public:

	Program(string);
	~Program();

	const string& inToPost(string);

private:
	map<string, string>* var_name_expression; //varijable i njihovi izrazi
	
};

#endif


