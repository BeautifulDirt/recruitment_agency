#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <form.h>
#include <form1.h>
#include <form12.h>
#include <form2.h>
#include <form3.h>
#include <form4.h>

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
    Form *form;
    Form1 *form1;
    Form12 *form12;
    Form2 *form2;
    Form3 *form3;
    Form4 *form4;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void searchAsp();
    void searchEmp();
    void addAspirants();
    void addEmployers();
    void addTransactions();
    void archiveTransactions();
    void exit_win();
    void information();
    
private:
    Ui::MainWindow *ui;
    QSqlDatabase sdb;
};

#endif // MAINWINDOW_H
