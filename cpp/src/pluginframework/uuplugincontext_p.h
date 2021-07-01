#ifndef UUPLUGINCONTEXTPRIVATE_H
#define UUPLUGINCONTEXTPRIVATE_H

class uuPluginPrivate;

class uuPluginContextPrivate
{
public:
    uuPluginPrivate* plugin;

    uuPluginContextPrivate(uuPluginPrivate* plugin);

    void invalidate();
};

#endif // UUPLUGINCONTEXTPRIVATE_H
