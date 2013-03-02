#ifndef VIEWWIDGET_HPP
#define VIEWWIDGET_HPP

#include <QWidget>

namespace Ui {
class ViewWidget;
}

class ViewWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ViewWidget(QWidget *parent = 0);
    ~ViewWidget();
    
private:
    Ui::ViewWidget *ui;
};

#endif // VIEWWIDGET_HPP
