#include "faceinput.h"
#include "ui_faceinput.h"


FaceInput::FaceInput(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FaceInput)
{
    ui->setupUi(this);

    QPalette pal(this->palette());
    pal.setColor(QPalette::Window, QColor(31,35,38, 24));
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    ui->widget->setStyleSheet("QWidget#widget{background:  transparent; border-radius: 10px; border: 1px solid gray;}");
    ui->widget_2->setStyleSheet("QWidget#widget_2{border-image: url(:/style/images/rect.png);}");
//    ui->widget_3->setStyleSheet("QWidget#widget_3{border-image: url(:/style/images/rect.png);}");

    ui->graphicsView_faceinput->setScene(new QGraphicsScene(this));
    ui->graphicsView_faceinput->scene()->addItem(&pixmap);

    ui->label->setStyleSheet("font:18pt;");
//    ui->label_2->setStyleSheet("font:18pt;");

    //ui->horizontalSlider->setRange(0, 100);
    //警告框使用
    widget = new ModifyUserInfo(this);
    widget->setGeometry(702, 200, 514, 421);
//    widget->show();
    widget->setHidden(true);

    QString dbpath = "/home/lbr/projects/GitProjects/0707/Qt_ncnn_opencv/QT_final/database/workers.db";
    db = new sql(dbpath);

    QString NumofWorkers = QStringLiteral("%1  ").arg(db->maxID());
    ui->label_4->setText(NumofWorkers);
}

FaceInput::~FaceInput()
{
    delete ui;
}


void FaceInput::on_pushButton_pressed()
{
    using namespace cv;

    if(video.isOpened()){
        ui->pushButton->setText("打开摄像头");
        video.release();
        return;
    }

    if(!video.open(0)){
        QMessageBox::critical(this,"Camera Error",
            "Make sure you entered a correct camera index,"
            "<br>or that the camera is not being accessed by another program!");
        return;
    }
    ui->pushButton->setText("关闭摄像头");


    Mat frame;

    const char *model_path = "/home/lbr/projects/GitProjects/0707/Qt_ncnn_opencv/QT_final/models";
    Recognize recognize(model_path);
    std::cout<<"models right";
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

                rectangle(frame, r, Scalar(0, 0, 255), 2, 8, 0);

                // Copy the data into new matrix
                ROI.copyTo(croppedImage);

                //add
                if(isSample && db->isConnected){
                    isSample = false;
                    index++;
                    QString name = "test";
                    int age = 18;
                    recognize.start(croppedImage, croppedfea);
                    db->addPerson(index,name,age,croppedfea);
                    QString NumofWorkers = QStringLiteral("%1  ").arg(db->maxID());
                    ui->label_4->setText(NumofWorkers);
                }

            }

            if(num_box<=0){
                ui->pushButton_2->setDisabled(true);
                ui->pushButton_2->setText("未检测到人脸");
            }
            else{
                ui->pushButton_2->setDisabled(false);
                ui->pushButton_2->setText("采集");

            }
            // Resize image for face detection


//            qDebug("test");
            QImage qimg(frame.data,
                        frame.cols,
                        frame.rows,
                        frame.step,
                        QImage::Format_RGB888);
            pixmap.setPixmap( QPixmap::fromImage(qimg.rgbSwapped()) );
            ui->graphicsView_faceinput->fitInView(&pixmap, Qt::KeepAspectRatio);
        }
        qApp->processEvents();

    }
}


void FaceInput::on_pushButton_2_clicked()
{
    isSample = true;

}


void FaceInput::on_pushButton_3_clicked()
{
    //reset database
    QSqlQuery query;
    if( !query.exec( "DELETE FROM WORKERS" ))
        qDebug() << "Error DELETE FROM WORKERS\n" << query.lastError();
    QString NumofWorkers = QStringLiteral("%1  ").arg(db->maxID());
    ui->label_4->setText(NumofWorkers);
}

