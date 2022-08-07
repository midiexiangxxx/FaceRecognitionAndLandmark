#ifndef SQL_H
#define SQL_H


#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QIODevice>
#include <QDebug>
#include <QVariant>


#define FEATURE_SIZE 512


class sql
{
public:
    bool isConnected = false;

    sql(const QString &DatabaseName);
    bool addPerson(int &id,QString& name,int &age,std::vector<float> &feature);
    void addHistory(int id,QString date,QString misbehavior,QString imagePath);
    void queryFeaturetoMAP();
    double findKindred(std::vector<float> &feature,int &id);
    int maxID();
    int maxHistory();


private:
    QSqlDatabase database;
    QSqlQuery sql_query;

    std::vector<std::array<float, FEATURE_SIZE>> featureMap;
};

#endif // SQL_H
