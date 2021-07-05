#ifndef LEPLUGINCONTEXTPRIVATE_H
#define LEPLUGINCONTEXTPRIVATE_H

class LePluginPrivate;

class LePluginContextPrivate
{
public:
    LePluginPrivate* plugin;

    LePluginContextPrivate(LePluginPrivate* plugin);

    bool isPluginContextValid() const;

    void invalidate();
};

#endif // LEPLUGINCONTEXTPRIVATE_H
