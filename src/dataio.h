#ifndef DATAIO_H
#define DATAIO_H

#include <fstream>
#include <iostream>
#include <vector>
#include <string.h>
#include <QDataStream>
#include <QFile>


using namespace std;
#define FEATURE_SIZE 128

typedef struct worker
{
    qint32 id;
    QString name;
    qint32 age;
    float feature[FEATURE_SIZE];
}worker_t;




#endif // DATAIO_H
