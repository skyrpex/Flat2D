#include "TextureDirWidget.hpp"
#include "TextureIconProvider.hpp"
#include <styledbar.h>
//#include <QActionGroup>
#include <QLabel>
#include <QToolBar>
#include <QTreeView>
#include <QFileSystemModel>
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>

//static const int SmallSize = 0;
//static const int MediumSize = 32;
//static const int BigSize = 64;
static const QSize IconSize(64, 64);
static const char LabelText[] = "Texture directory";

TextureDirWidget::TextureDirWidget(QWidget *parent) :
    QWidget(parent),
    m_toolBar(new Manhattan::StyledBar),
    m_view(new QTreeView),
    m_model(new QFileSystemModel)
{
//    QAction *small = m_toolBar->addAction(tr("Small icon size"));
//    small->setCheckable(true);
//    connect(small, SIGNAL(triggered()), this, SLOT(setSmallIconSize()));

//    QAction *medium = m_toolBar->addAction(tr("Medium icon size"));
//    medium->setCheckable(true);
//    connect(medium, SIGNAL(triggered()), this, SLOT(setMediumIconSize()));

//    QAction *big = m_toolBar->addAction(tr("Big icon size"));
//    big->setCheckable(true);
//    connect(big, SIGNAL(triggered()), this, SLOT(setBigIconSize()));

//    QActionGroup *group = new QActionGroup(m_toolBar);
//    group->addAction(small);
//    group->addAction(medium);
//    group->addAction(big);

//    m_toolBar->setSingleRow(false);
    {
        QHBoxLayout *layout = new QHBoxLayout(m_toolBar);
        layout->setMargin(0);
        layout->setSpacing(4);
        layout->setContentsMargins(5, 0, 0, 0);
        layout->addWidget(new QLabel(tr(LabelText)));
    }

    connect(m_model, SIGNAL(directoryLoaded(QString)), m_view, SLOT(expandAll()));
    m_model->setRootPath(QDir::currentPath());
    m_model->setNameFilterDisables(false);
    m_model->setNameFilters(nameFilters());
    m_model->setIconProvider(new TextureIconProvider);

    m_view->setDragEnabled(true);
    m_view->setDragDropMode(QAbstractItemView::DragOnly);
    m_view->setHeaderHidden(true);
    m_view->setIconSize(IconSize);
    m_view->setModel(m_model);
    m_view->setRootIndex(m_model->index(QDir::currentPath()));
    for(int i = 1; i < m_model->columnCount(); ++i) {
        m_view->setColumnHidden(i, true);
    }
    m_view->setFrameStyle(QFrame::NoFrame);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_toolBar);
    layout->addWidget(m_view);
}
QStringList TextureDirWidget::nameFilters() const
{
    return QStringList() << "*.jpg"
                         << "*.png";
}
