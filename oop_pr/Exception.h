#ifndef EXP_h
#define EXP_H

#include<exception>

class NegativeTime : public std::exception {
public:
	NegativeTime(const char* c) :exception(c) {};
protected:
private:
};

class UnexpectedNegativeNumber : public std::exception {
public:
	UnexpectedNegativeNumber(const char* c) :exception(c) {};
protected:
private:
};
class VarNotAvailableException : public std::exception {
public:
	VarNotAvailableException(const char* c) :exception(c) {};
protected:
private:
};

#endif