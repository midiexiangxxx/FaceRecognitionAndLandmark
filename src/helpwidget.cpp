#include "helpwidget.h"
#include "ui_helpwidget.h"
#include <QTabBar>
HelpWidget::HelpWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HelpWidget)
{
    ui->setupUi(this);

    ui->widget->setStyleSheet("QWidget#widget{background-color:  rgba(33,37,43,150); border-radius: 10px; border: 1px solid gray;}");
    ui->tab->setStyleSheet("QWidget#tab{background-color:  rgba(33,37,43,150); border-radius: 10px; border: 1px solid gray;}");
    ui->tab_2->setStyleSheet("QWidget#tab_2{background-color:  rgba(33,37,43,150); border-radius: 10px; border: 1px solid gray;}");
    ui->tab_3->setStyleSheet("QWidget#tab_3{background-color:  rgba(33,37,43,150); border-radius: 10px; border: 1px solid gray;}");
    ui->pushButton->setStyleSheet("QPushButton{background:  transparent; border-radius: 0px;}"
                                  "QPushButton:checked{background-color: rgb(1,128,215);}");
    ui->pushButton_2->setStyleSheet("QPushButton{background:  transparent; border-radius: 0px;}"
                                    "QPushButton:checked{background-color: rgb(1,128,215);}");
    ui->pushButton_3->setStyleSheet("QPushButton{background:  transparent; border-radius: 0px;}"
                                    "QPushButton:checked{background-color: rgb(1,128,215);}");

    ui->pushButton->setCheckable(true);
    ui->pushButton_2->setCheckable(true);
    ui->pushButton_3->setCheckable(true);


    //内容字体小点
    ui->label->setStyleSheet("font:18pt;");
    ui->label_3->setStyleSheet("font:18pt;");
    ui->label_5->setStyleSheet("font:18pt;");
    //隐藏标签
    ui->tabWidget->tabBar()->hide();
    //背景透明
    ui->tabWidget->setStyleSheet("QTabWidget:pane{border-top:0px solid #e8f3f9;background:  transparent; }");

//    connect(ui->pushButton, &QPushButton::clicked, [&](bool clicked){
//        ui->tabWidget->setCurrentIndex(0);
//        ui->pushButton_2->setChecked(false);
//        ui->pushButton_3->setChecked(false);
//    });
//    connect(ui->pushButton_2, &QPushButton::clicked, [&](bool clicked){
//        ui->tabWidget->setCurrentIndex(1);
//        ui->pushButton->setChecked(false);
//        ui->pushButton_3->setChecked(false);
//    });
//    connect(ui->pushButton_3, &QPushButton::clicked, [&](bool clicked){
//        ui->tabWidget->setCurrentIndex(2);
//        ui->pushButton_2->setChecked(false);
//        ui->pushButton->setChecked(false);
//    });

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(onButton2Clicked()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(onButton3Clicked()));

}

HelpWidget::~HelpWidget()
{
    delete ui;
}

void HelpWidget::onButtonClicked()
{
    ui->tabWidget->setCurrentIndex(0);
    ui->pushButton_2->setChecked(false);
    ui->pushButton_3->setChecked(false);
}

void HelpWidget::onButton2Clicked()
{
    ui->tabWidget->setCurrentIndex(1);
    ui->pushButton->setChecked(false);
    ui->pushButton_3->setChecked(false);
}

void HelpWidget::onButton3Clicked()
{
    ui->tabWidget->setCurrentIndex(2);
    ui->pushButton_2->setChecked(false);
    ui->pushButton->setChecked(false);
}
