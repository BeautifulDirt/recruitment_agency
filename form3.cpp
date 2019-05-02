#include "form3.h"
#include "ui_form3.h"

#include <QMessageBox>

int idTran;

int arrAsp[500];
int arrEmp[500];

bool flags = true;
bool tran = false;

Form3::Form3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form3)
{
    ui->setupUi(this);

    ui->radioButton->setChecked(true);
    formNew(false);
    formAdd(true);

    connect (ui->radioButton, SIGNAL(clicked()), this, SLOT(newTransactions()));
    connect (ui->radioButton_2, SIGNAL(clicked()), this, SLOT(addTransactions()));
    connect (ui->pushButton, SIGNAL(clicked()), this, SLOT(createTransaction()));
    connect (ui->pushButton_2, SIGNAL(clicked()), this, SLOT(delTransaction()));
    connect (ui->pushButton_3, SIGNAL(clicked()), this, SLOT(confirmTransaction()));

    //прочитать максимальный id
    QSqlQuery queryTranID;
    queryTranID.exec("SELECT max(id) FROM Transactions;");
    if (queryTranID.next()) {
        idTran = queryTranID.value(0).toInt();
    }

    int a=0, e=0;
    QSqlQuery query;
    query.exec("SELECT id, lastname, firstname, middlename, qualification FROM Aspirants");
    while (query.next())
    {
        arrAsp[a]=query.value(0).toInt();

        QStringList  lst;
        lst<<""+query.value(1).toString()+" "+ query.value(2).toString()+" "+query.value(3).toString()+", "+query.value(4).toString()+"";
        ui->comboBox->addItems(lst);
        ui->comboBox_2->addItems(lst);

        a++;
    }
    ui->comboBox->show();
    ui->comboBox_2->show();

    QSqlQuery query1;
    query1.exec("SELECT id, name, typeofactivity FROM Employers");
    while (query1.next())
    {
        arrEmp[e]=query1.value(0).toInt();

        QStringList  lst;
        lst<<""+query1.value(1).toString()+", "+ query1.value(2).toString()+"";
        ui->comboBox_3->addItems(lst);

        e++;
    }
    ui->comboBox_3->show();
}


void Form3::newTransactions()
{
    flags = true;

    formNew(false);
    formAdd(true);
}

void Form3::addTransactions()
{
    flags = false;

    formNew(true);
    formAdd(false);
}

void Form3::formNew(bool check)
{
    ui->lineEdit->setDisabled(check);
    ui->comboBox->setDisabled(check);
}

void Form3::formAdd(bool check)
{
    ui->comboBox_2->setDisabled(check);
    ui->comboBox_3->setDisabled(check);
}

int Asp, Emp, com;
QString nameEmp, qAsp;

void Form3::createTransaction()
{
    idTran++;
    tran = true;

    ui->textEdit->clear();
    com = ui->lineEdit_2->text().toInt();

    //прочитать и занести qAsp, nameEmp и com в таблицу Transactions
    if (flags){

        Asp = ui->comboBox->currentIndex();
        nameEmp = ui->lineEdit->text();

        QSqlQuery queryAsp1;
        queryAsp1.exec("SELECT qualification FROM Aspirants WHERE id ='"+QString::number(arrAsp[Asp])+"';");
        if (queryAsp1.next())
        {
            qAsp = queryAsp1.value(0).toString();
        }

        QSqlQuery queryTran1;
        queryTran1.prepare("insert into Transactions (id, employer, post, commission) values (?,?,?,?);");
        queryTran1.addBindValue(QString::number(idTran));
        queryTran1.addBindValue(nameEmp);
        queryTran1.addBindValue(qAsp);
        queryTran1.addBindValue(QString::number(com));
        queryTran1.exec();
    }

    else {
        Asp = ui->comboBox_2->currentIndex();
        Emp = ui->comboBox_3->currentIndex();

        QSqlQuery queryAsp2;
        queryAsp2.exec("SELECT qualification FROM Aspirants WHERE id ='"+QString::number(arrAsp[Asp])+"';");
        if (queryAsp2.next())
        {
            qAsp = queryAsp2.value(0).toString();
        }

        QSqlQuery queryEmp;
        queryEmp.exec("SELECT name FROM Employers WHERE id ='"+QString::number(arrEmp[Emp])+"';");
        if (queryEmp.next())
        {
            nameEmp = queryEmp.value(0).toString();
        }

        QSqlQuery queryTran2;
        queryTran2.prepare("insert into Transactions (id, employer, post, commission) values (?,?,?,?);");
        queryTran2.addBindValue(QString::number(idTran));
        queryTran2.addBindValue(nameEmp);
        queryTran2.addBindValue(qAsp);
        queryTran2.addBindValue(QString::number(com));
        queryTran2.exec();
    }

    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");

    QMessageBox msgBox;
    msgBox.setWindowTitle("База данных");
    msgBox.setText("Готово! Запись в архив сделок добавлена!");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();

    //показать результат в textEdit  
    QSqlQuery query2;
    query2.exec("SELECT employer, post, commission FROM Transactions WHERE id ='"+ QString::number(idTran) +"';");
    if (query2.next()) {
    ui->textEdit->insertPlainText("Работодатель: "+query2.value(0).toString()+
                                  "\nДолжность: "+query2.value(1).toString()+
                                  "\nКомиссионные, руб: "+query2.value(2).toString()+
                                  "\n\nЕсли все верно, нажмите кнопку Подтвердить!");
    }
}

void Form3::delTransaction()
{
    tran = false;
    //удалить из БД сделку в случае нажатия кнопки "Удалить и изменить"
    if (flags)
        ui->lineEdit->setText(nameEmp);
    ui->lineEdit_2->setText(QString::number(com));

    QSqlQuery query3;
    query3.prepare("DELETE FROM Transactions WHERE id ='" +QString::number(idTran)+"';");
    query3.exec();

    idTran--;

}

void Form3::confirmTransaction(){

    tran = false;
    //удалить соискателя и работодателя(если это нужно) из таблиц БД
    if (!flags)
    {
        QSqlQuery query4;
        query4.prepare("DELETE FROM Employers WHERE id ='" +QString::number(arrEmp[Emp])+"';");
        query4.exec();
    }

    QSqlQuery query5;
    query5.prepare("DELETE FROM Aspirants WHERE id ='" +QString::number(arrAsp[Asp])+"';");
    query5.exec();

    QMessageBox msgBox;
    msgBox.setWindowTitle("База данных");
    msgBox.setText("Готово! Анкеты удалены из БД! \nСделка выполнена!");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();

    ui->textEdit->clear();
}

void Form3::closeEvent(QCloseEvent *event)
{
    if (tran)
    {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::question( this, "База данных", tr("Вы не подтвердили выполнение сделки!\nНажмите кнопку Подтвердить, чтобы заключить сделку, иначе сделка будет удалена!\n\nЗакрыть окно?"),
                                     QMessageBox::Yes | QMessageBox::No , QMessageBox::No );
        if (ret == QMessageBox::No)
           event->ignore();
        else
        {
            QSqlQuery query6;
            query6.prepare("DELETE FROM Transactions WHERE id ='" +QString::number(idTran)+"';");
            query6.exec();
            tran = false;
        }
     }

}

Form3::~Form3()
{
    delete ui;
}

void Form3::resizeEvent(QResizeEvent *)
{

}


