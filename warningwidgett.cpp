
#include "warningwidgett.h"

WarningWidgetT::WarningWidgetT(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WarningWidgetT)
{
//    this->ui = new Ui::WarningWidgetT();
    ui->setupUi(this);
    QPalette pal(this->palette());
    pal.setColor(QPalette::Window, QColor(255,255,255, 0));
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    ui->widget->setStyleSheet("QWidget#widget{border-image: url(:/style/images/warning.png);}");
    ui->label->setStyleSheet("background-color: rgb(255, 77, 77);border-radius: 8px;font:28pt;");

}

WarningWidgetT::~WarningWidgetT()
{
    delete ui;
}

