#ifndef TEXTUREDIRWIDGET_H
#define TEXTUREDIRWIDGET_H

#include <QWidget>

namespace Manhattan {
class StyledBar;
}
class QTreeView;
class QFileSystemModel;

class TextureDirWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit TextureDirWidget(QWidget *parent = 0);

private:
    QStringList nameFilters() const;

    Manhattan::StyledBar *m_toolBar;
    QTreeView *m_view;
    QFileSystemModel *m_model;
};

#endif // TEXTUREDIRWIDGET_H
