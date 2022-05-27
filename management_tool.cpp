#include "management_tool.h"
#include "ui_management_tool.h"
#include <iostream>
#include <QString>
#include <QDateTime>
#include <QList>
#include <unistd.h>
#include <QListWidget>
#include <QIcon>
#include <QMessageBox>
using namespace std;

int cur_project = 0, cur_new_task = 0, cur_progress_task = 0, cur_completed_task = 0, cur_task_status = 0;

management_tool::management_tool(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::management_tool)
{
    ui->setupUi(this);
    ui->warning_4->setVisible(false);
}

management_tool::~management_tool()
{
    delete ui;
}

//check if input date has correct format
bool management_tool::checkDateFormat(std::string date){
    if (date.size() != 10 || date[2] != '/' || date[5] != '/'){
        return false;
    }
    std::string month = date.substr(0, 2);
    std::string day = date.substr(3, 5);
    std::string year = date.substr(6, 10);
    //check month
    if (!isdigit(month[0]) || !isdigit(month[1])){
        return false;
    }
    if ( stoi(month) < 1 || stoi(month) > 12){
        return false;
    }
    //check day
    if (!isdigit(day[0]) || !isdigit(day[1])){
        return false;
    }
    if ( stoi(day) < 1 || stoi(day) > 31){
        return false;
    }
    //check year
    if (!isdigit(year[0]) || !isdigit(year[1]) || !isdigit(year[2]) || !isdigit(year[3])){
        return false;
    }

    return true;

}

void management_tool::refreshTasks(){
    this->newTasks = taskModel().fetchObjectsBy(this->projects[cur_project], "New");
    this->progressTasks = taskModel().fetchObjectsBy(this->projects[cur_project], "In Progress");
    this->completedTasks = taskModel().fetchObjectsBy(this->projects[cur_project], "Completed");
}


// start with all set page functions ---------------------------------------------------------------------------------------------
//set to login page
void management_tool::setLoginPage(){
    ui->stackedWidget->setCurrentIndex(0);
    ui->user_4->clear();
    ui->password_4->clear();
    ui->password_4->setEchoMode(QLineEdit::Password);
}


//set up main page
void management_tool::setMainPage(){
    //clear widgets
    ui->projectList_2->clear();
    //clear variable
    this->projects.clear();
    //set welcome label text
    ui->welcomeLabel->setText("Welcome, "  + this->usr->position + ":"+ this->usr->userName);

    //fetch user name and project list from MySQL db


    //set up project list
    this->projects = projectModel().fetchAllObjects();
    ui->projectList_2->setColumnCount(3);
    QStringList label;
    label<<"Project Name"<<"Start Date"<<"End Date";
    ui->projectList_2->setHeaderLabels(label);

    for (auto item = projects.begin(); item != projects.end(); item++)
    {
        projectObject project = *item;
        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, project.name);
        if(project.status == "New"){
            child->setIcon(0, QIcon(":/icon/new.png"));
        }
        else if(project.status == "In Progress"){
            child->setIcon(0, QIcon(":/icon/in_progress.png"));
        }
        else if(project.status == "Completed"){
            child->setIcon(0, QIcon(":/icon/completed.png"));
        }
        else{
            child->setIcon(0, QIcon(":/icon/closed.png"));
        }
        child->setText(1, project.createDate.toString("yyyy-MM-dd"));
        child->setText(2, project.updateDate.toString("yyyy-MM-dd"));
        ui->projectList_2->addTopLevelItem(child);
    }
    //chech user role and decide whether to show participants button
}

//set up project page
void management_tool::setProjectPage(){

    projectObject project = this->projects[cur_project];
    ui->projectName->setText(project.name);
    //clear widgets
    ui->taskList->clear();
    ui->bugList->clear();
    //set place holder
    ui->bugTitle->clear();
    ui->bugDescription->clear();
    ui->bugTitle->setPlaceholderText("Bug title");
    ui->bugDescription->setPlaceholderText("Bug description");

    //get and set up project status. Index 0 = in progress, index 1 = completed
    if(project.status == "New"){
        ui->projectStatusBox->setCurrentIndex(0);
    }
    else if(project.status == "In Progress"){
        ui->projectStatusBox->setCurrentIndex(1);
    }
    else if(project.status == "Completed"){
        ui->projectStatusBox->setCurrentIndex(2);
    }
    else{
        ui->projectStatusBox->setCurrentIndex(3);
    }

    //get task list
    QStringList label;
    ui->taskList->setColumnCount(5);
    label<<"Task Name"<<"Status"<<"Start Date"<<"End Date"<<"Worker";
    ui->taskList->setHeaderLabels(label);
    refreshTasks();

    //get new task
    QTreeWidgetItem *root1 = new QTreeWidgetItem(ui->taskList);
    root1->setText(0, "New");
    ui->taskList->addTopLevelItem(root1);
    //retrieve data from sql db
    for (auto item = this->newTasks.begin(); item != this->newTasks.end(); item++)
    {
        taskObject task = *item;
        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, task.name);
        child->setText(1, task.status);
        child->setText(2, task.createDate.toString("yyyy-MM-dd"));
        child->setText(3, task.updateDate.toString("yyyy-MM-dd"));
        child->setText(4, task.owner);
        root1->addChild(child);
    }

    //get in progress task
    QTreeWidgetItem *root2 = new QTreeWidgetItem(ui->taskList);
    root2->setText(0, "In Progress");
    ui->taskList->addTopLevelItem(root2);
    //retrieve data from sql db
    for (auto item = this->progressTasks.begin(); item != this->progressTasks.end(); item++)
    {
        taskObject task = *item;
        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, task.name);
        child->setText(1, task.status);
        child->setText(2, task.createDate.toString("yyyy-MM-dd"));
        child->setText(3, task.updateDate.toString("yyyy-MM-dd"));
        child->setText(4, task.owner);
        root2->addChild(child);
    }

    //get completed tasks
    QTreeWidgetItem *root3= new QTreeWidgetItem(ui->taskList);
    root3->setText(0, "Completed");
    ui->taskList->addTopLevelItem(root3);
    for (auto item = this->completedTasks.begin(); item != this->completedTasks .end(); item++)
    {
        taskObject task = *item;
        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, task.name);
        child->setText(1, task.status);
        child->setText(2, task.createDate.toString("yyyy-MM-dd"));
        child->setText(3, task.updateDate.toString("yyyy-MM-dd"));
        child->setText(4, task.owner);
        root3->addChild(child);
    }

    //get bug list
    this->bugs = bugModel().fetchObjectsBy(project);
    for (auto item = this->bugs.begin(); item != this->bugs.end(); item++){
        bugObject bug = *item;
        ui->bugList->addItem(bug.name);
    }
    //check user's role
}



//set up create new project page
void management_tool::setNewProjectPage(){
    //clear all widgets
    ui->employeeList->clear();
    ui->projectTitle->clear();
    ui->projectDescription->clear();
    ui->projectDate->clear();
    //hide all warning message
    ui->projectTitleWarning->setVisible(false);
    ui->dateFormatWarning->setVisible(false);
    ui->emptyDescriptionWarning->setVisible(false);
    //set up employee list
    this->newParticipants = userModel().fetchAllObjects();
    for (auto new_item = this->newParticipants.begin(); new_item != this->newParticipants.end(); new_item++)
    {
        user participant = *new_item;
        QListWidgetItem *item = new QListWidgetItem;
        item->setText(participant.userName);
        item->setCheckState(Qt::Unchecked);
        ui->employeeList->addItem(item);
    }
}


//set up change participants page
void management_tool::setParticipantPage(){
    this->curParticipants = participantModel().fetchObjectsBy(this->projects[cur_project]);
    //clear widgets
    ui->addParticipants->clear();
    ui->currentParticipants->clear();
    //retrieve participant lists and new participants list from MySQL db


    //set up current participants list
    for (auto new_item = this->curParticipants.begin(); new_item != this->curParticipants.end(); new_item++)
    {
        participantObject participant = *new_item;
        QListWidgetItem *item = new QListWidgetItem;
        item->setText(participant.userName);
        item->setCheckState(Qt::Unchecked);
        ui->currentParticipants->addItem(item);
    }

    vector<user>allUsers = userModel().fetchAllObjects();
    this->newParticipants = vector<user>();

    //set up new participants list
    for (user participant: allUsers){
        bool added = false;
        for(participantObject addedParticipant: this->curParticipants){
            if(addedParticipant.posID == participant.posID){
                added = true;
            }
        }

        qDebug()<<"All User" << participant.userName << " " << participant.posID;

        if(!added){
            qDebug()<<participant.userName;
            this->newParticipants.push_back(participant);
            QListWidgetItem *item = new QListWidgetItem;
            item->setText(participant.userName);
            item->setCheckState(Qt::Unchecked);
            ui->addParticipants->addItem(item);
        }
    }
}

taskObject management_tool::getTask(){
    taskObject task;
    if(cur_task_status == 0){
        task = this->newTasks[cur_new_task];
    }
    else if (cur_task_status == 1){
        task = this->progressTasks[cur_progress_task];
    }
    else{
        task = this->completedTasks[cur_completed_task];
    }
    return task;
}

//set up task page
void management_tool::setTaskPage(){
    //clear widget
    ui->commentInput->clear();
    ui->commentInput->setPlaceholderText("Write a comment...");
    if (ui->scrollAreaWidgetContents->layout() != NULL){
        QLayoutItem *item;
        while(item = ui->scrollAreaWidgetContents->layout()->takeAt(0)){
            delete item;
        }
    }
    //set task title label
    refreshTasks();
    taskObject task = getTask();

    ui->taskLabel->setText(task.name);
    ui->taskDescription->setText(task.description);
    ui->workerLabel->setText(task.owner);
    //check if the user is the worker


    //if is worker, hide assign_to_me button, show status change box
    if(this->usr->position == "manager"){
        ui->reassignButton->setVisible(false);
        ui->taskStatusLabel->setVisible(true);
        ui->taskStatusBox->setVisible(true);
        //get task status and change status box
        ui->taskStatusBox->setCurrentIndex(0);
    }
    //if not worker, show assign_to_me button, hide status change box
    else{
        ui->reassignButton->setVisible(true);
        ui->taskStatusLabel->setVisible(false);
        ui->taskStatusBox->setVisible(false);
    }

    if(task.status == "New"){
        ui->taskStatusBox->setCurrentIndex(0);
    }
    else if(task.status == "In Progress"){
        ui->taskStatusBox->setCurrentIndex(1);
    }
    else{
        ui->taskStatusBox->setCurrentIndex(2);
    }

    //set comment section
    vector<commentObject> comments = commentModel().fetchObjectsBy(task);
    for (auto item = comments.begin(); item != comments.end(); item++)
    {
        commentObject comment = *item;
        QTextBrowser* text = new QTextBrowser();
        text->setText(comment.content);
        text->setStyleSheet("background-color: rgb(255, 255, 255);");
        ui->scrollAreaWidgetContents->layout()->addWidget(text);

    }
    //ui->scrollAreaWidgetContents->setLayout(layout);
}


//set up new task page
void management_tool::setNewTaskPage(){
    //clear widget
    ui->employeeList_2->clear();
    ui->newTaskTitle->clear();
    ui->newTaskDescription->clear();
    ui->newTaskDate->clear();
    //hide all warning messages
    ui->taskDateWarning->setVisible(false);
    ui->taskDescriptionWarning->setVisible(false);
    ui->taskTitleWarning->setVisible(false);
    ui->taskParticipantWarning->setVisible(false);
    //get employee list for this project from sql db




    //set up employee list widget
    this->users = userModel().fetchObjectsBy("employee");
    for (auto new_item = this->users.begin(); new_item != this->users.end(); new_item++)
    {
        user user = *new_item;
        QListWidgetItem *item = new QListWidgetItem;
        item->setText(user.userName);
        ui->employeeList_2->addItem(item);

    }
}



//---------------------------------------------------------------------------------------------------------------------------------

void management_tool::on_login_2_clicked()
{
    QString uid = ui->user_4->text();
    QString pwd = ui->password_4->text();
       //check credential

    this->usr = user::getInstance();
    if(this->usr->initUserWithAuth(uid, pwd)){
        //if right credential
        ui->warning_4->setVisible(false);
        setMainPage();
        //check user role
        //if user is employee, disable certain features by setting a few buttons invisible
        if (this->usr->position == "employee"){
            ui->createNew->setVisible(false);
            ui->deleteProject->setVisible(false);
            ui->viewParticipants->setVisible(false);
            ui->deleteBug->setVisible(false);
            ui->deleteTaskButton->setVisible(false);
            ui->newTaskButton->setVisible(false);
            ui->projectStatusBox->setVisible(false);
            ui->projectStatusLabel->setVisible(false);
        }
        ui->stackedWidget->setCurrentIndex(1);
    }
    else{
        //if wrong credential, show warning message
        ui->warning_4->setVisible(true);
    }
}


void management_tool::on_logout_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void management_tool::on_viewDetail_clicked()
{
    if (ui->projectList_2->selectedItems().size()!=0){
        cur_project = ui->projectList_2->currentIndex().row();
        //set up project page
        setProjectPage();
        //go to project page
        ui->stackedWidget->setCurrentIndex(2);
    }
}


void management_tool::on_backToMain_clicked()
{
    setMainPage();
    ui->stackedWidget->setCurrentIndex(1);
}


void management_tool::on_cancelNewProject_clicked()
{
    setMainPage();
    ui->stackedWidget->setCurrentIndex(1);
}


void management_tool::on_confirmNewProject_clicked()
{
    //hide all warning message at the beginning
    ui->projectTitleWarning->setVisible(false);
    ui->dateFormatWarning->setVisible(false);
    ui->emptyDescriptionWarning->setVisible(false);
    //get input info
    QString title = ui->projectTitle->text();
    QString description = ui->projectDescription->toPlainText();
    QString finishDate_str = ui->projectDate->text();
    std::string std_finishDate = ui->projectDate->text().toStdString();

    //check if project title is available
    if(title.size() == 0){
        ui->projectTitleWarning->setVisible(true);
    }


    //check date format
    else if (!checkDateFormat(std_finishDate)){
        ui->dateFormatWarning->setVisible(true);
    }
    //check if description is empty
    else if (description.size() == 0){
        ui->emptyDescriptionWarning->setVisible(true);
    }

    else{
        //update MySQL db
        QDateTime finishDate = QDateTime::fromString(finishDate_str, "MM/dd/yyyy");
        QString formattedDate = finishDate.toString("yyyy-MM-dd");
        projectModel().addProject(title, description, formattedDate);
        this->projects = projectModel().fetchAllObjects();
        projectObject lastProject = this->projects.back();
        int i = 0;
        for(user newParticipant: this->newParticipants)
        {
            if (ui->employeeList->item(i)->checkState() == Qt::Checked){
                 participantModel().addParticipant(newParticipant, lastProject);
            }
            i++;
        }


        //go back to main page
        QMessageBox::information(this, "Completed", "New project created");
        setMainPage();
        ui->stackedWidget->setCurrentIndex(1);
    }
}


void management_tool::on_createNew_clicked()
{
    setNewProjectPage();
    ui->stackedWidget->setCurrentIndex(3);
}


void management_tool::on_backToMain_2_clicked()
{
    setMainPage();
    ui->stackedWidget->setCurrentIndex(1);
}


void management_tool::on_viewParticipants_clicked()
{
    if (ui->projectList_2->selectedItems().size()!=0){
        cur_project = ui->projectList_2->currentIndex().row();
        setParticipantPage();
        ui->stackedWidget->setCurrentIndex(4);
    }
}


void management_tool::on_addParticipantsButton_clicked()
{
    //get added employees list
    //update MySQL db
    int i = 0;
    for(user participant: this->newParticipants){
        if (ui->addParticipants->item(i)->checkState() == Qt::Checked){
             participantModel().addParticipant(participant, this->projects[cur_project]);
        }

        i++;
    }

    //update current page
    setParticipantPage();
    this->repaint();

}


void management_tool::on_removeParticipants_clicked()
{
    //get selected employees list
    //update MySQL db
    int i = 0;
    for(participantObject participant: this->curParticipants){
        if (ui->currentParticipants->item(i)->checkState() == Qt::Checked){
             participantModel().removeParticipant(participant);
        }

        i++;
    }


    //update current page
    setParticipantPage();
    this->repaint();
}


void management_tool::on_deleteProject_clicked()
{
    //check if there is a selected project
    if (ui->projectList_2->selectedItems().size()!=0){
        //update sql db
        int idx = ui->projectList_2->currentIndex().row();
        projectModel().removeProject(this->projects[idx]);

        setMainPage();
        this->repaint();
    }
}


void management_tool::on_pushButton_4_clicked()
{
    if(ui->taskList->selectedItems().size() == 1 && ui->taskList->currentItem()->columnCount() == 5){
        cur_task_status = ui->taskList->currentIndex().parent().row();
        if(cur_task_status == 0){
            cur_progress_task = ui->taskList->currentIndex().row();
        }
        else{
            cur_completed_task = ui->taskList->currentIndex().row();
        }
        setTaskPage();
        ui->stackedWidget->setCurrentIndex(5);
    }
}


void management_tool::on_viewBug_clicked()
{
    int idx = ui->bugList->currentRow();
    bugObject bug = this->bugs[idx];
    if (ui->bugList->selectedItems().size() == 1){
        QMessageBox::information(this, bug.name, bug.description);
    }
}



void management_tool::on_backToProject_clicked()
{
    setProjectPage();
    ui->stackedWidget->setCurrentIndex(2);
}


void management_tool::on_cancelNewTask_clicked()
{
    setProjectPage();
    ui->stackedWidget->setCurrentIndex(2);
}




void management_tool::on_newTaskButton_clicked()
{
    setNewTaskPage();
    ui->stackedWidget->setCurrentIndex(6);
}


void management_tool::on_projectStatusBox_currentIndexChanged(int index)
{
    projectObject project = this->projects[cur_project];
    if (index == 0){
        project.status = "New";
    }
    else if (index == 1){
        project.status = "In Progress";
    }
    else if (index == 2){
        project.status = "Completed";
    }
    else{
        project.status = "Closed";
    }

    //upate db
    project.updateProject();

    //refresh page
    this->repaint();
}


void management_tool::on_deleteTaskButton_clicked()
{
    //check if there is a selected task
    if(ui->taskList->selectedItems().size() == 1 && ui->taskList->currentItem()->columnCount() == 5){
        cur_task_status = ui->taskList->currentIndex().parent().row();
        if(cur_task_status == 0){
            cur_progress_task = ui->taskList->currentIndex().row();
        }
        else{
            cur_completed_task = ui->taskList->currentIndex().row();
        }

        //update sql db
        taskModel().removeTask(getTask());
        setProjectPage();
        this->repaint();
    }
}


void management_tool::on_deleteBug_clicked()
{
    //check if there is a selected project
    if(ui->bugList->selectedItems().size()!=0){
        int idx = ui->bugList->currentRow();
        //update sql db
        bugObject bug = this->bugs[idx];
        bugModel().removeBug(bug);
        setProjectPage();
        this->repaint();
    }
}


void management_tool::on_confirmNewTask_clicked()
{
    //hide all warning messages at the beginning
    ui->taskDateWarning->setVisible(false);
    ui->taskDescriptionWarning->setVisible(false);
    ui->taskTitleWarning->setVisible(false);
    ui->taskParticipantWarning->setVisible(false);
    //get input info
    QString title = ui->newTaskTitle->text();
    QString description = ui->newTaskDescription->toPlainText();
    QString finishDate_str = ui->newTaskDate->text();
    std::string std_finishDate = ui->newTaskDate->text().toStdString();
    //get participant
    if(ui->employeeList_2->selectedItems().size() == 0){
        ui->taskParticipantWarning->setVisible(true);
        return;
    }

    //check if project title is available
    if(title.size() == 0){
        ui->taskTitleWarning->setVisible(true);
    }


    //check date format
    else if (!checkDateFormat(std_finishDate)){
        ui->taskDateWarning->setVisible(true);
    }
    //check if description is empty
    else if (description.size() == 0){
        ui->taskDescriptionWarning->setVisible(true);
    }
    else{
        //update MySQL db
        QDateTime finishDate = QDateTime::fromString(finishDate_str, "MM/dd/yyyy");
        QString formattedDate = finishDate.toString("yyyy-MM-dd");
        qDebug() << formattedDate;
        int idx = ui->employeeList_2->currentRow();
        user employee = this->users[idx];
        taskModel().addTask(this->projects[cur_project], title, description, formattedDate, employee);

        //go back to project page
        QMessageBox::information(this, "Completed", "New task created");
        setProjectPage();
        ui->stackedWidget->setCurrentIndex(2);
    }
}


void management_tool::on_createBug_clicked()
{
    //get new bug info
    QString title = ui->bugTitle->text();
    QString description = ui->bugDescription->toPlainText();
    //check if bug title available
    if (title.size() == 0){
        QMessageBox::information(this, "Warning", "Bug title unavailable");
    }
    //check if bug description is empty
    else if (description.size() ==0){
        QMessageBox::information(this, "Warning", "Bug description cannot be empty");
    }
    //create new bug
    else{
        //update to sql db
        bugModel().addBug(this->projects[cur_project], title, description);

        QMessageBox::information(this, "Completed", "New bug created");
        //refresh the page
        setProjectPage();
        this->repaint();
    }
}


//post new comment button
void management_tool::on_pushButton_7_clicked()
{
    QString comment = ui->commentInput->toPlainText();
    //check if comment is empty
    if (comment.size() == 0){
        QMessageBox::information(this, "Warning", "Cannot post an empty comment");
    }
    else{
        //update to sql db
        commentModel().addComment(comment, getTask());

        QMessageBox::information(this, "Completed", "New comment posted");
        //refresh page
        setTaskPage();
        this->repaint();
    }
}


void management_tool::on_reassignButton_clicked()
{
    //update to sql db
    taskObject task = getTask();
    task.assignTask(*this->usr);

    //refresh the page
    setTaskPage();
    this->repaint();
}


void management_tool::on_taskStatusBox_currentIndexChanged(int index)
{
    string status;
    taskObject task = getTask();
    if (index == 0){
        task.status = "New";
    }
    else if (index == 1){
        task.status = "In Progress";
    }
    else if (index == 2){
        task.status = "Completed";
    }

    //upate task status to sql db
    task.updateTask();


    this->repaint();
}

