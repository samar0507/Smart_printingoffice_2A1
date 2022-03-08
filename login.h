#ifndef LOGIN_H
#define LOGIN_H
#include "mainwindow.h"
#include "employes.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class login; }
QT_END_NAMESPACE

class login : public QMainWindow
{
    Q_OBJECT

public:
    login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_login_2_clicked();

private:
    Ui::login *ui;
    MainWindow *ri;
    QSqlDatabase db;
};
#endif // LOGIN_H
