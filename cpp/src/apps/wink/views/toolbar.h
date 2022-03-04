#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>

class QLabel;
class QListView;
class ToolBar : public QWidget
{
    Q_OBJECT

public:
    explicit ToolBar(QWidget* parent = nullptr);
    ~ToolBar();

private:
    QListView* m_listView;
};

#endif // TOOLBAR_H
