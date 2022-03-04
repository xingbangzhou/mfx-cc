#include "stable.h"
#include "toolbar.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QListView>

ToolBar::ToolBar(QWidget* parent)
    : QWidget(parent)
    , m_listView(new QListView(this))
{
    setObjectName("ToolBar");

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignHCenter);
    layout->addSpacing(32);
    layout->addWidget(m_listView);

}

ToolBar::~ToolBar()
{

}
