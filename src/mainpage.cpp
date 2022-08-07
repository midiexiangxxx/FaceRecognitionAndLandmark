#include "mainpage.h"
#include "ui_mainpage.h"

#include <QPainter>
#include <QDebug>
#include <QRect>
#include <QGraphicsOpacityEffect>

#include <cmath>

#include "ExternValues.h"

#include <fstream>

#define X_count 80
int count__ = 0;
template <typename T>
cv::Mat plotGraph(std::vector<T>& val1, std::vector<T>& val2, std::vector<T>& val3, int YRange[2])
{
    int rows = 200;
    cv::Mat image = cv::Mat::zeros( rows, val1.size(), CV_8UC3 );
    image.setTo(0);
    for (int i = 0; i < (int)val1.size()-1; i++)
    {
        cv::line(image, cv::Point(i, rows - 1 - (val1[i])*100), cv::Point(i+1, rows - 1 - (val1[i+1])*100), cv::Scalar(255, 0, 0), 1);
        cv::line(image, cv::Point(i, rows - 1 - (val2[i])*100), cv::Point(i+1, rows - 1 - (val2[i+1])*100), cv::Scalar(0, 255, 0), 1);
        cv::line(image, cv::Point(i, rows - 1 - (val3[i])*100), cv::Point(i+1, rows - 1 - (val3[i+1])*100), cv::Scalar(0, 0, 255), 1);
    }

    return image;
}


void draw_polyline(cv::Mat &img, const dlib::full_object_detection& d, const int start, const int end, bool isClosed = false)
{
    std::vector <cv::Point> points;
    for (int i = start; i <= end; ++i)
    {
        points.push_back(cv::Point(d.part(i).x(), d.part(i).y()));
    }
    cv::polylines(img, points, isClosed, cv::Scalar(255, 0, 0), 2, 16);

}

void render_face(cv::Mat &img, const dlib::full_object_detection& d)
{
    DLIB_CASSERT
    (
        d.num_parts() == 68,
        "\n\t Invalid inputs were given to this function. "
        << "\n\t d.num_parts():  " << d.num_parts()
    );

    draw_polyline(img, d, 36, 41, true);    // Left eye
    draw_polyline(img, d, 42, 47, true);    // Right Eye
    draw_polyline(img, d, 48, 59, true);    // Outer lip
    draw_polyline(img, d, 60, 67, true);    // Inner lip

}


MainPage::MainPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainPage)
{
    ui->setupUi(this);
    initUI();
}

MainPage::~MainPage()
{
    delete ui;
}

void MainPage::initUI()
{
    qDebug()<<"init ui";
    QPalette pal(this->palette());
    pal.setColor(QPalette::Window, QColor(31,35,38, 24));
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    ui->widget_3->setStyleSheet("QWidget#widget_3{border-image: url(:/style/images/rect.png);}");
    ui->widget_2->setStyleSheet("QWidget#widget_4{border-image: url(:/style/images/rect.png);}");
    ui->widget_5->setStyleSheet("QWidget#widget_5{border-image: url(:/style/images/rect.png);}");
    ui->graphicsView->setStyleSheet("QWidget#widget_5{border-image: url(:/style/images/rect.png);}");

    ui->label->setStyleSheet("font:18pt;");
    ui->label_2->setStyleSheet("font:18pt;");

    //警告框使用
    // yawn
    warning = new WarningWidget(this);

    warning->setGeometry(1770,300,800,350);
    warning->setHidden(true);
    //sleepy
    warning_ = new WarningWidgetVT(this);
    warning_->setGeometry(1770,300,800,350);
    warning_->setHidden(true);

    //PASS frame using
    passing = new passwidget(this);
    passing->setGeometry(529, 320, 901, 307);
    passing->setHidden(true);
    ui->graphicsView->setScene(new QGraphicsScene(this));
    ui->graphicsView->scene()->addItem(&pixmap);

    ui->chartview->setScene(new QGraphicsScene(this));
    ui->chartview->scene()->addItem(&chartpixmap);

    QString dbpath = "/home/lbr/projects/GitProjects/0707/Qt_ncnn_opencv/QT_final/database/workers.db";
    db = new sql(dbpath);

    state = RECOGNIZE;
    save_idx += db->maxHistory();


}
std::vector<double> mouth_ratio;
std::vector<double> left_eye;
std::vector<double> right_eye;
void MainPage::on_pushButton_pressed()
{
    using namespace cv;
    if(video.isOpened()){
        ui->pushButton->setText("Open Camera");
        video.release();
        return;
    }

    if(!video.open(0)){
        QMessageBox::critical(this,"Camera Error",
            "Make sure you entered a correct camera index,"
            "<br>or that the camera is not being accessed by another program!");
        return;
    }
    ui->pushButton->setText("Close Camera");
    Mat frame,chart;

    //dlib
    const char *landmark_model = "/home/lbr/projects/GitProjects/0707/Qt_ncnn_opencv/QT_final/shape_predictor_68_face_landmarks.dat";
    dlib::shape_predictor pose_model;
    dlib::deserialize(landmark_model) >> pose_model;

    //初始化mtcnn & recognation
    const char *model_path = "/home/lbr/projects/GitProjects/0707/Qt_ncnn_opencv/QT_final/models";
    Recognize recognize(model_path);
    //sampleimg = cv::imread("/home/lbr/projects/GitProjects/0707/Qt_ncnn_opencv/QT_final/sample.jpg", CV_LOAD_IMAGE_COLOR);
    //recognize.start(sampleimg, samplefea);



    std::vector<dlib::rectangle> faces;

    while(video.isOpened())
    {
        video >> frame;

        if(!frame.empty())
        {
            MTCNN mtcnn(model_path);
            mtcnn.SetMinFace(40);

            ncnn::Mat ncnn_img = ncnn::Mat::from_pixels(frame.data, ncnn::Mat::PIXEL_BGR2RGB, frame.cols, frame.rows);
            std::vector<Bbox> finalBbox;
            mtcnn.detect(ncnn_img, finalBbox);

            const int num_box = finalBbox.size();
            std::vector<cv::Rect> bbox;
            bbox.resize(num_box);


            for(int i = 0; i < num_box; i++){
                cv::Rect r = Rect(finalBbox[0].x1, finalBbox[0].y1,  finalBbox[0].x2 - finalBbox[0].x1, finalBbox[0].y2 - finalBbox[0].y1);
                cv::Mat ROI(frame, r);
                cv::Mat croppedImage;
                std::vector<float> croppedfea;
                cv::Point org;

                dlib::rectangle R(
                                    (long)(finalBbox[0].x1),
                                    (long)(finalBbox[0].y1),
                                    (long)(finalBbox[0].x2),
                                    (long)(finalBbox[0].y2)
                );

                dlib::cv_image<dlib::bgr_pixel> dimg(frame);
//                std::vector<dlib::full_object_detection> shapes;
                // Landmark detection on full sized image
                dlib::full_object_detection shape = pose_model(dimg,R);
//                shapes.push_back(shape);
                render_face(frame, shape);

                //calculate eyes
                double left_ratio = (shape.part(39).x() - shape.part(36).x())/2.0/(shape.part(41).y() + shape.part(40).y() - shape.part(37).y() - shape.part(38).y()+0.1f);
                double right_ratio = (shape.part(45).x() - shape.part(42).x())/2.0/(shape.part(47).y() + shape.part(46).y() - shape.part(44).y() - shape.part(43).y()+0.1f);
                double mouth = (shape.part(66).y() + shape.part(57).y() - shape.part(62).y() - shape.part(51).y())/((float)(shape.part(54).x() - shape.part(48).x()));
                //std::cout << "left: " << left_ratio << "right: " << right_ratio << "mouth: " << mouth << std::endl;

                eye_blink.push_back(left_ratio+right_ratio-2.3);
                if(eye_blink.size()>2)
                    eye_blink.erase(eye_blink.begin());

                if(eye_blink.front() < 0 && eye_blink.back()>0 ){
                    num_blink++;
                }

                if(left_ratio>1&&right_ratio>1)
                {
                    close_eye++;
                }
                else
                {
                    close_eye = 0;
                }


                if(state == RECOGNIZE)
                    rectangle(frame, r, Scalar(0, 0, 255), 2, 8, 0);

                if( db->maxID() > 0 && state==RECOGNIZE ){

                    // Copy the data into new matrix
                    ROI.copyTo(croppedImage);

                    recognize.start(croppedImage, croppedfea);
                    double similar;
                    int id;
                    similar = db->findKindred(croppedfea,id);
                    QString text;
                    if(similar > 0.59){
                       text = QStringLiteral("ID: %1 similarity: %2 ").arg(id).arg(similar);
                    }
                    else{
                       text = QStringLiteral("       similarity: %2 ").arg(similar-0.2);
                    }
                    putText(frame,text.toStdString(),cv::Point(finalBbox[0].x1, finalBbox[0].y1),FONT_HERSHEY_COMPLEX,1,Scalar(0,0,255),4);
                }


                //chart
                mouth_ratio.push_back(mouth);
                left_eye.push_back(left_ratio);
                right_eye.push_back(right_ratio);
                if(mouth_ratio.size()>300){
                    mouth_ratio.erase(mouth_ratio.begin());
                    left_eye.erase(left_eye.begin());
                    right_eye.erase(right_eye.begin());
                }

                int range[2] = {0, 2};

                chart = plotGraph(mouth_ratio,left_eye,right_eye,range);

                if(state == DETECTION)
                {
                    if(mouth>1.63){
                        warning->setHidden(false);
                        ui->label_5->setText("Current VioLation:  Yawn");
                        count_warning_mouth = 12;
                        if(SAVE){
                            this->save_frame(ROI,save_idx,"yawning");
                            save_idx++;
                            SAVE = 0;
                            count__++;
                        }
                    }
                    else{
                        warning->setHidden(true);
                    }
                    if(close_eye>10)
                    {
                        warning_->setHidden(false);
                        ui->label_5->setText("Current VioLation: Sleep");
                        if(SAVE){
                            this->save_frame(ROI,save_idx,"closing eyes");
                            save_idx++;
                            SAVE = 0;
                            count__++;
                        }
                        close_eye = 0;
                        count_warning_eyes = 12;
                    }
                    if(count_warning_mouth-->0)
                    {
                        warning->setHidden(false);
                    }
                    else if(count_warning_eyes-->0){
                        warning_->setHidden(false);
                    }
                    else// if(count_warning<=0)
                    {
                        warning_->setHidden(true);
                        warning->setHidden(true);
                    }
                }
                if(count__ >= 7){
                    ui->label_4->setText("Driver Condition:  bad    ");
                }
                else if(count__ >= 3){
                    ui->label_4->setText("Driver Condition:  tired  ");
                }
                else{
                    ui->label_4->setText("Driver Condition:  fine   ");
                }
                int id;
                double similar = db->findKindred(croppedfea,id);
                if(state == RECOGNIZE && num_blink >= 2 &&similar >= 0.62){
                    passing->setHidden(false);
                    ui->label_3->setText("Legal Yes or No? yes  ");
                    count_passing = 12;
                    state = DETECTION;
                    num_blink = 0;
                }
                else{
                    passing->setHidden(true);
                }
                if(count_passing-->0){
                    passing->setHidden(false);
                }
                else{
                    passing->setHidden(true);
                }
                if(count_warning_mouth < 0 && count_warning_eyes < 0){
                    SAVE = 1;
                    count_warning_eyes = 0;
                    count_warning_mouth = 0;
                }
                noFace_count = 0;

            }
            if(num_box==0){
                noFace_count++;
                qDebug() << "noFace_count: " << noFace_count;
                if(noFace_count > 50 && state == DETECTION){
                    noFace_count = 0;
                    state = RECOGNIZE;
                    ui->label_3->setText("Legal Yes or No? no   ");
                    num_blink = 0;
                }
            }


            QImage qimg(frame.data,
                        frame.cols,
                        frame.rows,
                        frame.step,
                        QImage::Format_RGB888);
            pixmap.setPixmap( QPixmap::fromImage(qimg.rgbSwapped()) );
            ui->graphicsView->fitInView(&pixmap, Qt::KeepAspectRatio);

            QImage chartqimg(chart.data,
                             chart.cols,
                             chart.rows,
                             chart.step,
                             QImage::Format_RGB888);
            chartpixmap.setPixmap( QPixmap::fromImage(chartqimg.rgbSwapped()) );
            ui->chartview->fitInView(&chartpixmap, Qt::KeepAspectRatio);
        }
        qApp->processEvents();
    }

}


void MainPage::resizeEvent(QResizeEvent*)
{
    QRect rect;
//    rect = ui->widget_3->geometry();
//    ui->graphicsView->setGeometry(rect.x()-20,rect.y()-54,rect.width(),rect.height());
//    rect = ui->widget_2->geometry();
//    ui->chartview->setGeometry(rect.x()-5,rect.y()-10,rect.width(),rect.height());

}

void MainPage::save_frame(cv::Mat roi,int save_idx,QString misbehavior)
{

    string img_path = "/home/lbr/projects/GitProjects/0707/Qt_ncnn_opencv/QT_final/his_imgs/image_"+to_string(save_idx)+".jpg";
    if(!(roi.empty())){
       cv::imwrite(img_path,roi);
       QString date=QDateTime::currentDateTime().toString("yyyy MM dd hh mm");
       QString imgpath = QString::fromStdString(img_path);
       db->addHistory(save_idx,date,misbehavior,imgpath);

    }
}

