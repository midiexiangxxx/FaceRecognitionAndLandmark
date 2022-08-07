#include "modifyuserinfo.h"
#include "ui_modifyuserinfo.h"

ModifyUserInfo::ModifyUserInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModifyUserInfo)
{
    ui->setupUi(this);
    QPalette pal(this->palette());
    pal.setColor(QPalette::Window, QColor(31,35,38, 24));
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    ui->widget->setStyleSheet("QWidget#widget{border-image: url(:/style/images/menu_rect.png);}");
}

ModifyUserInfo::~ModifyUserInfo()
{
    delete ui;
}
