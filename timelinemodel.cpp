#include "timelinemodel.h"

timelineModel::timelineModel(){}

vector<timelineObject> timelineModel::fetchObjectsBy(projectObject project)
{
    objects = vector<timelineObject>();
    QString qry_s =  QString("SELECT * FROM project_management.timeline WHERE project_management.timeline.project_id = %1;").arg(project.projectID);
    QSqlQuery qry =  DB::getInstance()->read(qry_s);
    while(qry.next())
    {
        timelineObject newObject = timelineObject();
        newObject.timelineID = qry.value(0).toInt();
        int nameFieldNo = qry.record().indexOf("name");
        newObject.name = qry.value(nameFieldNo).toString();
        int statusNo = qry.record().indexOf("status");
        newObject.status = qry.value(statusNo).toString();
        int createDateNo = qry.record().indexOf("start_date");
        newObject.startDate = qry.value(createDateNo).toDateTime();
        int updateDateNo = qry.record().indexOf("end_date");
        newObject.endDate = qry.value(updateDateNo).toDateTime();
        objects.push_back(newObject);
    }
    return objects;
}

bool timelineModel::addTimeline(projectObject project, QString content)
{
    QString qry_s =  QString("INSERT INTO `project_management`.`timeline` (`name`, `project_id`) VALUES ('%1', %2);").arg(content, QString::number(project.projectID));
    return DB::getInstance()->write(qry_s);
}

bool timelineModel::removeTimeline(timelineObject timeline)
{
    QString qry_s =  QString("DELETE FROM `project_management`.`timeline` WHERE (`id` = %1);").arg(timeline.timelineID);
    return DB::getInstance()->write(qry_s);
}
