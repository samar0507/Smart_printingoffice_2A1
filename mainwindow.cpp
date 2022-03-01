#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employes.h"
#include<QMessageBox>
#include<QIntValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->id->setValidator(new QIntValidator(0,9999999,this));

    ui->tab_employes->setModel(e.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_add_btn_clicked()
{
    int id=ui->id->text().toInt();
        QString nom=ui->nom->text();
        QString prenom=ui->per->text();
        QString date_naiss=ui->date->text();
        QString fonc= ui->fonc->text();
        employes e(id,nom,prenom,date_naiss,fonc);
        bool test=e.ajouter();
        if(test)
        {
            //REFRESH
            ui->tab_employes->setModel(e.afficher());
            QMessageBox::information(nullptr, QObject::tr("OK"),
                        QObject::tr("Ajout effectué.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Failed"),
                        QObject::tr("Ajout non effectué.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

        }
}

void MainWindow::on_del_btn_clicked()
{
    int id=ui->del_id->text().toInt();
         bool test=e.supprimer(id);
         if(test)
         {
             //REFRESH
             ui->tab_employes->setModel(e.afficher());
             QMessageBox::information(nullptr, QObject::tr("OK"),
                         QObject::tr("Suppression effectuée.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
         }
         else
         {
             QMessageBox::critical(nullptr, QObject::tr("Failed"),
                         QObject::tr("Suppression non effectuée.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);

         }
}

void MainWindow::on_mod_btn_clicked()
{
    int id=ui->id_mod->text().toInt();
           QString nom=ui->nom_mod->text();
           QString prenom=ui->per_mod->text();
           QString date_naiss=ui->date_mod->text();
           QString fonc=ui->fonc_mod->text();
        bool test=e.modifier(id,nom,prenom,date_naiss,fonc);
        if(test)
        {
            //REFRESH
            ui->tab_employes->setModel(e.afficher());
            QMessageBox::information(nullptr, QObject::tr("OK"),
                        QObject::tr("Modification effectuée.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Failed"),
                        QObject::tr("Modification non effectuée.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
}
