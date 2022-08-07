#ifndef DATAANALYSIS_H
#define DATAANALYSIS_H

#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QTimer>
namespace Ui {
class DataAnalysis;
}

class DataAnalysis : public QWidget
{
    Q_OBJECT

public:
    explicit DataAnalysis(QWidget *parent = NULL);
    ~DataAnalysis();

private:
    Ui::DataAnalysis *ui;
    QGraphicsPixmapItem chartpixmap;
    QTimer timer;

public slots:
    void plot();
};

#endif // DATAANALYSIS_H
