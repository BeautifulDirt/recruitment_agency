#include "form4.h"
#include "ui_form4.h"

#include <QMessageBox>

int i;
int array[500];

QStandardItem *item;
QStandardItemModel *model = new QStandardItemModel;

Form4::Form4(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form4)
{
    ui->setupUi(this);
    connect (ui->pushButton, SIGNAL(clicked()), this, SLOT(TableView()));
    connect (ui->pushButton_2, SIGNAL(clicked()), this, SLOT(deleteinformation()));
    connect (ui->pushButton_3, SIGNAL(clicked()), this, SLOT(informationTable()));

    informationTable();
}

void Form4::informationTable()
{
    model->clear();
    i=0;

    model->setColumnCount(3);
    model->setHorizontalHeaderLabels(QStringList()<<"Работодатель"<<"Должность"<<"Комиссионные, руб");
    ui->tableView->setModel(model);

    QSqlQuery query;
    query.exec("SELECT * FROM Transactions");
    while (query.next())
    {
        array[i]=query.value(0).toInt();

        item = new QStandardItem(query.value(1).toString());
        model->setItem(i, 0, item);

        item = new QStandardItem(query.value(2).toString());
        model->setItem(i, 1, item);

        item = new QStandardItem(query.value(3).toString());
        model->setItem(i, 2, item);

        i++;
    }
}

void Form4::deleteinformation(){

    QItemSelectionModel *selectModel = ui->tableView->selectionModel();
    if (selectModel->hasSelection()) {
        int str = selectModel->selectedRows().first().row();
        QSqlQuery queryDel;
        queryDel.prepare("DELETE FROM Transactions WHERE id ='" +QString::number(array[str])+"';");
        queryDel.exec();
        informationTable();
    }
}

void Form4::TableView()
{
    QString  txt;
    txt = ui->lineEdit->text();
    find(txt);
}

void Form4::find(QString text)
{
    informationTable();
    ui->lineEdit->setText("");

    QString tmp;
    QRegExp rx("^"+text+"");

    for (int j=0;j<3;j++){
        for (int k=0;k<ui->tableView->model()->rowCount();k++){
            tmp = ui->tableView->model()->data(ui->tableView->model()->index(k,j)).toString();
            if (rx.exactMatch(tmp)){
                ui->tableView->model()->setData(ui->tableView->model()->index(k,j),QBrush(QColor(96, 153, 96)),Qt::BackgroundRole);
            }
        }
    }
}

void Form4::closeEvent(QCloseEvent *event)
{
   event->accept();
   model->clear();
   i=0;
}

Form4::~Form4()
{
    delete ui;
}

void Form4::resizeEvent(QResizeEvent *)
{

}


