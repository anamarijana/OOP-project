#ifndef TATTLETALE
#define TATTLETALE
#include"Interfaces.h"


class Tattletale : public ITimedElement { //druge klase znaju da je izvedena
public:
	virtual void notify(ID id) override;
protected:

private:

};

#endif