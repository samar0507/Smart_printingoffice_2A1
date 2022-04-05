#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "commande.h"
#include "historique.h"
#include <QMessageBox>
#include"QIntValidator"
#include <QSqlQuery>
#include<QPainter>
#include<QPdfWriter>
#include<QDesktopServices>
#include<QUrl>
#include<QFile>
#include<QTextStream>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //QPixmap pix("C:\Users\ASUS\Desktop\bg.png")
    ui->le_idc_4->setValidator(new QIntValidator(0,9999,this));
    ui->le_idcl_3->setValidator(new QIntValidator(0,9999,this));
    ui->le_prix_3->setValidator(new QIntValidator(0,9999,this));
    ui->prix_3->setValidator(new QIntValidator(0,9999,this));
    ui->idcl_3->setValidator(new QIntValidator(0,9999,this));
    ui->chercher_3->setValidator(new QIntValidator(0,9999,this));
    ui->table_commande_3->setModel(c.afficher());
    //ui->del_id_4->setModel(c.afficher_id());
    //ui->tableView_3->setModel((c.afficher_id()));
    ui->table_histo->setModel(c.display_history());
}

MainWindow::~MainWindow()
{
    delete ui;
    ui->table_histo->setModel(c.display_history());

}

void MainWindow::on_add_btn_3_clicked()
{
    int idc=ui->le_idc_4->text().toInt();
      int idcl=ui->le_idcl_3->text().toInt();
        int prix=ui->le_prix_3->text().toInt();
        QDate date_c=ui->date_4->date();
        QString demande=ui->demande_4->text();
        QString idc1=ui->le_idc_4->text();
    commande c(idc,idcl,prix,date_c,demande);
bool test=c.ajouter();
bool addfile=c.history_file(idc,idcl,prix,date_c);
if(test&&addfile)

{   //REFRESH
    ui->table_commande_3->setModel(c.afficher());
    ui->tableView_3->setModel(c.afficher_id());
    ui->del_id_4->setModel(c.afficher_id());
    QMessageBox::information(nullptr, QObject::tr("OK"),
                QObject::tr("Ajout effectué\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
    QString nomFile ="file";
              QFile file("C:/Users/ASUS/Desktop/projet/copieee/copieee/historique.txt");
              QString finalmsg="fichier modifie avec succes";
               if(!file.exists()){
               finalmsg="fichier cree avec succes";
               }
              file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);



              QTextStream txt(&file);
                QString d_info = QDateTime::currentDateTime().toString();

              QString message2=d_info+" - Une commande a été ajoutée avec le idc "+idc1+"\n";
              txt << message2;
}
else
    QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                QObject::tr("Ajout non effectué\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}
void MainWindow::on_button_supprimer_3_clicked()
{
    commande c1; c1.setidc(ui->del_id_4->currentText().toInt());
    QString idc=ui->del_id_4->currentText();
    bool test=c1.supprimer(c1.getidc());
    QMessageBox msgBox;
    if(test)
    {   ui->table_commande_3->setModel(c.afficher());
        ui->tableView_3->setModel(c.afficher_id());
        //ui->update_id->setModel(c.afficher_id());
        ui->del_id_4->setModel(c.afficher_id());

        msgBox.setText("Suppression avec succes.");
        QString nomFile ="Historique";
                     QFile file("C:/Users/ASUS/Desktop/projet/copieee/copieee/historique.txt");
                     QString finalmsg="fichier modifie avec succes";
                      if(!file.exists()){
                      finalmsg="fichier cree avec succes";
                      }
                     file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);



                     QTextStream txt(&file);
                       QString d_info = QDateTime::currentDateTime().toString();

                      QString message2=d_info+" - Une commande a été supprimée avec le idc "+idc+" \n";
                     txt << message2;


    }
    else
        msgBox.setText("Echec de suppression.");
        msgBox.exec();
}
void MainWindow::on_button_modifier_3_clicked()
{int idc=ui->update_id_3->text().toInt();

    int idcl=ui->idcl_3->text().toInt();
      int prix=ui->prix_3->text().toInt();
      QDate date_c=ui->date_5->date();
      QString demande=ui->demande_5->text();
      QString id=ui->tableView_3->model()->data(ui->tableView_3->model()->index(ui->tableView_3->currentIndex().row(),0)).toString();
 commande c2(idc,idcl,prix,date_c,demande);
 bool test=c2.modifier();
 QMessageBox msgBox;
 if(test)
 {
    ui->table_commande_3->setModel(c.afficher());
    ui->tableView_3->setModel(c.afficher_id());
    ui->del_id_4->setModel(c.afficher_id());
    msgBox.setText("Modification avec succes.");

    QString nomFile ="Historique";
         QFile file("C:/Users/ASUS/Desktop/projet/copieee/copieee/historique.txt");
         QString finalmsg="fichier modifie avec succes";
          if(!file.exists()){
          finalmsg="fichier cree avec succes";
          }
         file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);



         QTextStream txt(&file);
           QString d_info = QDateTime::currentDateTime().toString();

         QString message2=d_info+" - Une commande a été modifiée avec le idc "+id+"\n";
         txt << message2;

 }
 else
     msgBox.setText("Echec de Modification.");
     msgBox.exec();

}

void MainWindow::on_tri_prix_3_clicked()
{
    ui->table_commande_3->setModel(c.tri_prix());
    ui->table_histo->setModel(c.display_history());
       QMessageBox::information(nullptr, QObject::tr("Ok"),
                QObject::tr("tri effectu.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}
void MainWindow::on_tri_idc_3_clicked()
{
    ui->table_commande_3->setModel(c.tri_idc());

    QMessageBox::information(nullptr, QObject::tr("Ok"),
             QObject::tr("tri effectu.\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);
}
void MainWindow::on_tri_date_3_clicked()
{
    ui->table_commande_3->setModel(c.tri_idc());
        QMessageBox::information(nullptr, QObject::tr("Ok"),
                 QObject::tr("tri effectu.\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);
}
void commande::rechercher(QTableView *table, int idc)
{
   /* int idc=ui->chercher_3->text().toInt();

    ui->table_commande_3->setModel(c.recherche(idc));
    //c.recherche(ui->table_commande_3,idc);
    QMessageBox::information(nullptr,QObject::tr("OK"),
                              QObject::tr("recherche effectue.\n"
                                          "clic cancel to exit."),QMessageBox::Cancel);*/
   /* ui->table_commande_3->setModel(c.afficher());
             int idc=ui->chercher_3->text().toInt();
             c.recherche(ui->table_commande_3,idc);*/
    QSqlQueryModel *model=new QSqlQueryModel();
       QSqlQuery *query =new QSqlQuery;
       query->prepare("select * from commande where regexp_like(idc,:idc);");
       query->bindValue(":idc",idc);

       if(idc==0)
       {
           query->prepare("select * from commande");
       }
       query->exec();
       model->setQuery(*query);
       table->setModel(model);
       table->show();
}

/*void MainWindow::on_tableView_activated(const QModelIndex &index)
{
    QSqlQuery query;
        QString idc=ui->tableView->model()->data(index).toString();
        query.prepare("select * from commande where idc='"+idc+"'");
        if(query.exec())
        {
            while (query.next())
            {
               // ui->update_id->setText(query.value(0).toString());
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
}*/

void MainWindow::on_tableView_3_activated(const QModelIndex &index)
{
    QSqlQuery query;
        QString idc=ui->tableView_3->model()->data(index).toString();

        query.prepare("select * from commande where idc='"+idc+"'");
        if(query.exec())
        {
            while (query.next())
            {
               // ui->update_id->setText(query.value(0).toString());
                ui->idcl_3->setText(query.value(1).toString());
                ui->prix_3->setText(query.value(2).toString());
                ui->date_5->setDate(query.value(3).toDate());
                ui->demande_5->setText(query.value(4).toString());
            }
         }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("Failed"),
                            QObject::tr("Impossible.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
            }
}

void MainWindow::on_PDF_clicked()
{
    //QPdfWriter pdf("C:/Users/ASUS/Desktop/copieee/Commande.pdf");
    QPdfWriter pdf("C:/Users/ASUS/Desktop/projet/copieee/copieee/Commande.pdf");


    QPainter painter(&pdf);
    const QImage image("C:/Users/ASUS/Desktop/projet/copieee/copieee/logo.png");
            const QPoint imageCoordinates(0,0);
            painter.drawImage(imageCoordinates,image);

    int i = 4000;
    painter.setPen(Qt::blue);
    painter.setFont(QFont("Arial", 30));
    painter.drawText(3000,1500,"LISTE DES COMMANDES");
    painter.setPen(Qt::black);
   // painter.setFont(QFont("Arial", 50));
    // painter.drawText(1100,2000,afficheDC);
    painter.drawRect(2700,200,7300,2600);
    painter.drawRect(0,3000,9600,500);
    painter.setFont(QFont("Arial", 9));
    painter.drawText(300,3300,"Identifiant Commande");
    painter.drawText(2300,3300,"Identifiant Client");
    painter.drawText(4300,3300,"Prix");
    painter.drawText(6300,3300,"Date Commande");
    painter.drawText(8000,3300,"Demande");
    QSqlQuery query;
    query.prepare("select * from COMMANDE");
    query.exec();
    while (query.next())
    {
        painter.drawText(300,i,query.value(0).toString());
        painter.drawText(2300,i,query.value(1).toString());
        painter.drawText(4300,i,query.value(2).toString());
        painter.drawText(6300,i,query.value(3).toString());
        painter.drawText(8000,i,query.value(4).toString());
        i = i +500;
    }

    int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/ASUS/Desktop/projet/copieee/copieee/Commande.pdf"));

        painter.end();
    }
    if (reponse == QMessageBox::No)
    {
        painter.end();
    }
}




void MainWindow::on_pushButton_clicked()
{
    ui->table_histo->setModel(c.display_history());


}

void MainWindow::on_pushButton_2_clicked()
{
    QString month=ui->comboBox->currentText();
    ui->table_histo_2->setModel(c.calcul(month));
}

void MainWindow::on_tabWidget_4_currentChanged(int index)
{
    ui->table_commande_3->setModel(c.afficher());

        QSqlQueryModel *modal=new QSqlQueryModel;
        QSqlQuery *qry=new QSqlQuery;
        qry->prepare("select idc from commande");
        qry->exec();
        modal->setQuery(*qry);
        ui->del_id_4->setModel(modal);

        ui->tableView_3->setModel(modal);
}

void MainWindow::on_chercher_3_textChanged(const QString &arg1)
{
    c.clear_commande(ui->table_commande_3);
                int idc=ui->chercher_3->text().toInt();
                c.rechercher(ui->table_commande_3,idc);
}
