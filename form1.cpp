#include "form1.h"
#include "ui_form1.h"

#include <QMessageBox>

int idAsp;

Form1::Form1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form1)
{
    ui->setupUi(this);

    connect (ui->pushButton, SIGNAL(clicked()), this, SLOT(database()));
    connect (ui->pushButton_2, SIGNAL(clicked()), this, SLOT(clean()));
    connect (ui->pushButton_3, SIGNAL(clicked()), this, SLOT(update()));

    //прочитать максимальный id
    //увеличить на 1
    QSqlQuery queryID;
    queryID.exec("SELECT max(id) FROM Aspirants;");

    if (queryID.next()) {
        idAsp = queryID.value(0).toInt();
    }

}

QString  ln, fn, mn, qua, activ, od;
int salary;

void Form1::database()
{
    idAsp++;

    ln = ui->lineEdit->text();
    fn = ui->lineEdit_2->text();
    mn = ui->lineEdit_3->text();
    qua = ui->lineEdit_4->text();
    activ = ui->lineEdit_5->text();
    od = ui->textEdit->toPlainText();
    salary = ui->lineEdit_6->text().toInt();

    QSqlQuery query;
    query.prepare("insert into Aspirants (id, lastname, firstname, middlename, qualification, typeofactivity, otherdata, salary) values (?,?,?,?,?,?,?,?);");
    query.addBindValue(QString::number(idAsp));
    query.addBindValue(ln);
    query.addBindValue(fn);
    query.addBindValue(mn);
    query.addBindValue(qua);
    query.addBindValue(activ);
    query.addBindValue(od);
    query.addBindValue(salary);
    query.exec();

    cleanForm();
    ui->textEdit_2->clear();

    QMessageBox msgBox;
    msgBox.setWindowTitle("База данных");
    msgBox.setText("Готово! Запись добавлена!");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();

    QSqlQuery query1;
    query1.exec("SELECT lastname, firstname, middlename, qualification, typeofactivity, otherdata, salary FROM Aspirants WHERE id ='"+ QString::number(idAsp) +"';");
    if (query1.next()) {
    ui->textEdit_2->insertPlainText("ФИО: "+query1.value(0).toString()+" "+query1.value(1).toString()+" "+query1.value(2).toString()+
                                    "\nКвалификация: "+query1.value(3).toString()+
                                    "\nСфера деятельности: "+query1.value(4).toString()+
                                    "\nИные данные: "+query1.value(5).toString()+
                                    "\nПредполагаемый размер з/п, руб: "+query1.value(6).toString());
    }

}

void Form1::clean()
{
    cleanForm();
}

void Form1::cleanForm()
{
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
    ui->lineEdit_4->setText("");
    ui->lineEdit_5->setText("");
    ui->lineEdit_6->setText("");
    ui->textEdit->clear();
}

void Form1::update()
{
    QSqlQuery query;
    query.prepare("DELETE FROM Aspirants WHERE id ='" +QString::number(idAsp)+"';");
    query.exec();

    ui->lineEdit->setText(ln);
    ui->lineEdit_2->setText(fn);
    ui->lineEdit_3->setText(mn);
    ui->lineEdit_4->setText(qua);
    ui->lineEdit_5->setText(activ);
    ui->lineEdit_6->setText(QString::number(salary));
    ui->textEdit->insertPlainText(od);

    idAsp--;
}

Form1::~Form1()
{
    delete ui;
}

void Form1::resizeEvent(QResizeEvent *)
{

}


