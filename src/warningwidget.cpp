#include "warningwidget.h"
#include "ui_warningwidget.h"

WarningWidget::WarningWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WarningWidget)
{
    ui->setupUi(this);
    QPalette pal(this->palette());
    pal.setColor(QPalette::Window, QColor(255,255,255, 0));
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    ui->widget->setStyleSheet("QWidget#widget{border-image: url(:/style/images/warning.png);}");
    ui->label->setStyleSheet("background-color: rgb(255, 77, 77);border-radius: 8px;font:28pt;");
//    ui->widget->move(200,200);
//    ui->widget->setGeometry(1250,300,750,350);
}

WarningWidget::~WarningWidget()
{
    delete ui;
}
