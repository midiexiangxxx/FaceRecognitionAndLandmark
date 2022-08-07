QT       += core gui multimediawidgets sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
#define nullptr NULL
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    customsqltablemodel.cpp \
    dataanalysis.cpp \
    dlib/all/source.cpp \
    faceinput.cpp \
    helpwidget.cpp \
    history.cpp \
    main.cpp \
    mainpage.cpp \
    mainwindow.cpp \
    mobilefacenet.cpp \
    modifyuserinfo.cpp \
    mtcnn.cpp \
    pagemenu.cpp \
    passwidget.cpp \
    sql.cpp \
    warningwidget.cpp \
    warningwidgetvt.cpp

HEADERS += \
    ExternValues.h \
    customsqltablemodel.h \
    dataanalysis.h \
    dlib/queue.h \
    faceinput.h \
    helpwidget.h \
    history.h \
    mainpage.h \
    mainwindow.h \
    mobilefacenet.h \
    modifyuserinfo.h \
    mtcnn.h \
    pagemenu.h \
    passwidget.h \
    sql.h \
    warningwidget.h \
    warningwidgetvt.h

FORMS += \
    dataanalysis.ui \
    faceinput.ui \
    helpwidget.ui \
    history.ui \
    mainpage.ui \
    mainwindow.ui \
    modifyuserinfo.ui \
    pagemenu.ui \
    passwidget.ui \
    warningwidget.ui \
    warningwidgetvt.ui



# 配置 openmp
QMAKE_CXXFLAGS += -fopenmp -mavx


LIBS += -fopenmp

LIBS += -lpthread -lm

#LIBS += -lX11
NCNN_DIR = ./ncnn
usrLocLib = $$PWD/opencv/lib
# 配置所用库so文件
LIBS += $${usrLocLib}/libopencv_highgui.so \
    $${usrLocLib}/libopencv_core.so \
    $${usrLocLib}/libopencv_imgproc.so \
    $${usrLocLib}/libopencv_imgcodecs.so \
    $${usrLocLib}/libopencv_video.so \
    $${usrLocLib}/libopencv_videoio.so \
    $${usrLocLib}/libopencv_calib3d.so \
    $${usrLocLib}/libopencv_features2d.so \
    $${usrLocLib}/libopencv_flann.so \
    $${usrLocLib}/libopencv_objdetect.so \
    $${usrLocLib}/libopencv_photo.so \
    $${usrLocLib}/libopencv_stitching.so \


LIBS += $$PWD/ncnn/my_build/install/lib/libncnn.a


INCLUDEPATH += $$PWD/opencv/include

INCLUDEPATH += $${NCNN_DIR}/my_build/install/include/ncnn \
               $${NCNN_DIR}/src

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES += \
    shape_predictor_68_face_landmarks.dat \
    ./dlib/
