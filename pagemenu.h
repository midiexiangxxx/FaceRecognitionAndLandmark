#ifndef PAGEMENU_H
#define PAGEMENU_H

#include <QWidget>

namespace Ui {
class PageMenu;
}

class PageMenu : public QWidget
{
    Q_OBJECT

public:
    explicit PageMenu(QWidget *parent = NULL);
    ~PageMenu();

signals:
    void changePage(PageMenu *menu, int index);

private slots:
    void onButtonClicked();
    void onButton2Clicked();
    void onButton3Clicked();
    void onButton4Clicked();
    void onButton5Clicked();
private:
    Ui::PageMenu *ui;
};

#endif // PAGEMENU_H
