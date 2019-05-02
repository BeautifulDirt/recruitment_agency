#ifndef FORM1_H
#define FORM1_H

#include <QWidget>
#include <QtGui>

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class Form1;
}

class Form1 : public QWidget
{
    Q_OBJECT
    
public:
    explicit Form1(QWidget *parent = 0);
    ~Form1();

protected:
    void resizeEvent(QResizeEvent *);

public slots:
    void database();
    void clean();
    void cleanForm();
    void update();
    
private:
    Ui::Form1 *ui;
};

#endif // FORM1_H
