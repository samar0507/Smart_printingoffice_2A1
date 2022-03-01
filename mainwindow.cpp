#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
    #include <QComboBox>
#include <QLineEdit>
#include <QMessageBox>
#include <QIntValidator>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab_cl->setModel(cl.afficher());
    QSqlQueryModel *model = new QSqlQueryModel;
        model->setQuery("SELECT cin FROM client");
        ui->comboBox->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_4_clicked()
{

int cin=ui->comboBox->currentText().toInt();
    bool test=cl.supprimer(cin);
    if(test)
    { ui->tab_cl->setModel(cl.afficher());//refresh
        ui->comboBox->clear();
        QSqlQueryModel *model = new QSqlQueryModel;
            model->setQuery("SELECT cin FROM client");
            ui->comboBox->setModel(model);

        QMessageBox::information(nullptr, QObject::tr("done"),
                               QObject::tr("suppression effectue.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);

           }
               else
                   QMessageBox::critical(nullptr, QObject::tr("error"),
                               QObject::tr("suppression non effectue.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_pushButton_20_clicked()
{
    int cin = ui->lineEdit_cin->text().toInt();
    QString nom=ui->lineEdit_nom->text();
    int date_naissance = ui->lineEdit_date->text().toInt();
    QString adresse=ui->lineEdit_adresse->text();
      QString prenom=ui->lineEdit_prenom->text();

      client cl(cin,date_naissance,nom,prenom,adresse);
       bool test=cl.ajouter();
       if(test)
       { ui->tab_cl->setModel(cl.afficher());//refresh
           ui->comboBox->clear();
           QSqlQueryModel *model = new QSqlQueryModel;
               model->setQuery("SELECT cin FROM client");
               ui->comboBox->setModel(model);
           ui->lineEdit_cin->clear();
           ui->lineEdit_nom->clear();
           ui->lineEdit_prenom->clear();
           ui->lineEdit_date->clear();
           ui->lineEdit_adresse->clear();
           QMessageBox::information(nullptr, QObject::tr("done"),
                                  QObject::tr("ajout effectue.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);

              }
                  else
                      QMessageBox::critical(nullptr, QObject::tr("error"),
                                  QObject::tr("ajout non effectue.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_pushButton_19_clicked()
{

    int cin = ui->lineEdit_cin->text().toInt();
    QString nom=ui->lineEdit_nom->text();
    int date_naissance = ui->lineEdit_date->text().toInt();
    QString adresse=ui->lineEdit_adresse->text();
      QString prenom=ui->lineEdit_prenom->text();
      client cl(cin,date_naissance,nom,prenom,adresse );
      bool test=cl.modifier(cin);
      if(test)
      { ui->tab_cl->setModel(cl.afficher());//refresh
          QSqlQueryModel *model = new QSqlQueryModel;
              model->setQuery("SELECT cin FROM client");
              ui->comboBox->setModel(model);
              ui->comboBox->clear();
          ui->lineEdit_cin->clear();
          ui->lineEdit_nom->clear();
          ui->lineEdit_prenom->clear();
          ui->lineEdit_date->clear();
          ui->lineEdit_adresse->clear();
      QMessageBox::information(nullptr, QObject::tr("done "),
                        QObject::tr("modification effectué!\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);


      }
        else
            QMessageBox::critical(nullptr, QObject::tr("error"),
                        QObject::tr("modification non effectué !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
}

