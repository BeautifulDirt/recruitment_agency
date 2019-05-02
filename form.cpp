#include "form.h"
#include "ui_form.h"

int asp;
int arrayAsp[500];

QStandardItem *itemAsp;
QStandardItemModel *modelAsp = new QStandardItemModel;

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);

    connect (ui->pushButton, SIGNAL(clicked()), this, SLOT(TableViewAsp()));
    connect (ui->pushButton_2, SIGNAL(clicked()), this, SLOT(deleteinformationAsp()));
    connect (ui->pushButton_3, SIGNAL(clicked()), this, SLOT(informationTableAsp()));

    informationTableAsp();

}

void Form::informationTableAsp()
{
    modelAsp->clear();
    asp=0;

    modelAsp->setColumnCount(7);
    modelAsp->setHorizontalHeaderLabels(QStringList()<<"Фамилия"<<"Имя"<<"Отчество"<<"Квалификация"<<"Вид деятельности"<<"Иные данные"<<"Предполагаемая з/п, руб");
    ui->tableView->setModel(modelAsp);

    QSqlQuery query;
    query.exec("SELECT * FROM Aspirants");
    while (query.next())
    {
        arrayAsp[asp]=query.value(0).toInt();

        itemAsp = new QStandardItem(query.value(1).toString());
        modelAsp->setItem(asp, 0, itemAsp);

        itemAsp = new QStandardItem(query.value(2).toString());
        modelAsp->setItem(asp, 1, itemAsp);

        itemAsp = new QStandardItem(query.value(3).toString());
        modelAsp->setItem(asp, 2, itemAsp);

        itemAsp = new QStandardItem(query.value(4).toString());
        modelAsp->setItem(asp, 3, itemAsp);

        itemAsp = new QStandardItem(query.value(5).toString());
        modelAsp->setItem(asp, 4, itemAsp);

        itemAsp = new QStandardItem(query.value(6).toString());
        modelAsp->setItem(asp, 5, itemAsp);

        itemAsp = new QStandardItem(query.value(7).toString());
        modelAsp->setItem(asp, 6, itemAsp);

        asp++;
    }
}

void Form::deleteinformationAsp()
{
    QItemSelectionModel *selectModel = ui->tableView->selectionModel();
    if (selectModel->hasSelection()) {
        int str = selectModel->selectedRows().first().row();
        QSqlQuery queryDel;
        queryDel.prepare("DELETE FROM Aspirants WHERE id ='" +QString::number(arrayAsp[str])+"';");
        queryDel.exec();
        informationTableAsp();
    }
}

void Form::TableViewAsp()
{
    QString  textAsp;
    textAsp = ui->lineEdit->text();
    findAsp(textAsp);
}

void Form::findAsp(QString txt)
{
    informationTableAsp();
    ui->lineEdit->setText("");

    QString tmp;
    QRegExp rx("^"+txt+"");

    for (int j=0;j<7;j++){
        for (int k=0;k<ui->tableView->model()->rowCount();k++){
            tmp = ui->tableView->model()->data(ui->tableView->model()->index(k,j)).toString();
            if (rx.exactMatch(tmp)){
                ui->tableView->model()->setData(ui->tableView->model()->index(k,j),QBrush(QColor(96, 153, 96)),Qt::BackgroundRole);
            }
        }
    }
}

Form::~Form()
{
    delete ui;
}

void Form::resizeEvent(QResizeEvent *)
{

}


