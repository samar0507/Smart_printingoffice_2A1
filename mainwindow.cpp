#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "produits.h"
#include "statistiques.h"


#include <QPrinter>
#include<QPrintDialog>
#include<QPdfWriter>
#include<QPainter>
#include<QDesktopServices>
#include<QUrl>
#include <QtWidgets>
#include <QPlainTextEdit>
#include <QPrinterInfo>
#include <QTextStream>
#include <QTextStream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->l_id->setValidator(new QIntValidator(0,9999,this));
    ui->l_prix->setValidator(new QIntValidator(0,99999999,this));
    ui->l_quantite->setValidator(new QIntValidator(0,99999999,this));
    ui->l_idm->setValidator(new QIntValidator(0,9999,this));
    ui->l_prixm->setValidator(new QIntValidator(0,99999999,this));
    ui->l_quantitem->setValidator(new QIntValidator(0,99999999,this));

    ui->tab_produit->setModel(P.afficher());
    QSqlQueryModel * model2= new QSqlQueryModel();
    model2->setQuery("select id from produits")  ;
    ui->l_idm->setModel(model2) ;
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select id from produits")  ;
    ui->l_id_sup->setModel(model) ;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refresh()
{
    QSqlQueryModel * model2= new QSqlQueryModel();
    model2->setQuery("select id from produits")  ;
    ui->l_idm->setModel(model2) ;
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select id from produits")  ;
    ui->l_id_sup->setModel(model) ;
    ui->tab_produit->setModel(model2) ;
}

void MainWindow::on_pb_ajouter_clicked() //ajouter un produit
{
    int id=ui->l_id->text().toInt();
    QString nom=ui->l_nom->text();
    QDate date_p=ui->l_date->date();
    int prix=ui->l_prix->text().toInt();
    int quantite=ui->l_quantite->text().toInt();

    Produits P(id,nom,date_p,prix,quantite);
    if( nom.isEmpty()  )
       {
        QMessageBox::critical(0,qApp->tr("Erreur!!"),qApp->tr("Veuillez remplir les champs vides."),QMessageBox::Cancel);
       }
    else
       {
    bool test=P.ajouter();
     if (test)
      {
           Notification n("Ajouté avec succés","Produit ajouté");
           n.afficher();
          ui->tab_produit->setModel(P.afficher());
          ui->l_id->clear();
          ui->l_nom->clear();
          ui->l_date->clear();
          ui->l_prix->clear();
          ui->l_quantite->clear();
      }
    else
        {   Notification n("Echec d'ajout ","Produit non ajouté");
            n.afficher();
        }
    }
}

void MainWindow::on_pb_supprimer_clicked() //supprimer un produit
{
    int id = ui->l_id_sup->currentText().toInt();
    bool test=P.supprimer(id);
    if(test)
  {
        Notification n("Supprimé avec succés","Produit supprimé");
        n.afficher();
        ui->tab_produit->setModel(P.afficher());

        QSqlQueryModel * model2= new QSqlQueryModel();
        model2->setQuery("select id from produits")  ;
        ui->l_idm->setModel(model2) ;

        QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("select id from produits")  ;
        ui->l_id_sup->setModel(model) ;

  }
    else
    {   Notification n("Echec de suppression ","Produit non supprimée");
        n.afficher();
    }
}


void MainWindow::on_pb_modifier_clicked() //modifier un produit
{
    int id =ui->l_idm->currentText().toInt();
    QString nom =ui->l_nomm->text();
    QDate date_p=ui->l_datem->date();
    int prix=ui->l_prixm->text().toInt();
    int quantite=ui->l_quantitem->text().toInt();

    Produits P2(id,nom,date_p,prix,quantite);
    if( nom.isEmpty() )
       {
        QMessageBox::critical(0,qApp->tr("Erreur!!"),qApp->tr("Veuillez remplir les champs vides."),QMessageBox::Cancel);
       }
    else
     {
      bool test=P2.modifier(P2);
       if (test)
       {
         Notification n("Modifié avec succés","Produit modifié");
         n.afficher();
         ui->tab_produit->setModel(P.afficher());

         ui->l_idm->clear();
         ui->l_nomm->clear();
         ui->l_datem->clear();
         ui->l_prixm->clear();
         ui->l_quantitem->clear();

         QSqlQueryModel * model2= new QSqlQueryModel();
         model2->setQuery("select id from produits")  ;
         ui->l_idm->setModel(model2) ;
         ui->l_id_sup->setModel(model2) ;


       }
     }

}

void MainWindow::on_l_idm_currentIndexChanged(const QString &arg1)
{
    int id=ui->l_idm->currentText().toInt();
    QSqlQuery query;
    query.prepare("select * from produits where id= :id ");
    query.bindValue(":id",id);
    if (query.exec())
    {
        while(query.next())
        {
            ui->l_nomm->setText(query.value(1).toString());
            ui->l_datem->setDate(query.value(2).toDate());
            ui->l_prixm->setText(query.value(3).toString());
            ui->l_quantitem->setText(query.value(4).toString());
        }
    }
}


void MainWindow::on_pb_import_image_clicked() //importation d'image
{
        QString filename = QFileDialog::getOpenFileName(this,tr("choose"),"",tr("Images(*.jpeg *jpg *.png *.bmp *.gif *.mp4)"));
        if (QString::compare(filename, QString()) !=0)
        {
            QImage image;
            bool valid = image.load(filename);
            if (valid)
            {
            image = image.scaledToWidth(ui->imag->width(), Qt::SmoothTransformation);
            ui->imag->setPixmap(QPixmap::fromImage(image));
            }
            else
            {
                ///error handling
            }
            }
}

void MainWindow::on_pb_supprimer_tout_clicked()
{
    bool test=P.supprimerTout();
    QMessageBox::StandardButton reply =QMessageBox::information(this,"Supprimer la liste","Etes-vous sur?",QMessageBox::Yes|QMessageBox::No);
   if(reply == QMessageBox::Yes)
   {
      if(test)
       {    Notification n("Supprimés avec succés","Tous les Produits sont supprimés");
         n.afficher();
         ui->tab_produit->setModel(P.afficher());      

       }
    else
        Notification n("Echec de suppression ","Produits non supprimés");
         n.afficher();
   }
}


void MainWindow::on_tri_nom_clicked()
{
     ui->tab_produit->setModel(P.trierN());
}

void MainWindow::on_tri_date_clicked()
{
     ui->tab_produit->setModel(P.trierD());
}

void MainWindow::on_tri_id_clicked()
{
    ui->tab_produit->setModel(P.trierID());
}





void MainWindow::on_pb_pdf_clicked()
{
    QPdfWriter pdf("C:/Users/Lenovo/Documents/2A/Projet QT/GestionDeProduits/pdf_produits.pdf");
    QPainter painter(&pdf);
    int i = 4000;
        painter.setPen(Qt::blue);
        painter.setFont(QFont("Georgia", 30));
        painter.drawText(2700,1600,"Tableau des Produits");
        painter.setPen(Qt::black);
        painter.setFont(QFont("Arial", 15));
        painter.drawPixmap(QRect(7900,10,1600,600),QPixmap("C:/Users/Lenovo/Documents/2A/Projet QT/GestionDeProduits/logo.png"));
        painter.drawPixmap(QRect(4,9,2100,2100),QPixmap("C:/Users/Lenovo/Documents/2A/Projet QT/GestionDeProduits/pro.jpg"));

        painter.drawRect(30,3000,7500,500);
        painter.setFont(QFont("Arial", 9));
        painter.drawText(500,3300,"Identifiant");
        painter.drawText(1400,3300,"Nom ");
        painter.drawText(2600,3300,"Date de Production");
        painter.drawText(4800,3300,"Prix");
        painter.drawText(5900,3300,"Quantité de produit ");



        QSqlQuery query;
                           query.prepare("<SELECT CAST( GETDATE() AS Date ) ");
                           time_t tt;
                           struct tm* ti;
                           time(&tt);
                           ti=localtime(&tt);
                           asctime(ti);
                           painter.drawText(7000,11000, asctime(ti));

        query.prepare("select * from produits");
        query.exec();
        while (query.next())
        {
            painter.drawText(500,i,query.value(0).toString());
            painter.drawText(1400,i,query.value(1).toString());
            painter.drawText(2600,i,query.value(2).toString());
            painter.drawText(4800,i,query.value(3).toString());
            painter.drawText(6200,i,query.value(4).toString());

          i = i + 500;
        }

        int reponse = QMessageBox::question(this, "Génerer PDF", "Vous voulez affichez le PDF ?", QMessageBox::Yes |  QMessageBox::No);
            if (reponse == QMessageBox::Yes)
            {   Notification n("Exportation avec succés","PDF Enregistré");
                n.afficher();
                QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/Lenovo/Documents/2A/Projet QT/GestionDeProduits/pdf_produits.pdf"));
            }
            if (reponse == QMessageBox::No)
            {
                 painter.end();
            }
}




void MainWindow::on_stat_clicked()
{
    statistiques *s = new statistiques();
    setWindowModality(Qt::WindowModal);
    s->show();
}


void MainWindow::on_rech_textEdited(const QString &arg1)//recherche avancee sans button
{

    QSqlQueryModel * model4= new QSqlQueryModel();
    QSqlQuery q;
    q.prepare("select * from PRODUITS WHERE ID like '%"+ui->rech->text()+"%' OR NOM like '%"+ui->rech->text()+"%' OR DATE_P like '%"+ui->rech->text()+"%' OR PRIX like '%"+ui->rech->text()+"%' OR QUANTITE like '%"+ui->rech->text()+"%'  ");
           P.rechercher(q) ;
           q.exec();
           model4->setQuery(q);
           ui->tab_produit->setModel(P.rechercher(q));//refresh


}



void MainWindow::on_refresh_mod_clicked()
{
    QSqlQueryModel * model2= new QSqlQueryModel();
    model2->setQuery("select *  from produits")  ;
    ui->l_idm->setModel(model2) ;
    ui->tab_produit->setModel(model2) ;
}
