#ifndef PROGRAM_H
#define PROGRAM_H

#include <iostream>
#include<map>
#include<string>

using namespace std;

class Program {
public:
	static Program* Instance(const string&);
	static Program* returnInstance();
	
	~Program();

	void inToPost(string*,int);
	map<int, string> getVarNameExp();
protected:
	
private:
	static string filename_;
	Program(const string&);
	
	map <int,string> var_name_expression; //varijable i njihovi izrazi
	
};

#endif


