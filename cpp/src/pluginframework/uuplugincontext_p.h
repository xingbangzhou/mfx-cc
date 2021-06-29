#ifndef UUPLUGINCONTEXT_P_H
#define UUPLUGINCONTEXT_P_H

class uuPluginPrivate;

class uuPluginContextPrivate
{
public:

    uuPluginPrivate* plugin;

    uuPluginContextPrivate(uuPluginPrivate* plugin);

    void isPluginContextValid() const;

    void invalidate();
};

#endif // UUPLUGINCONTEXT_P_H
