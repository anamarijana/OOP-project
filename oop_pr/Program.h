#ifndef PROGRAM_H
#define PROGRAM_H

#include <iostream>

using namespace std;

class Program {
public:

	Program(const string&);
	~Program();

	const string& inToPost(string*);
	int getExpNum();
	string** getVarNameExp();
protected:
	
private:
	int expression_num;
	string **var_name_expression; //varijable i njihovi izrazi
	
};

#endif


