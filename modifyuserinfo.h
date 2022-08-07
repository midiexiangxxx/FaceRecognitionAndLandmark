#ifndef MODIFYUSERINFO_H
#define MODIFYUSERINFO_H

#include <QWidget>

namespace Ui {
class ModifyUserInfo;
}

class ModifyUserInfo : public QWidget
{
    Q_OBJECT

public:
    explicit ModifyUserInfo(QWidget *parent = NULL);
    ~ModifyUserInfo();

private:
    Ui::ModifyUserInfo *ui;
};

#endif // MODIFYUSERINFO_H
