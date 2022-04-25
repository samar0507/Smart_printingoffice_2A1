#include "login.h"
#include "ui_login.h"
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
login::login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}


void login::on_login_2_clicked()
{

    QString nom = ui->lineEdit_username->text();
    QString pass = ui->lineEdit_password->text();

    QSqlQuery query;


         query.prepare(("SELECT *FROM employes WHERE nom =:nom AND pass=:pass"));
         query.bindValue(":nom",nom);
         query.bindValue(":pass",pass);
         query.exec();
         if(query.next())
         {

             ri = new MainWindow(this);
                        ri->show();
                        }

                        else{
                            QMessageBox::critical(this,"Error","Wrong password or username");
                        }
}
