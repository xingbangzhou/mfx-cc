#ifndef XHPLUGINCONTEXTPRIVATE_H
#define XHPLUGINCONTEXTPRIVATE_H

class XhPluginPrivate;

class XhPluginContextPrivate
{
public:
    XhPluginPrivate* plugin;

    XhPluginContextPrivate(XhPluginPrivate* plugin);

    bool isPluginContextValid() const;

    void invalidate();
};

#endif // XHPLUGINCONTEXTPRIVATE_H
