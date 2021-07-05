#ifndef TESTASERVICE_H
#define TESTASERVICE_H

#include <qglobal.h>

struct TestAService
{
	virtual ~TestAService() {}

	virtual void callA() = 0;
};

Q_DECLARE_INTERFACE(TestAService, "plugina_test.TestAService")

#endif // TESTASERVICE_H