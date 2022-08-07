#ifndef WARNINGWIDGETVT_H
#define WARNINGWIDGETVT_H

#include <QWidget>

namespace Ui {
class WarningWidgetVT;
}

class WarningWidgetVT : public QWidget
{
    Q_OBJECT

public:
    explicit WarningWidgetVT(QWidget *parent = nullptr);
    ~WarningWidgetVT();

private:
    Ui::WarningWidgetVT *ui;
};

#endif // WARNINGWIDGETVT_H
