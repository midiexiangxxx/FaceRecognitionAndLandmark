#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pagemenu.h"
#include <QTabWidget>
#include <QDebug>
#include <QTabBar>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //隐藏标题栏
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->resize(1920, 1080);
    m_menu_show = false;
    //隐藏标签
    ui->tabWidget->tabBar()->hide();
    //关闭按钮
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(onButton2Clicked()));
//    connect(ui->pushButton_2, &QPushButton::clicked, [&]{
//        QApplication* app;
//        app->exit(0);
//    });
//    //最小化
//    connect(ui->pushButton_3, &QPushButton::clicked, [&](bool clicked){
//        this->setWindowState(Qt::WindowMinimized);
//    });
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(onButton3Clicked()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(onButton4Clicked()));

    this->setStyleSheet("QMainWindow#MainWindow{border-image: url(:/style/images/BackGround.jpg);}");
    ui->topWidget->setStyleSheet("QWidget#topWidget{border-image: url(:/style/images/top.png);}");
    ui->tabWidget->setStyleSheet("QTabWidget:pane{border-top:0px solid #e8f3f9;background:  transparent; }");

    QPalette pal2(ui->centralwidget->palette());
    pal2.setColor(QPalette::Window, QColor(31,35,38, 24));
    ui->centralwidget->setAutoFillBackground(true);
    ui->centralwidget->setPalette(pal2);
    //菜单按钮是透明的
    QPushButton *menu = new QPushButton(this);
    QIcon menuIcon = QIcon(":/icon/images/menu.png");

    menu->setIcon(menuIcon);
    menu->setText("菜单");
    menu->setStyleSheet("QPushButton{background:  transparent;font:12pt;}"
                        "QPushButton:hover{background-color:rgb(1,128,215);}");
    menu->setGeometry(1504, 35, 75, 30);
    connect(menu, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
//    connect(menu, &QPushButton::clicked, [&](bool clicked){
//        this->setWindowModality(Qt::ApplicationModal);
//        PageMenu *pagemen = new PageMenu(this);
//        pagemen->setGeometry(702, 330, 514, 471);
//        pagemen->show();
//        connect(pagemen, &PageMenu::changePage, [=](int index){
//            //点击菜单切换页面
//            ui->tabWidget->setCurrentIndex(index);
//            QString title = "疲劳驾驶预警系统";
//            switch (index) {
//            case 2:
//                title = "历史记录";
//                break;
//            case 3:
//                title = "数据分析";
//                break;
//            case 4:
//                title = "帮助文档";
//                break;
//            default:
//                break;
//            }
//            ui->label->setText(title);
//            delete pagemen;
//        });

//    });

    ui->pushButton_2->setStyleSheet("background:  transparent;");
    ui->pushButton_3->setStyleSheet("background:  transparent;");
    ui->pushButton_4->setStyleSheet("background:  transparent;");
    //中间的标题样式
    QFont font  = ui->label->font();
    font.setPointSize(21);
    font.setWeight(QFont::Weight::Thin);
    ui->label->setFont(font);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onButtonClicked()
{
    this->setWindowModality(Qt::ApplicationModal);
    m_menu = new PageMenu(this);
    m_menu->setGeometry(702, 330, 514, 471);
    m_menu->show();
    m_menu_show = true;
    connect(m_menu, SIGNAL(changePage(PageMenu*, int)), this, SLOT(onChangePage(PageMenu*,int)));
}

void MainWindow::onButton2Clicked()
{
    QApplication* app;
    app->exit(0);
}

void MainWindow::onButton3Clicked()
{
    this->setWindowState(Qt::WindowMinimized);
}

void MainWindow::onButton4Clicked()
{
     this->setWindowState(Qt::WindowMaximized);
}

void MainWindow::onChangePage(PageMenu *menu, int index)
{
    qDebug()<<index;
    //点击菜单切换页面
    ui->tabWidget->setCurrentIndex(index);
    QString title = "疲劳驾驶预警系统";
    switch (index) {
    case 2:
        title = "历史记录";
        break;
    case 3:
        title = "数据分析";
        break;
    case 4:
        title = "帮助文档";
        break;
    default:
        break;
    }
    ui->label->setText(title);
    delete menu;
    menu = NULL;
    m_menu_show = false;
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(m_menu != NULL && m_menu_show)
    {
        delete m_menu;
        m_menu = NULL;
        m_menu_show = false;
    }
}

