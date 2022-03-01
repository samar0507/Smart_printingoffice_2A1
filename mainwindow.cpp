#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fournisseurs.h"
#include<QMessageBox>
#include<QIntValidator>
//test git
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->id->setValidator(new QIntValidator(0,9999999,this));

    ui->tab_fournisseurs->setModel(f.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_add_btn_clicked()
{
    //récupération des informations saisies
    int id=ui->id->text().toInt();
    QString nom=ui->nom->text();
    QString date_deb=ui->deb->text();
    QString date_fin=ui->fin->text();
    QString adresse= ui->adresse->text();
    fournisseurs f(id,nom,date_deb,date_fin,adresse);
    bool test=f.ajouter();
    if(test)
    {
        //REFRESH
        ui->tab_fournisseurs->setModel(f.afficher());
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
     bool test=f.supprimer(id);
     if(test)
     {
         //REFRESH
         ui->tab_fournisseurs->setModel(f.afficher());
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
void MainWindow::on_update_btn_clicked()
{
    //récupération des informations saisies
    int id=ui->update_id->text().toInt();
//    int id=ui->update_id->text().toInt();
//    e.setId(ui->update_id->text().toInt())
       QString nom=ui->new_nom->text();
       QString date_deb=ui->new_deb->text();
       QString date_fin=ui->new_fin->text();
       QString adresse=ui->new_adresse->text();
//    e.setNom(ui->new_nom->text());
//    e.setPrenom(ui->new_prenom->text());
//    etudiant e(id,nom,prenom);
    bool test=f.modifier(id,nom,date_deb,date_fin,adresse);
    if(test)
    {
        //REFRESH
        ui->tab_fournisseurs->setModel(f.afficher());
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

void MainWindow::on_detele_all_btn_clicked()
{
    //int id=ui->del_id->text().toInt();
     bool test=f.supprimerTout();
     if(test)
     {
         //REFRESH
         ui->tab_fournisseurs->setModel(f.afficher());
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
