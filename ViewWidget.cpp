#include "ViewWidget.hpp"
#include "ui_ViewWidget.h"
#include <QToolButton>
#include <QSpacerItem>

ViewWidget::ViewWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewWidget)
{
    ui->setupUi(this);

    {
        QButtonGroup *group = new QButtonGroup(this);
        group->addButton(ui->createButton);
        group->addButton(ui->transformButton);
        group->addButton(ui->parentEditButton);
    }
    ui->transformButton->setChecked(true);


    {
        QButtonGroup *group = new QButtonGroup(this);
        group->addButton(ui->bonesButton);
        group->addButton(ui->attachmentsButton);
    }
    ui->bonesButton->setChecked(true);
}

ViewWidget::~ViewWidget()
{
    delete ui;
}
