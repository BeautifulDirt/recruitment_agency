#ifndef FORM3_H
#define FORM3_H

#include <QWidget>
#include <QtGui>

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>

#include <QMouseEvent>

namespace Ui {
class Form3;
}

class Form3 : public QWidget
{
    Q_OBJECT
    
public:
    explicit Form3(QWidget *parent = 0);
    ~Form3();

protected:
    void resizeEvent(QResizeEvent *);

public slots:
    void newTransactions();
    void addTransactions();
    void formNew(bool check);
    void formAdd(bool check);
    void createTransaction();
    void delTransaction();
    void confirmTransaction();

private:
    Ui::Form3 *ui;
    void closeEvent(QCloseEvent *event);
};

#endif // FORM3_H
