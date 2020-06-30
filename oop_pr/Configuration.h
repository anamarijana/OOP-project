#ifndef KONFIGURACIJA_H
#define KONFIGURACIJA_H

#include <iostream>

using namespace std;

class Configuration {
public:
	Configuration(const string& filepath);
	
	int getMultiTime();
	int getAddTime();
	int getExpTime();
	int getAssTime();
	int getMemoTime();
	bool getCompTime();
protected:
	
private:
	int Ta = 0;
	int Tm = 0;
	int Tw = 0;
	int Te = 0;
	int Nw = 0;
	bool compilation = 0;
};

#endif



