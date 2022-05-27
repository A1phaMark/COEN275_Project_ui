#ifndef DB_H
#define DB_H

#include <QtSql>
#include <QSqlDatabase>

class DB
{
    private :
            DB();
            DB(const DB &);
           ~DB();

            static DB* instance;
            QSqlDatabase qdb;
    public:
            static DB* getInstance();
            void connectToDB();
            QSqlQuery read(QString qry);
            bool write(QString qry);
};

#endif // DB_H
