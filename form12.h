#ifndef FORM12_H
#define FORM12_H

#include <QWidget>
#include <QtGui>

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class Form12;
}

class Form12 : public QWidget
{
    Q_OBJECT
    
public:
    explicit Form12(QWidget *parent = 0);
    ~Form12();

protected:
    void resizeEvent(QResizeEvent *);

public slots:
    void TableViewEmp();
    void findEmp(QString txt);
    void informationTableEmp();
    void deleteinformationEmp();
    
private:
    Ui::Form12 *ui;
};

#endif // FORM12_H
