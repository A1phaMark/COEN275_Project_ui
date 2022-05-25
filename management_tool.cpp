#include "management_tool.h"
#include "ui_management_tool.h"
#include <iostream>
#include <QString>
#include <QList>
#include <unistd.h>
#include <QListWidget>
#include <QIcon>
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

//set up main page
void management_tool::setMainPage(){
    //set welcome label text
    ui->welcomeLabel->setText("Welcome, " + QString::fromStdString(userid));

    //fetch project list from MySQL db


    //set up project list
    this->projects.clear();
    for(int i = 0; i<100; i++){
        this->projects.push_back("project"+std::to_string(i));
    }
    for(string p: this->projects){
        QListWidgetItem *item = new QListWidgetItem;
        item->setText(QString::fromStdString(p));
        item->setIcon(QIcon(":/icon/in_progress.png"));
        ui->projectList->addItem(item);
    }
    //chech user role and decide whether to show participants button
}

//set up project page
void management_tool::setProjectPage(std::string p){
    ui->projectName->setText(QString::fromStdString(p));
    //get task list
    for (int i=0; i<20; i++){
        string temp = "task"+std::to_string(i);
        this->tasks.push_back(temp);
        ui->taskList->addItem(QString::fromStdString(temp));
    }
    //get bug list
    for (int i=0; i<12; i++){
        string temp = "task"+std::to_string(i);
        this->bugs.push_back(temp);
        ui->bugList->addItem(QString::fromStdString(temp));
    }
    //check user's role
}

//set up create new project page
void management_tool::setNewProjectPage(){
    //hide all message
    ui->projectTitleWarning->setVisible(false);
    ui->successMessage->setVisible(false);
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
    string pname = ui->projectList->currentItem()->text().toStdString();
    cout<<pname<<endl;
    //set up project page
    setProjectPage(pname);
    //go to project page
    ui->stackedWidget->setCurrentIndex(2);
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
    //check if project title is available

    //if title not available

    //if title available
    ui->successMessage->setVisible(true);

    //get participants list
    std::string title = ui->projectTitle->text().toStdString();
    std::string description = ui->projectDescription->toPlainText().toStdString();
    std::string date = ui->projectDate->text().toStdString();
    std::vector<std::string> part;
    cout<<description<<endl;
    for (int i=0; i < ui->employeeList->count(); i++){
        if (ui->employeeList->item(i)->checkState() == Qt::Checked){
            part.push_back(ui->employeeList->item(i)->text().toStdString());
            cout << ui->employeeList->item(i)->text().toStdString()<<endl;
        }
    }

    //update MySQL db


    //go back to main page
    sleep(2);
    setMainPage();
    ui->stackedWidget->setCurrentIndex(1);
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
    string pname = ui->projectList->currentItem()->text().toStdString();
    setParticipantPage(pname);
    ui->stackedWidget->setCurrentIndex(4);
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

