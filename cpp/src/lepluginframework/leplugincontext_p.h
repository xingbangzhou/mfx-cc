#ifndef LEPLUGINCONTEXTPRIVATE_H
#define LEPLUGINCONTEXTPRIVATE_H

class LePluginPrivate;

class LePluginContextPrivate
{
public:
    LePluginPrivate* plugin;

    LePluginContextPrivate(LePluginPrivate* plugin);

    void invalidate();
};

#endif // LEPLUGINCONTEXTPRIVATE_H
