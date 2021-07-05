#ifndef TESTBSERVICE_H
#define TESTBSERVICE_H

#include <qglobal.h>

struct TestBService
{
	virtual ~TestBService() {}

	virtual void callB() = 0;
};

#endif // TESTBSERVICE_H