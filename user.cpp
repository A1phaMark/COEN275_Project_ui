#include "user.h"
user* user::instance = nullptr;

user::user(){}

bool user::initUserWithAuth(QString userName, QString password)
{
    if(instance->login(userName, password)){
        QString qry_s = QString("SELECT * FROM project_management.position WHERE user_id = %1;").arg(this->userID);
        QSqlQuery qry =  DB::getInstance()->read(qry_s);

        if(qry.next())
        {
            instance->posID = qry.value(0).toInt();
            int nameFieldNo = qry.record().indexOf("name");
            instance->position = qry.value(nameFieldNo).toString();
            return true;
        }

        return true;
    }

    return false;
}

user* user::getInstance()
{
    if (instance == nullptr){
        instance = new user();
    }
    return instance;
}
