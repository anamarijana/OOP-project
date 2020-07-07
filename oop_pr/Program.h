#ifndef PROGRAM_H
#define PROGRAM_H


#include<map>
#include<string>
#include<vector>

using namespace std;

class Program {
public:

	
	void deleteForCheck();
	static Program* Instance();
	
	Program(const Program&) = delete;
	Program(Program&&) = delete;
	
	~Program();
	void read(const string&);
	vector<string> getVarNameExp();
protected:
	
private:

	Program();
	vector<string> var_name_expression;
	//map <int,string> var_name_expression; 
	
};

#endif


