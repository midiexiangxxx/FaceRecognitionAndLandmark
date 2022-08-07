#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QPushbutton>
#include "pagemenu.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = NULL);
    ~MainWindow();

private slots:
    void onButtonClicked();
    void onButton2Clicked();
    void onButton3Clicked();
    void onButton4Clicked();
    void onChangePage(PageMenu *menu, int index);
protected:
    void mouseReleaseEvent(QMouseEvent *event);
private:
    Ui::MainWindow *ui;
    PageMenu *m_menu;
    bool m_menu_show;
};
#endif // MAINWINDOW_H
