#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFile>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QFile f("style.сss");
    if (!f.exists())
    {
        qDebug("Unable to set stylesheet, file not found");
    }
    else
    {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        qApp->setStyleSheet(ts.readAll());
    }

    ui->setupUi(this);
    connect (ui->pushButton, SIGNAL(clicked()), this, SLOT(searchAsp()));
    connect (ui->pushButton_2, SIGNAL(clicked()), this, SLOT(addAspirants()));
    connect (ui->pushButton_3, SIGNAL(clicked()), this, SLOT(addEmployers()));
    connect (ui->pushButton_4, SIGNAL(clicked()), this, SLOT(addTransactions()));
    connect (ui->pushButton_5, SIGNAL(clicked()), this, SLOT(archiveTransactions()));
    connect (ui->pushButton_6, SIGNAL(clicked()), this, SLOT(exit_win()));
    connect (ui->pushButton_7, SIGNAL(clicked()), this, SLOT(information()));
    connect (ui->pushButton_8, SIGNAL(clicked()), this, SLOT(searchEmp()));
    
    sdb=QSqlDatabase::addDatabase("QSQLITE");
    //sdb.setHostName("localhost");
    sdb.setDatabaseName("job.db");
    //sdb.setUserName("root");
    //sdb.setPassword("");

    if (!sdb.open())
    {
        qDebug() << "Ошибочка с соединением!";
        QMessageBox msgBox;
        msgBox.setWindowTitle("Соединение...");
        msgBox.setText("Ошибка соединения с базой данных!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        return;
    }

    information();
}

void MainWindow::information()
{
    ui->textEdit->clear();

    QString  name, typeofactivity, address, phone;
    QSqlQuery query;
    query.exec("SELECT name, typeofactivity, address, phone FROM Employers");
    while (query.next())
    {
        name = query.value(0).toString();
        typeofactivity = query.value(1).toString();
        address = query.value(2).toString();
        phone = query.value(3).toString();
        ui->textEdit->insertPlainText("Работодатель: "+name+"\nСфера деятельности: "+typeofactivity+"\n"+address+"\nт."+phone+"\n\n");
    }
}

void MainWindow::searchAsp()
{
    form = new Form();
    form->show();
}

void MainWindow::searchEmp()
{
    form12 = new Form12();
    form12->show();
}

void MainWindow::addAspirants()
{
    form1 = new Form1();
    form1->show();
}

void MainWindow::addEmployers()
{
    form2 = new Form2();
    form2->show();
}

void MainWindow::addTransactions()
{
    form3 = new Form3();
    form3->show();
}

void MainWindow::archiveTransactions()
{
    form4 = new Form4();
    form4->show();
}

void MainWindow::exit_win()
{
    close();
    form->close();
    form1->close();
    form2->close();
    form3->close();
    form4->close();
    sdb.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}
