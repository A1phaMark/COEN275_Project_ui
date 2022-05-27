#include "db.h"

DB* DB::instance = nullptr;

DB::DB(){}

QSqlQuery DB::read(QString qry)
{
    QSqlQuery query = QSqlQuery(instance->qdb);
    bool success = query.exec(qry);

//    if(success){

//    }

    return query;
}

bool DB::write(QString qry)
{
    QSqlQuery query = QSqlQuery(instance->qdb);
    return query.exec(qry);
}


void DB::connectToDB()
{
    instance->qdb = QSqlDatabase::addDatabase("QMYSQL");
    instance->qdb.setHostName("127.0.0.1");
    instance->qdb.setUserName("root");
    instance->qdb.setPassword("Coen@275");
    instance->qdb.setDatabaseName("project_management");

    if(instance->qdb.open()){
        qDebug() << "DB Connection OK";
    }
    else{
        qDebug() << "Fail to connect!";
    }
}


DB* DB::getInstance()
{
    if (instance == nullptr){
        instance = new DB();
        instance->connectToDB();
    }
    return instance;
}
