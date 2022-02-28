#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "produits.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab_produit->setModel(P.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_ajouter_clicked()
{
    int id=ui->l_id->text().toInt();
    QString nom=ui->l_nom->text();
    QDate date_p=ui->l_date->date();
    float prix=ui->l_prix->text().toInt();
    int quantite=ui->l_quantite->text().toInt();

    Produits P(id,nom,date_p,prix,quantite);
    bool test=P.ajouter();
    QMessageBox msgBox;
    if (test)
      {  //refresh
        ui->tab_produit->setModel(P.afficher());
         msgBox.setText("Ajout avec succés");
          ui->l_id->clear();
          ui->l_nom->clear();
          ui->l_date->clear();
          ui->l_prix->clear();
          ui->l_quantite->clear();
    }
    else
         msgBox.setText("Echec d'ajout.");
         msgBox.exec();
}

void MainWindow::on_pb_supprimer_clicked()
{
    Produits P1;
    P1.setid(ui->l_id_sup->text().toInt());
    bool test=P1.supprimer(P1.getid());
    QMessageBox msgBox;
    if (test)
    {       //refresh
        ui->tab_produit->setModel(P.afficher());
        QMessageBox::information(this,"Suppression","Suppression avec succés");

        // msgBox.setText("Suppression avec succés");
         ui->l_id_sup->clear();

   }
    else
         msgBox.setText("Echec de suppression.");
         msgBox.exec();
}


void MainWindow::on_pb_modifier_clicked()
{

    int id =ui->l_idm->text().toInt();
    QString nom =ui->l_nomm->text();
    QDate date_p=ui->l_datem->date();
    int prix=ui->l_prixm->text().toInt();
    int quantite=ui->l_quantitem->text().toInt();

Produits P2(id,nom,date_p,prix,quantite);

bool test=false;
     if (id>0)test=P2.modifier(P2);
    {
        ui->tab_produit->setModel(P.afficher());
        QMessageBox::information(this,"Modification","ce Produit a eté modifiée");
    }
     ui->l_idm->clear();
     ui->l_nomm->clear();
     ui->l_datem->clear();
     ui->l_prixm->clear();
     ui->l_quantitem->clear();
}
