#include "form12.h"
#include "ui_form12.h"

int emp;
int arrayEmp[500];

QStandardItem *itemEmp;
QStandardItemModel *modelEmp = new QStandardItemModel;

Form12::Form12(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form12)
{
    ui->setupUi(this);
    connect (ui->pushButton, SIGNAL(clicked()), this, SLOT(TableViewEmp()));
    connect (ui->pushButton_2, SIGNAL(clicked()), this, SLOT(deleteinformationEmp()));
    connect (ui->pushButton_3, SIGNAL(clicked()), this, SLOT(informationTableEmp()));

    informationTableEmp();
}

void Form12::informationTableEmp()
{
    modelEmp->clear();
    emp=0;

    modelEmp->setColumnCount(4);
    modelEmp->setHorizontalHeaderLabels(QStringList()<<"Предприятие"<<"Вид деятельности"<<"Адрес"<<"Телефон");
    ui->tableView->setModel(modelEmp);

    QSqlQuery query;
    query.exec("SELECT * FROM Employers");
    while (query.next())
    {
        arrayEmp[emp]=query.value(0).toInt();

        itemEmp = new QStandardItem(query.value(1).toString());
        modelEmp->setItem(emp, 0, itemEmp);

        itemEmp = new QStandardItem(query.value(2).toString());
        modelEmp->setItem(emp, 1, itemEmp);

        itemEmp = new QStandardItem(query.value(3).toString());
        modelEmp->setItem(emp, 2, itemEmp);

        itemEmp = new QStandardItem(query.value(4).toString());
        modelEmp->setItem(emp, 3, itemEmp);

        emp++;
    }
}

void Form12::deleteinformationEmp()
{
    //удаление производится первой по счету выбранной строки
    QItemSelectionModel *selectModel = ui->tableView->selectionModel();
    if (selectModel->hasSelection()) {
        int str = selectModel->selectedRows().first().row();
        QSqlQuery queryDel;
        queryDel.prepare("DELETE FROM Employers WHERE id ='" +QString::number(arrayEmp[str])+"';");
        queryDel.exec();
        informationTableEmp();
    }
}

void Form12::TableViewEmp()
{
    QString  textEmp;
    textEmp = ui->lineEdit->text();
    findEmp(textEmp);
}

void Form12::findEmp(QString txt)
{
    informationTableEmp();
    ui->lineEdit->setText("");

    QString tmp;
    QRegExp rx("^"+txt+"");

    for (int j=0;j<4;j++){
        for (int k=0;k<ui->tableView->model()->rowCount();k++){
            tmp = ui->tableView->model()->data(ui->tableView->model()->index(k,j)).toString();
            if (rx.exactMatch(tmp)){
                ui->tableView->model()->setData(ui->tableView->model()->index(k,j),QBrush(QColor(96, 153, 96)),Qt::BackgroundRole);
            }
        }
    }
}


Form12::~Form12()
{
    delete ui;
}

void Form12::resizeEvent(QResizeEvent *)
{

}


