#ifndef FORM4_H
#define FORM4_H

#include <QWidget>
#include <QtGui>

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>

namespace Ui {
class Form4;
}

class Form4 : public QWidget
{
    Q_OBJECT
    
public:
    explicit Form4(QWidget *parent = 0);
    ~Form4();

protected:
    void resizeEvent(QResizeEvent *);

public slots:
    void TableView();
    void find(QString text);
    void informationTable();
    void deleteinformation();

    
private:
    Ui::Form4 *ui;
    void closeEvent(QCloseEvent *event);
};

#endif // FORM4_H
