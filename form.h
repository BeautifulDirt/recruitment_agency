#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QtGui>

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT
    
public:
    explicit Form(QWidget *parent = 0);
    ~Form();

protected:
    void resizeEvent(QResizeEvent *);

public slots:
    void TableViewAsp();
    void findAsp(QString txt);
    void informationTableAsp();
    void deleteinformationAsp();
    
private:
    Ui::Form *ui;
};

#endif // FORM_H
