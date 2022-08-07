#include "pagemenu.h"
#include "ui_pagemenu.h"

PageMenu::PageMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageMenu)
{
    ui->setupUi(this);
    QPalette pal(this->palette());
    pal.setColor(QPalette::Window, QColor(31,35,38, 24));
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    ui->widget->setStyleSheet("QWidget#widget{border-image: url(:/style/images/menu_rect.png);}");

//    connect(ui->pushButton, &QPushButton::clicked, [&]{emit changePage(0);});
//    connect(ui->pushButton_2, &QPushButton::clicked, [&]{emit changePage(1);});
//    connect(ui->pushButton_3, &QPushButton::clicked, [&]{emit changePage(2);});
//    connect(ui->pushButton_4, &QPushButton::clicked, [&]{emit changePage(3);});
//    connect(ui->pushButton_5, &QPushButton::clicked, [&]{emit changePage(4);});

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(onButton2Clicked()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(onButton3Clicked()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(onButton4Clicked()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(onButton5Clicked()));

    ui->pushButton->setStyleSheet("QPushButton{background-color:rgb(31,35,38);border: 1px solid #A0A0A0;}"
                                  "QPushButton:hover{background-color:rgb(1,128,215);}");
    ui->pushButton_2->setStyleSheet("QPushButton{background-color:rgb(31,35,38);border: 1px solid #A0A0A0;}"
                                    "QPushButton:hover{background-color:rgb(1,128,215);}");
    ui->pushButton_3->setStyleSheet("QPushButton{background-color:rgb(31,35,38);border: 1px solid #A0A0A0;}"
                                    "QPushButton:hover{background-color:rgb(1,128,215);}");
    ui->pushButton_4->setStyleSheet("QPushButton{background-color:rgb(31,35,38);border: 1px solid #A0A0A0;}"
                                    "QPushButton:hover{background-color:rgb(1,128,215);}");
    ui->pushButton_5->setStyleSheet("QPushButton{background-color:rgb(31,35,38);border: 1px solid #A0A0A0;}"
                                    "QPushButton:hover{background-color:rgb(1,128,215);}");


}

PageMenu::~PageMenu()
{
    delete ui;
}

void PageMenu::onButtonClicked()
{
    emit changePage(this, 0);
}

void PageMenu::onButton2Clicked()
{
    emit changePage(this, 1);
}

void PageMenu::onButton3Clicked()
{
    emit changePage(this, 2);
}

void PageMenu::onButton4Clicked()
{
    emit changePage(this, 3);
}

void PageMenu::onButton5Clicked()
{
    emit changePage(this, 4);
}
