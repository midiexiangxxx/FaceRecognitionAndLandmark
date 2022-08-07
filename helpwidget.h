#ifndef HELPWIDGET_H
#define HELPWIDGET_H

#include <QWidget>

namespace Ui {
class HelpWidget;
}

class HelpWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HelpWidget(QWidget *parent = NULL);
    ~HelpWidget();

private slots:
    void onButtonClicked();
    void onButton2Clicked();
    void onButton3Clicked();

private:
    Ui::HelpWidget *ui;
};

#endif // HELPWIDGET_H
