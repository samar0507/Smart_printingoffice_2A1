#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "commande.h"
#include <QMessageBox>
#include"QIntValidator"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_idc_2->setValidator(new QIntValidator(0,9999,this));
    ui->table_commande->setModel(c.afficher());
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
        QString date_c=ui->date->text();
        QString demande=ui->demande->text();
    commande c(idc,idcl,prix,date_c,demande);
bool test=c.ajouter();
if(test)

{   //REFRESH
    ui->table_commande->setModel(c.afficher());
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
    commande c1; c1.setidc(ui->del_id->text().toInt());
    bool test=c1.supprimer(c1.getidc());
    QMessageBox msgBox;
    if(test)
    {
        msgBox.setText("Suppression avec succes.");
          ui->table_commande->setModel(c.afficher());

    }
    else
        msgBox.setText("Echec de suppression.");
        msgBox.exec();
}

void MainWindow::on_button_modifier_clicked()
{ int idc=ui->idc_1->text().toInt();
    int idcl=ui->idcl_1->text().toInt();
      int prix=ui->prix_1->text().toInt();
      QString date_c=ui->date_1->text();
      QString demande=ui->demande_1->text();
 commande c2(idc,idcl,prix,date_c,demande);
 bool test=c2.modifier();
 QMessageBox msgBox;
 if(test)
 {
     msgBox.setText("Modification avec succes.");
       ui->table_commande->setModel(c.afficher());

 }
 else
     msgBox.setText("Echec de Modification.");
     msgBox.exec();
}


