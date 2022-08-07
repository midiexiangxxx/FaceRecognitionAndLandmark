#ifndef PASSWIDGET_H
#define PASSWIDGET_H

#include <QWidget>

namespace Ui {
class passwidget;
}

class passwidget : public QWidget
{
    Q_OBJECT

public:
    explicit passwidget(QWidget *parent = nullptr);
    ~passwidget();

private:
    Ui::passwidget *ui;
};

#endif // PASSWIDGET_H
