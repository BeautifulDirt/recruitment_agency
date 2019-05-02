#ifndef FORM2_H
#define FORM2_H

#include <QWidget>
#include <QtGui>

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class Form2;
}

class Form2 : public QWidget
{
    Q_OBJECT
    
public:
    explicit Form2(QWidget *parent = 0);
    ~Form2();

protected:
    void resizeEvent(QResizeEvent *);

public slots:
    void database();
    void clean();
    void cleanForm();
    void update();
    
private:
    Ui::Form2 *ui;
};

#endif // FORM2_H
