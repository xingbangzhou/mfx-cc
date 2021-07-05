#ifndef PLUGINASERVICE_H
#define PLUGINASERVICE_H

#include <QObject>

#include "lepluginframework/leplugincontext.h"
#include "shared/testaservice.h"

class PluginAService : public QObject,
	public TestAService
{
	Q_OBJECT
	Q_INTERFACES(TestAService)
public:
    explicit PluginAService(LePluginContext* pc);
	
	void callA() Q_DECL_OVERRIDE;
};

#endif // PLUGINASERVICE_H
