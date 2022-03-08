#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "commande.h"
#include <QMessageBox>
#include"QIntValidator"
#include <QSqlQuery>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_idc_2->setValidator(new QIntValidator(0,9999,this));
    ui->le_idcl->setValidator(new QIntValidator(0,9999,this));
    ui->le_prix->setValidator(new QIntValidator(0,9999,this));
    ui->prix_1->setValidator(new QIntValidator(0,9999,this));
    ui->idcl_1->setValidator(new QIntValidator(0,9999,this));
    ui->chercher->setValidator(new QIntValidator(0,9999,this));
    ui->table_commande->setModel(c.afficher());

    ui->del_id_2->setModel(c.afficher_id());
    ui->tableView->setModel((c.afficher_id()));

}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_add_btn_clicked()
{
    int idc=ui->le_idc_2->text().toInt();
      int idcl=ui->le_idcl->text().toInt();
        int prix=ui->le_prix->text().toInt();
        QDate date_c=ui->date->date();
        QString demande=ui->demande->text();
    commande c(idc,idcl,prix,date_c,demande);
bool test=c.ajouter();
if(test)

{   //REFRESH
    ui->table_commande->setModel(c.afficher());
    ui->tableView->setModel(c.afficher_id());
    ui->del_id_2->setModel(c.afficher_id());
    QMessageBox::information(nullptr, QObject::tr("OK"),
                QObject::tr("Ajout effectué\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}
else
    QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                QObject::tr("Ajout non effectué\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_button_supprimer_clicked()
{
    commande c1; c1.setidc(ui->del_id_2->currentText().toInt());

    bool test=c1.supprimer(c1.getidc());
    QMessageBox msgBox;
    if(test)
    {   ui->table_commande->setModel(c.afficher());
        ui->tableView->setModel(c.afficher_id());
       // ui->update_id->setModel(c.afficher_id());
        ui->del_id_2->setModel(c.afficher_id());
        msgBox.setText("Suppression avec succes.");


    }
    else
        msgBox.setText("Echec de suppression.");
        msgBox.exec();
}

void MainWindow::on_button_modifier_clicked()
{   int idc=ui->update_id->text().toInt();
    //int idc=ui->idc_1->text().toInt();
    int idcl=ui->idcl_1->text().toInt();
      int prix=ui->prix_1->text().toInt();
      QDate date_c=ui->date_1->date();
      QString demande=ui->demande_1->text();
 commande c2(idc,idcl,prix,date_c,demande);
 bool test=c2.modifier();
 QMessageBox msgBox;
 if(test)
 {
    ui->table_commande->setModel(c.afficher());
    ui->tableView->setModel(c.afficher_id());
    ui->del_id_2->setModel(c.afficher_id());
    msgBox.setText("Modification avec succes.");

 }
 else
     msgBox.setText("Echec de Modification.");
     msgBox.exec();
}





void MainWindow::on_tri_prix_clicked()
{   ui->table_commande->setModel(c.tri_prix());
    QMessageBox::information(nullptr, QObject::tr("Ok"),
             QObject::tr("tri effectu.\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);
 }

void MainWindow::on_tri_idc_clicked()
{
    ui->table_commande->setModel(c.tri_idc());

    QMessageBox::information(nullptr, QObject::tr("Ok"),
             QObject::tr("tri effectu.\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_tri_date_clicked()
{   ui->table_commande->setModel(c.tri_idc());
    QMessageBox::information(nullptr, QObject::tr("Ok"),
             QObject::tr("tri effectu.\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);

}
void MainWindow::on_rechercher_clicked()
{

             int idc=ui->chercher->text().toInt();

             ui->table_commande->setModel(c.recherche(idc));
             QMessageBox::information(nullptr,QObject::tr("OK"),
                                       QObject::tr("recherche effectue.\n"
                                                   "clic cancel to exit."),QMessageBox::Cancel);
                    }






void MainWindow::on_tableView_activated(const QModelIndex &index)
{
    QSqlQuery query;
        QString idc=ui->tableView->model()->data(index).toString();
        query.prepare("select * from commande where idc='"+idc+"'");
        if(query.exec())
        {
            while (query.next())
            {
                ui->update_id->setText(query.value(0).toString());
                ui->idcl_1->setText(query.value(1).toString());
                ui->prix_1->setText(query.value(2).toString());
                ui->date_1->setDate(query.value(3).toDate());
                ui->demande_1->setText(query.value(4).toString());
            }
         }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("Failed"),
                            QObject::tr("Impossible.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
            }
}
