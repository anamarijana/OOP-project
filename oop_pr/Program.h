#ifndef PROGRAM_H
#define PROGRAM_H


#include<map>
#include<string>

using namespace std;

class Program {
public:

	

	static Program* Instance();
	
	Program(const Program&) = delete;
	Program(Program&&) = delete;
	
	~Program() = default;
	void read(const string&);
	map<int, string> getVarNameExp();
protected:
	
private:

	Program();
	
	map <int,string> var_name_expression; 
	
};

#endif


