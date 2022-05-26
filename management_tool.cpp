#include "management_tool.h"
#include "ui_management_tool.h"
#include <iostream>
#include <QString>
#include <QList>
#include <unistd.h>
#include <QListWidget>
#include <QIcon>
#include <QMessageBox>
using namespace std;

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


// start with all set page functions ---------------------------------------------------------------------------------------------
//set to login page
void management_tool::setLoginPage(){
    ui->stackedWidget->setCurrentIndex(0);
}


//set up main page
void management_tool::setMainPage(){
    //clear widgets
    ui->projectList->clear();
    //clear variable
    this->projects.clear();
    //set welcome label text
    ui->welcomeLabel->setText("Welcome, " + QString::fromStdString(userid));

    //fetch user name and project list from MySQL db


    //set up project list
    ui->projectList->clear();
    for(int i = 0; i<10; i++){
        this->projects.push_back("project"+std::to_string(i));
    }
    for(string p: this->projects){
        QListWidgetItem *item = new QListWidgetItem;
        item->setText(QString::fromStdString(p));
        //check status and set status icon


        item->setIcon(QIcon(":/icon/in_progress.png"));
        ui->projectList->addItem(item);
    }
    //chech user role and decide whether to show participants button
}

//set up project page
void management_tool::setProjectPage(std::string p){
    ui->projectName->setText(QString::fromStdString(p));
    this->projectName = p;
    //clear widgets
    ui->taskList->clear();
    ui->bugList->clear();
    //set place holder
    ui->bugTitle->clear();
    ui->bugDescription->clear();
    ui->bugTitle->setPlaceholderText("Bug title");
    ui->bugDescription->setPlaceholderText("Bug description");
    //retrieve data from sql db




    //get and set up project status. Index 0 = in progress, index 1 = completed
    ui->projectStatusBox->setCurrentIndex(1);

    //get task list
    QStringList label;
    ui->taskList->setColumnCount(5);
    label<<"Task Name"<<"Status"<<"Start Date"<<"End Date"<<"Worker";
    ui->taskList->setHeaderLabels(label);

    //get in progress task
    QTreeWidgetItem *root1 = new QTreeWidgetItem(ui->taskList);
    root1->setText(0, "In Progress");
    ui->taskList->addTopLevelItem(root1);
    for (int i=0; i<30; i++){
        std::string temp = "Task"+std::to_string(i);
        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, QString::fromStdString(temp));
        //check task status
        child->setText(1, "In Progress");
        //check task start and end date
        child->setText(2, QString::fromStdString(std::to_string(i)+"/23/2022"));
        child->setText(3, QString::fromStdString(std::to_string(i)+"/23/2023"));
        child->setText(4, "Worker1");
        root1->addChild(child);
    }

    //get completed tasks
    QTreeWidgetItem *root2 = new QTreeWidgetItem(ui->taskList);
    root2->setText(0, "Completed");
    ui->taskList->addTopLevelItem(root2);
    for (int i=0; i<30; i++){
        std::string temp = "Task"+std::to_string(i);
        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, QString::fromStdString(temp));
        //check task status
        child->setText(1, "Completed");
        //check task start and end date
        child->setText(2, QString::fromStdString(std::to_string(i)+"/23/2022"));
        child->setText(3, QString::fromStdString(std::to_string(i)+"/23/2023"));
        child->setText(4, "Worker1");
        root2->addChild(child);
    }

    //get bug list
    for (int i=0; i<12; i++){
        string temp = "bug"+std::to_string(i);
        this->bugs.push_back(temp);
        ui->bugList->addItem(QString::fromStdString(temp));
    }
    //check user's role
}



//set up create new project page
void management_tool::setNewProjectPage(){
    //clear widgets
    ui->employeeList->clear();
    //hide all warning message
    ui->projectTitleWarning->setVisible(false);
    ui->dateFormatWarning->setVisible(false);
    ui->emptyDescriptionWarning->setVisible(false);
    //set up employee list
    for (int i=0; i<42; i++){
        QListWidgetItem *item = new QListWidgetItem;
        string temp = "employee"+std::to_string(i);
        item->setText(QString::fromStdString(temp));
        item->setCheckState(Qt::Unchecked);
        ui->employeeList->addItem(item);
    }
}


//set up change participants page
void management_tool::setParticipantPage(std::string p){
    this->projectName = p;
    std::vector<std::string> participants;
    std::vector<std::string> newParticipants;
    //clear widgets
    ui->addParticipants->clear();
    ui->currentParticipants->clear();
    //retrieve participant lists and new participants list from MySQL db


    //set up current participants list
    for (string par: participants){
        QListWidgetItem *item = new QListWidgetItem;
        item->setText(QString::fromStdString(par));
        item->setCheckState(Qt::Unchecked);
        ui->currentParticipants->addItem(item);
    }

    //set up new participants list
    for (string par: newParticipants){
        QListWidgetItem *item = new QListWidgetItem;
        item->setText(QString::fromStdString(par));
        item->setCheckState(Qt::Unchecked);
        ui->addParticipants->addItem(item);
    }
}

//set up task page
void management_tool::setTaskPage(std::string tn){
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
    ui->taskLabel->setText(QString::fromStdString(tn));
    //check if the user is the worker


    //if is worker, hide assign_to_me button, show status change box
    if(1){
        ui->reassignButton->setVisible(false);
        ui->taskStatusLabel->setVisible(true);
        ui->taskStatusBox->setVisible(true);
        //get task status and change status box



        ui->taskStatusBox->setCurrentIndex(0);
    }
    //if not worker, show assign_to_me button, hide status change box
    if(0){
        ui->reassignButton->setVisible(true);
        ui->taskStatusLabel->setVisible(false);
        ui->taskStatusBox->setVisible(false);
    }
    //set comment section
    for (int i =0; i<6; i++){
    QTextBrowser* text = new QTextBrowser();
    text->setText("The progress looks good so far. Keep up the good work!!!");
    text->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->scrollAreaWidgetContents->layout()->addWidget(text);
    }
    //ui->scrollAreaWidgetContents->setLayout(layout);
}


//set up new task page
void management_tool::setNewTaskPage(){
    //clear widget
    ui->employeeList_2->clear();
    //hide all warning messages
    ui->taskDateWarning->setVisible(false);
    ui->taskDescriptionWarning->setVisible(false);
    ui->taskTitleWarning->setVisible(false);
    ui->taskParticipantWarning->setVisible(false);
    //get employee list for this project from sql db




    //set up employee list widget
    for (int i=0; i<12; i++){
        QListWidgetItem *item = new QListWidgetItem;
        string temp = "employee"+std::to_string(i);
        item->setText(QString::fromStdString(temp));
        ui->employeeList_2->addItem(item);
    }
}



//---------------------------------------------------------------------------------------------------------------------------------

void management_tool::on_login_2_clicked()
{
    string uid = ui->user_4->text().toStdString();
    string pwd = ui->password_4->text().toStdString();
    //check credential


    //if wrong credential, show warning message
    ui->warning_4->setVisible(true);

    //if right credential
    this->userid = uid;
    ui->warning_4->setVisible(false);
    //check user role

    //if user is employee, disable certain features by setting a few buttons invisible
    if (0){
        ui->createNew->setVisible(false);
        ui->deleteProject->setVisible(false);
        ui->viewParticipants->setVisible(false);
        ui->deleteBug->setVisible(false);
        ui->deleteTaskButton->setVisible(false);
        ui->newTaskButton->setVisible(false);
        ui->projectStatusBox->setVisible(false);
        ui->projectStatusLabel->setVisible(false);
    }
    //set up and go to main page
    setMainPage();
    ui->stackedWidget->setCurrentIndex(1);
}


void management_tool::on_logout_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void management_tool::on_viewDetail_clicked()
{
    if (ui->projectList->selectedItems().size()!=0){
        string pname = ui->projectList->currentItem()->text().toStdString();
        cout<<pname<<endl;
        //set up project page
        setProjectPage(pname);
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
    std::string title = ui->projectTitle->text().toStdString();
    std::string description = ui->projectDescription->toPlainText().toStdString();
    std::string finishDate = ui->projectDate->text().toStdString();
    //get participants list
    std::vector<std::string> part;
    cout<<description<<endl;
    for (int i=0; i < ui->employeeList->count(); i++){
        if (ui->employeeList->item(i)->checkState() == Qt::Checked){
            part.push_back(ui->employeeList->item(i)->text().toStdString());
            cout << ui->employeeList->item(i)->text().toStdString()<<endl;
        }
    }

    //check if project title is available
    if(title.size() == 0){
        ui->projectTitleWarning->setVisible(true);
    }


    //check date format
    else if (!checkDateFormat(finishDate)){
        ui->dateFormatWarning->setVisible(true);
    }
    //check if description is empty
    else if (description.size() == 0){
        ui->emptyDescriptionWarning->setVisible(true);
    }

    else{
        //update MySQL db


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
    if(ui->projectList->selectedItems().size()!=0){
        string pname = ui->projectList->currentItem()->text().toStdString();
        setParticipantPage(pname);
        ui->stackedWidget->setCurrentIndex(4);
    }
}


void management_tool::on_addParticipantsButton_clicked()
{
    //get added employees list
    std::vector<std::string> addP;
    for (int i=0; i<ui->addParticipants->count(); i++){
        if (ui->addParticipants->item(i)->checkState() == Qt::Checked){
            std::string temp = ui->addParticipants->item(i)->text().toStdString();
            addP.push_back(temp);
        }
    }
    //update MySQL db


    //update current page


    this->repaint();

}


void management_tool::on_removeParticipants_clicked()
{
    //get selected employees list
    std::vector<std::string> currentP;
    for (int i=0; i<ui->currentParticipants->count(); i++){
        if (ui->currentParticipants->item(i)->checkState() == Qt::Checked){
            std::string temp = ui->currentParticipants->item(i)->text().toStdString();
            currentP.push_back(temp);
        }
    }
    //update MySQL db


    //update current page


    this->repaint();
}


void management_tool::on_deleteProject_clicked()
{
    //check if there is a selected project
    if(ui->projectList->selectedItems().size()!=0){
        string pname = ui->projectList->currentItem()->text().toStdString();
        //update sql db


        setMainPage();
        this->repaint();
    }
}


void management_tool::on_pushButton_4_clicked()
{
    if(ui->taskList->selectedItems().size() == 1 && ui->taskList->currentItem()->columnCount() == 5){
        std::string taskName = ui->taskList->currentItem()->text(0).toStdString();
        cout<<taskName<<endl;
        setTaskPage(taskName);
        ui->stackedWidget->setCurrentIndex(5);
    }
}


void management_tool::on_viewBug_clicked()
{
    if (ui->bugList->selectedItems().size() == 1){
        QMessageBox::information(this, "bug1", "this is a bug. The button doesn't work and it will crush the program.");
    }
}



void management_tool::on_backToProject_clicked()
{
    setProjectPage(this->projectName);
    ui->stackedWidget->setCurrentIndex(2);
}


void management_tool::on_cancelNewTask_clicked()
{
    setProjectPage(this->projectName);
    ui->stackedWidget->setCurrentIndex(2);
}




void management_tool::on_newTaskButton_clicked()
{
    setNewTaskPage();
    ui->stackedWidget->setCurrentIndex(6);
}


void management_tool::on_projectStatusBox_currentIndexChanged(int index)
{
    string status;
    if (index == 0){
        status = "In Progress";
    }
    else{
        status = "Completed";
    }
    cout<<index<<endl;
    //upate db



    //refresh page
    this->repaint();
}


void management_tool::on_deleteTaskButton_clicked()
{
    //check if there is a selected task
    if(ui->taskList->selectedItems().size() == 1 && ui->taskList->currentItem()->columnCount() == 5){
        string tname = ui->taskList->currentItem()->text(0).toStdString();
        //update sql db


        setProjectPage(this->projectName);
        this->repaint();
    }
}


void management_tool::on_deleteBug_clicked()
{
    //check if there is a selected project
    if(ui->bugList->selectedItems().size()!=0){
        string bname = ui->bugList->currentItem()->text().toStdString();
        //update sql db


        setProjectPage(this->projectName);
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
    std::string title = ui->newTaskTitle->text().toStdString();
    std::string description = ui->newTaskDescription->toPlainText().toStdString();
    std::string finishDate = ui->newTaskDate->text().toStdString();
    //get participant
    if(ui->employeeList_2->selectedItems().size() == 0){
        ui->taskParticipantWarning->setVisible(true);
    }
    else{
        std::string participant = ui->employeeList_2->currentItem()->text().toStdString();
    }
    //check if project title is available
    if(title.size() == 0){
        ui->taskTitleWarning->setVisible(true);
    }


    //check date format
    else if (!checkDateFormat(finishDate)){
        ui->taskDateWarning->setVisible(true);
    }
    //check if description is empty
    else if (description.size() == 0){
        ui->taskDescriptionWarning->setVisible(true);
    }
    else{
        //update MySQL db



        //go back to project page
        QMessageBox::information(this, "Completed", "New task created");
        setProjectPage(this->projectName);
        ui->stackedWidget->setCurrentIndex(2);
    }
}


void management_tool::on_createBug_clicked()
{
    //get new bug info
    std::string title = ui->bugTitle->text().toStdString();
    std::string description = ui->bugDescription->toPlainText().toStdString();
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




        QMessageBox::information(this, "Completed", "New bug created");
        //refresh the page
        setProjectPage(this->projectName);
        this->repaint();
    }
}


//post new comment button
void management_tool::on_pushButton_7_clicked()
{
    std::string comment = ui->commentInput->toPlainText().toStdString();
    std::string taskName = ui->taskLabel->text().toStdString();
    //check if comment is empty
    if (comment.size() == 0){
        QMessageBox::information(this, "Warning", "Cannot post an empty comment");
    }
    else{
        //update to sql db



        QMessageBox::information(this, "Completed", "New comment posted");
        //refresh page
        setTaskPage(taskName);
        this->repaint();
    }
}


void management_tool::on_reassignButton_clicked()
{
    //update to sql db



    //refresh the page
    setTaskPage(ui->taskLabel->text().toStdString());
    this->repaint();
}


void management_tool::on_taskStatusBox_currentIndexChanged(int index)
{
    string status;
    if (index == 0){
        status = "In Progress";
    }
    else{
        status = "Completed";
    }
    cout<<index<<endl;
    //upate task status to sql db


    this->repaint();
}

