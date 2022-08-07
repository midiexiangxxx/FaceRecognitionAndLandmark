#include "dataanalysis.h"
#include "ui_dataanalysis.h"
#include <QTextCharFormat>
#include <QCalendarWidget>
#include "ExternValues.h"
#include "opencv2/opencv.hpp"
#include <unistd.h>
#include <QDebug>
int safe_count = 0,mid_count = 0,large_count = 0;
template <typename T>
cv::Mat plotGraph(std::vector<T>& val1, std::vector<T>& val2, std::vector<T>& val3)
{
    int rows = 200;
    cv::Mat image = cv::Mat::zeros( rows, val1.size(), CV_8UC3 );
    image.setTo(0);
    for (int i = 0; i < (int)val1.size()-1; i++)
    {
          cv::line(image, cv::Point(i, rows - 1 - (val1[i]+val2[i]+val3[i])*33.33),
                   cv::Point(i+1, rows - 1 - (val3[i+1]+val1[i+1]+val2[i+1])*33.33), cv::Scalar(0, 0, 255), 1);
    }
    return image;
}


DataAnalysis::DataAnalysis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataAnalysis)
{
    ui->setupUi(this);
    ui->widget_3->setStyleSheet("QWidget#widget_3{background-color:  rgba(33,37,43,150); border-radius: 10px; border: 1px solid gray;}");
    ui->widget_4->setStyleSheet("QWidget#widget_4{background-color:  rgba(33,37,43,150); border-radius: 10px; border: 1px solid gray;}");
    //日历周末颜色

    ui->label_3->setStyleSheet("font: normal bold 20px ;");
    ui->label_2->setStyleSheet("font: normal bold 20px ;");
    ui->chartView->setScene(new QGraphicsScene(this));
    ui->chartView->scene()->addItem(&chartpixmap);
    timer.setInterval(10);
    connect(&timer,SIGNAL(timeout()),this,SLOT(plot()));
    timer.start();
}

DataAnalysis::~DataAnalysis()
{
    delete ui;
}

void DataAnalysis::plot()
{
    //qDebug()<<"qdebug"<<endl;
        cv::Mat chart;
        chart = plotGraph(mouth_ratio,left_eye,right_eye);
        QImage chartqimg(chart.data,
                      chart.cols,
                      chart.rows,
                      chart.step,
                      QImage::Format_RGB888);
        chartpixmap.setPixmap( QPixmap::fromImage(chartqimg.rgbSwapped()) );
        ui->chartView->fitInView(&chartpixmap, Qt::KeepAspectRatio);
}



