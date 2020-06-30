#ifndef PROGRAM_H
#define PROGRAM_H

#include <iostream>

using namespace std;

class Program {
public:
	static Program* Instance(const string&);
	static Program* returnInstance();
	
	~Program();

	void inToPost(string*);
	int getExpNum();
	string** getVarNameExp();
protected:
	
private:
	static string filename_;
	Program(const string&);
	int expression_num;
	string **var_name_expression = 0; //varijable i njihovi izrazi
	
};

#endif


