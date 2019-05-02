#include "form2.h"
#include "ui_form2.h"

#include <QMessageBox>

int idEmp;

Form2::Form2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form2)
{
    ui->setupUi(this);

    connect (ui->pushButton, SIGNAL(clicked()), this, SLOT(database()));
    connect (ui->pushButton_2, SIGNAL(clicked()), this, SLOT(clean()));
    connect (ui->pushButton_3, SIGNAL(clicked()), this, SLOT(update()));

    //прочитать максимальный id
    //увеличить на 1
    QSqlQuery queryID;
    queryID.exec("SELECT max(id) FROM Employers;");
    if (queryID.next()) {
        idEmp = queryID.value(0).toInt();
    }

}

QString  name, act, ads, phn;

void Form2::database()
{
    idEmp++;

    name = ui->lineEdit->text();
    act = ui->lineEdit_2->text();
    ads = ui->lineEdit_3->text();
    phn = ui->lineEdit_4->text();

    QSqlQuery query;
    query.prepare("insert into Employers (id, name, typeofactivity, address, phone) values (?,?,?,?,?);");
    query.addBindValue(QString::number(idEmp));
    query.addBindValue(name);
    query.addBindValue(act);
    query.addBindValue(ads);
    query.addBindValue(phn);
    query.exec();

    cleanForm();
    ui->textEdit->clear();

    QMessageBox msgBox;
    msgBox.setWindowTitle("База данных");
    msgBox.setText("Готово! Запись добавлена!");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();

    QSqlQuery query1;
    query1.exec("SELECT name, typeofactivity, address, phone FROM Employers WHERE id ='"+ QString::number(idEmp) +"';");
    if (query1.next()) {
    ui->textEdit->insertPlainText(query1.value(0).toString()+
                                    "\nСфера деятельности: "+query1.value(1).toString()+
                                    "\nАдрес: "+query1.value(2).toString()+
                                    "\nтел. "+query1.value(3).toString());
    }

}

void Form2::clean()
{
    cleanForm();
}

void Form2::cleanForm()
{
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
    ui->lineEdit_4->setText("");
}

void Form2::update()
{
    QSqlQuery query;
    query.prepare("DELETE FROM Employers WHERE id ='" +QString::number(idEmp)+"';");
    query.exec();

    ui->lineEdit->setText(name);
    ui->lineEdit_2->setText(act);
    ui->lineEdit_3->setText(ads);
    ui->lineEdit_4->setText(phn);

    idEmp--;

}

Form2::~Form2()
{
    delete ui;
}

void Form2::resizeEvent(QResizeEvent *)
{

}


