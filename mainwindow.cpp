#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include "humidite.h"
#include "connection.h"
#include "arduino.h"
#include "produits.h"
#include "statistiques.h"
#include "notification.h"
#include "employes.h"
#include "commande.h"
#include "fournisseurs.h"
#include "rfid.h"
#include "smtp.h"

#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include <QObject>
#include<ctime>
#include <QTcpSocket>
#include <QDebug>
#include <QLineEdit>
#include <QMessageBox>
#include <QIntValidator>
#include <qrcode.h>
#include<QFile>
#include<QFileDialog>
#include<QSvgRenderer>
#include <QTextDocument>
#include <QPainter>
#include <QTextStream>
#include <QPdfWriter>
#include <string>
#include <QSqlError>
#include <vector>
#include<QDirModel>
#include <string>
#include <iostream>
#include <fstream>
#include <QtSvg/QSvgRenderer>
#include <QTabWidget>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDesktopServices>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include<QPixmap>
#include <QPrintDialog>
#include<QPrinter>
#include <QTextTableCell>
#include <QSerialPort>
#include <QSerialPortInfo>
#include<QPainter>
#include<QDesktopServices>
#include<QUrl>
#include <QtWidgets>
#include <QPlainTextEdit>
#include <QPrinterInfo>
#include <QTextStream>
#include <QTextStream>
#include<QPdfWriter>

using qrcodegen::QrCode;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   centralWidget()->setStyleSheet("{background-image:url(qrc:/img/img/djjjj.jpg)}");
    //////////////////////Fournisseurs/////////////////////

   ui->id_add->setValidator(new QIntValidator(0,9999999,this));
   ui->tab_frnss->setModel(f.afficher());
   ui->del_id_5->setModel(f.load());
   ui->id_tab->setModel(f.afficher_id());
   ui->id_tab->setModel(f.afficher_id());
   connect(ui->envoyer_btn, SIGNAL(clicked()),this, SLOT(sendMail()));
   connect(ui->quitter_btn, SIGNAL(clicked()),this, SLOT(close()));
   connect(ui->parcourir_btn, SIGNAL(clicked()), this, SLOT(browse()));

   int ret=A.connect_arduino();
   switch(ret){
   case(0):qDebug()<< "arduino is available and is connected to : "<<Ar.getArduino_port_name();
       break;
   case(1):qDebug()<<"arduino is available but not connected to : "<<Ar.getArduino_port_name();
       break;
   case(-1):qDebug()<<"arduino is not available";
   }
   QObject::connect(Ar.getSerial(), SIGNAL(readyRead()), this, SLOT(update_label_uid()));
   //////////////////////////Client///////////////////////////
    ui->lineEdit_cin->setValidator(new QIntValidator(0,99999999,this));
        mCamera = new QCamera(this);
     mQCameraViewfinder = new QCameraViewfinder(this);
      mQCameraImageCapture = new QCameraImageCapture(mCamera,this);
      mLayout =new QVBoxLayout;
      mOptionsMenu = new QMenu("Ouvrir Cam",this);
      mCamera->setViewfinder(mQCameraViewfinder);
      mEncenderAction =new QAction("Ouvrir Cam",this);
      mApAction =new QAction("Stop Camera",this);
      mCaptureAction =new QAction("Capture image",this);
      mOptionsMenu->addActions({mEncenderAction,mApAction,mCaptureAction});
      ui->cam->setMenu(mOptionsMenu);
      mLayout->addWidget(mQCameraViewfinder);
      mLayout->setMargin(0);
      ui->scrollArea->setLayout(mLayout);
      connect(mEncenderAction,&QAction::triggered,[&](){
          mCamera->start();
      });
      connect(mApAction,&QAction::triggered,[&](){
          mCamera->stop();
      });
connect(mCaptureAction,&QAction::triggered,[&](){
   auto filename =QFileDialog ::getSaveFileName(this,"Capturer","/","Image(*.jpg;*.jpeg)");
   if(filename.isEmpty()){
       return;
   }
           mQCameraImageCapture->setCaptureDestination(QCameraImageCapture::CaptureToFile);
    QImageEncoderSettings ImageEncoderSettings;
    ImageEncoderSettings.setCodec("image/jpeg");
    ImageEncoderSettings.setResolution(1600,1200);
    mQCameraImageCapture->setEncodingSettings(ImageEncoderSettings);
    mCamera->setCaptureMode(QCamera::CaptureStillImage);
    mCamera->start();
    mQCameraImageCapture->capture(filename);
    mCamera->unlock();
});

ui->tab_cl->setModel(cl.afficher());

 /////////////////////////Produits////////////////////////

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



//ui->id->setValidator(new QIntValidator(0,9999999,this));
ui->tab_employes->setModel(e.afficher());
ui->tab_id_2->setModel((e.afficher_id()));
mSocket=new QTcpSocket(this);
mSocket->connectToHost("localhost",2000);
if (mSocket->waitForConnected(3000))
{
    ui->plainTextEdit->appendPlainText("se connecter correctement");
}
else
{
    ui->plainTextEdit->appendPlainText("pas de connexion");
}
connect(mSocket,SIGNAL(readyRead()),this,SLOT(leer()));

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
}


void MainWindow::on_g_client_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->client);
}

void MainWindow::on_pushButton_21_clicked()
{
   ui->stackedWidget->setCurrentWidget(ui->menu);
}

void MainWindow::on_pushButton_27_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->menu);
}

void MainWindow::on_pushButton_25_clicked()
{
  ui->stackedWidget->setCurrentWidget(ui->menu);
}

void MainWindow::on_ajout_cl_clicked()
{
    int cin = ui->lineEdit_cin->text().toInt();
    QString nom=ui->lineEdit_nom->text();
    QDate date_naissance = ui->dateEdit->date();
    QString adresse=ui->lineEdit_adresse->text();
      QString prenom=ui->lineEdit_prenom->text();

      QString res =QString ::number(cin);
      QString qrlink="C:/Users/21697/OneDrive/Documents/build-clients-Desktop_Qt_5_9_9_MinGW_32bit-Release/QRCode/"+res;
      client cl(cin,date_naissance,nom,prenom,adresse,qrlink);
      if(cin!=0 && nom!=""  && prenom!="" && adresse!="")
      {
       bool test=cl.ajouter();
       if(test)
       {
           Notification n("Ajouté avec succés","Client ajouté");
           n.afficher();
           ui->tab_cl->setModel(cl.afficher());//refresh

           ui->lineEdit_cin->clear();
           ui->lineEdit_nom->clear();
           ui->lineEdit_prenom->clear();
           ui->dateEdit->clear();
           ui->lineEdit_adresse->clear();

              }
       Notification n("Echec d'ajout ","Client non ajouté");
                  n.afficher();
       }
}

void MainWindow::on_modif_cl_clicked()
{
    int cin = ui->lineEdit_cin_2->text().toInt();
    QString nom=ui->lineEdit_nom_2->text();
    QDate date_naissance = ui->dateEdit_2->date();
    QString adresse=ui->lineEdit_adresse_2->text();
      QString prenom=ui->lineEdit_prenom_2->text();
      QString res =QString ::number(cin);
       QString qrlink="C:/Users/21697/OneDrive/Documents/build-clients-Desktop_Qt_5_9_9_MinGW_32bit-Release/QRCode/"+res;
      client cl(cin,date_naissance,nom,prenom,adresse,qrlink);
      if(cin!=0 && nom!="" && prenom!="" && adresse!="")
      {
      bool test=cl.modifier(cin);
      if(test)
      {
          Notification n("Modifié avec succés","Client ajouté");
          n.afficher();
          ui->tab_cl->setModel(cl.afficher());//refresh
          ui->lineEdit_cin_2->clear();
          ui->lineEdit_nom_2->clear();
          ui->lineEdit_prenom_2->clear();
          ui->dateEdit_2->clear();
          ui->lineEdit_adresse_2->clear();



      }
        else
          Notification n("Echec de modification  ","Client non modifié");
                     n.afficher();
      }

}

void MainWindow::on_lineEdit_search_cl_cursorPositionChanged(int arg1, int arg2)
{
    int cin = ui->lineEdit_search_cl->text().toInt();
     QString nom=ui->lineEdit_search_cl->text();
     QString prenom=ui->lineEdit_search_cl->text();
    if(arg2!= 0)
    {
    ui->tab_cl->setModel(cl.affichersearch(cin,nom,prenom));
    }
    else{
ui->tab_cl->setModel(cl.afficher());
    }
}

void MainWindow::on_excel_cl_clicked()
{
    QTableView *table;
       table = ui->tab_cl;

       QDateTime date = QDateTime::currentDateTime();
       QString formattedTime = date.toString("dd.MM.yyyy hh:mm:ss");
       QString d="excel/list "+formattedTime;
       QString filters("xls files (*.xls);;All files (*.*)");
       QString defaultFilter("xls files (*.xls)");
       QString fileName = QFileDialog::getSaveFileName(0, "Save file",d,
                          filters, &defaultFilter);
       QFile file(fileName);
       QAbstractItemModel *model =  table->model();
       if (file.open(QFile::WriteOnly | QFile::Truncate)) {
           QTextStream data(&file);
           QStringList strList;
           for (int i = 0; i < model->columnCount(); i++) {
               if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                  { strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
strList.append("\t");}
               else
                   strList.append("");
           }
           data << strList.join("") << "\n";
           for (int i = 0; i < model->rowCount(); i++) {
               strList.clear();
               for (int j = 0; j < model->columnCount(); j++) {

                   if (model->data(model->index(i, j)).toString().length() > 0)
                      { strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                   strList.append("\t");}
                   else
                       strList.append("");

               }
               data << strList.join("") + "\n";
           }
           file.close();
           Notification n("Exporter To Excel","Exporter En Excel Avec Succées");
           n.afficher();

       }
}

void MainWindow::on_supp_cl_clicked()
{
    if(ui->tab_cl->currentIndex().row()==-1)
                  QMessageBox::information(nullptr, QObject::tr("Suppression"),
                                           QObject::tr("Veuillez Choisir un client du Tableau.\n"
                                                       "Click Ok to exit."), QMessageBox::Ok);
              else
              {
                   int cin=ui->tab_cl->model()->data(ui->tab_cl->model()->index(ui->tab_cl->currentIndex().row(),0)).toInt();
    bool test=cl.supprimer(cin);
    if(test)
    { ui->tab_cl->setModel(cl.afficher());//refresh
       ui->lineEdit_search_cl->clear();

       Notification n("Supprimé avec succés","Client supprimé");
       n.afficher();
           }
               else
        Notification n("Echec de suppression ","Client non supprimés");
         n.afficher();


}
}

void MainWindow::on_fidelite_clicked()
{
    if(ui->tab_cl->currentIndex().row()==-1)
                  QMessageBox::information(nullptr, QObject::tr("PDF"),
                                           QObject::tr("Veuillez Choisir un client du Tableau.\n"
                                                       "Click Ok to exit."), QMessageBox::Ok);
              else
              {
        int cin=ui->tab_cl->model()->data(ui->tab_cl->model()->index(ui->tab_cl->currentIndex().row(),0)).toInt();
         QString res=QString::number(cin);
        QSqlDatabase db;
                            QTableView TableView_Client;
                            QSqlQueryModel * Modal=new  QSqlQueryModel();

                            QSqlQuery qry;
                             qry.prepare("SELECT * FROM client where cin like  '%"+res+"%';");
                             qry.exec();
                             Modal->setQuery(qry);
                             TableView_Client.setModel(Modal);
                             db.close();
                             QString strStream;
                             QTextStream out(&strStream);
                                                  QTextDocument *document = new QTextDocument();
                                                  document->setHtml(strStream);
                                          QString c ="Fidelite/Carte fidelite  "+res;
                             QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", c, "*.pdf");
                                                     if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

                                                    QPrinter printer (QPrinter::PrinterResolution);
                                                     printer.setOutputFormat(QPrinter::PdfFormat);

                                                     QPdfWriter pdfWriter(fileName);
                                                    pdfWriter.setPageSize(QPageSize(QPageSize::B8));
                                                   QString qrid="QRCode/"+res;
                                                   QPainter painter(&pdfWriter);

                                                     painter.drawPixmap(QRect(0,0,pdfWriter.logicalDpiX()*2.1,pdfWriter.logicalDpiY()*1.1),QPixmap("../clients/2.jpg"));
                                                      painter.drawPixmap(QRect(2280,1080,pdfWriter.logicalDpiX()*0.17,pdfWriter.logicalDpiY()*0.17),QPixmap(qrid));
                                                     pdfWriter.newPage();
                                                     painter.drawPixmap(QRect(0,0,pdfWriter.logicalDpiX()*2.1,pdfWriter.logicalDpiY()*1.1),QPixmap("../clients/1.jpg"));



    }
}

void MainWindow::on_qrcode_cl_clicked()
{
    if(ui->tab_cl->currentIndex().row()==-1)
                  QMessageBox::information(nullptr, QObject::tr("QrCode"),
                                           QObject::tr("Veuillez Choisir un client du Tableau.\n"
                                                       "Click Ok to exit."), QMessageBox::Ok);
              else
              {
                   int id=ui->tab_cl->model()->data(ui->tab_cl->model()->index(ui->tab_cl->currentIndex().row(),0)).toInt();
                   const QrCode qr = QrCode::encodeText(std::to_string(id).c_str(), QrCode::Ecc::LOW);
                   std::ofstream myfile;
                   myfile.open ("qrcode.svg") ;
                   myfile << qr.toSvgString(1);
                   myfile.close();
                   QSvgRenderer svgRenderer(QString("qrcode.svg"));
                   QPixmap pix( QSize(90, 90) );
                   QPainter pixPainter( &pix );
                   svgRenderer.render( &pixPainter );
                   ui->label_qr->setPixmap(pix);
                   QString s = QString::number(id);
                  QString qrid="QRCode/"+s;
                   QString fileName = QFileDialog::getSaveFileName(this, tr("Save QRCode"),
                                                                 qrid,
                                                                   tr("qrcode (*.png)"));
                   if (!fileName.isEmpty())
                   {
                     pix.save(fileName);
                   }

              }
}

void MainWindow::on_tab_cl_activated(const QModelIndex &index)
{
    QString val=ui->tab_cl->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("select * from client where cin ='"+val+"';");
    if (qry.exec())
    {
        while(qry.next())
        {
            ui->lineEdit_cin_2->setText(qry.value(0).toString());
            ui->lineEdit_nom_2->setText(qry.value(1).toString());
            ui->lineEdit_prenom_2->setText(qry.value(2).toString());
            ui->lineEdit_adresse_2->setText(qry.value(3).toString());
            ui->dateEdit_2->setDate(qry.value(4).toDate());

            ui->tab2->setCurrentWidget(ui->tab);
         }
    }
    else
    {
        QMessageBox::critical(this,tr("error"),qry.lastError().text());
    }
}

  /////////////////////////////////////////////produits
void MainWindow::on_g_produit_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->produit);

}

void MainWindow::on_pb_ajouter_clicked()//ajouter un produit
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

void MainWindow::on_pb_modifier_clicked()//modifier un produit
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
       else
       {   Notification n("Echec de modification ","Produit non modifié");
           n.afficher();
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

void MainWindow::on_pb_supprimer_clicked()//supprimer un produit
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



void MainWindow::on_pb_import_image_clicked()//importation d'image
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

void MainWindow::on_pb_supprimer_tout_clicked()//supprimer tout les produits
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

void MainWindow::on_pb_pdf_clicked() //pdf produits
{
    QPdfWriter pdf("pdf_produits.pdf");
    QPainter painter(&pdf);
    int i = 4000;
        painter.setPen(Qt::blue);
        painter.setFont(QFont("Georgia", 30));
        painter.drawText(2700,1600,"Tableau des Produits");
        painter.setPen(Qt::black);
        painter.setFont(QFont("Arial", 15));
        painter.drawPixmap(QRect(7900,10,1600,600),QPixmap(":/new/prefix1/logo.png"));
        painter.drawPixmap(QRect(4,9,2100,2100),QPixmap(":/new/prefix1/pro.jpg"));

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
                QDesktopServices::openUrl(QUrl::fromLocalFile("pdf_produits.pdf"));
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

void MainWindow::on_buttonon_clicked()
{
    A.write_to_arduino("1"); //envoyer 1 à arduino
    ui->label_etat->setText("ON");
}

void MainWindow::on_buttonoff_clicked()
{
    A.write_to_arduino("0"); //envoyer 0 à arduino
    ui->label_etat->setText("OFF");
}
void MainWindow::update_label()
{
 QByteArray sr=A.read_from_arduino();
 QString b= QString(sr);
  QStringList bb = b.split(",");
 int hum = bb[0].toInt();

 if(hum == 70)
 {
     connection c;
     c.createconnect();
QDateTime date = QDateTime::currentDateTime();
humidite h (date);
bool test=h.ajouter();
 }
qDebug () << hum;
ui->Hum->display(b);

alert=hum;

if (alert>60)
{
    ui->label_alert->setText("Taux d'humidite élevè!!!");
}
else {
     ui->label_alert->setText(" ");
}

 }





void MainWindow::on_pushButton_32_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->menu);

}

void MainWindow::on_pushButton_33_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->menu);

}

void MainWindow::on_pushButton_34_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->menu);

}

void MainWindow::on_pushButton_35_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->menu);

}

void MainWindow::on_pushButton_36_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->menu);

}

void MainWindow::on_g_emp_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->employe);
}
void MainWindow::on_add_btn_clicked()
{
    int id=ui->id->text().toInt();
        QString nom=ui->nom->text();
        QString prenom=ui->per->text();
        QDate date_naiss=ui->date->date();
        QString pass= ui->fonc->text();
        employes e(id,nom,prenom,date_naiss,pass);
        bool test=e.ajouter();
        if(test)
        {
            //REFRESH
            ui->tab_employes->setModel(e.afficher());
            ui->tab_id_2->setModel(e.afficher_id());
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
    int id=ui->combo->currentText().toInt();
         bool test=e.supprimer(id);
         if(test)
         {
             //REFRESH
             ui->tab_employes->setModel(e.afficher());
             ui->tab_id_2->setModel(e.afficher_id());
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
    int id=ui->update_id->text().toInt();
           QString nom=ui->nom_mod->text();
           QString prenom=ui->per_mod->text();
           QDate date_naiss=ui->date_mod->date();
           QString pass=ui->fonc_mod->text();
        bool test=e.modifier(id,nom,prenom,date_naiss,pass);
        if(test)
        {
            //REFRESH
            ui->tab_employes->setModel(e.afficher());
            ui->tab_id_2->setModel(e.afficher_id());
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
QSqlQueryModel*  employes ::afficher_id()
{ QSqlQueryModel *model=new QSqlQueryModel();
model->setQuery("select id from employes");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
return model;
}
void MainWindow::on_load_butt_clicked()
{
    QSqlQueryModel* modal= new QSqlQueryModel();
       modal->setQuery("SELECT id  FROM employes");
       ui->combo->setModel(modal);
}
void MainWindow::on_tab_id_2_activated(const QModelIndex &index)
{
        QSqlQuery query;
        QString id=ui->tab_id_2->model()->data(index).toString();
        query.prepare("select * from employes where id='"+id+"'");
        if(query.exec())
        {
            while (query.next())
            {
                ui->update_id->setText(query.value(0).toString());
                ui->nom_mod->setText(query.value(1).toString());
                ui->per_mod->setText(query.value(2).toString());
                ui->date_mod->setDate(query.value(3).toDate());
                ui->fonc_mod->setText(query.value(4).toString());
            }
         }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("Failed"),
                            QObject::tr("Impossible.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
            }
}
/*commande*/
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
              QFile file("C:/Users/ASUS/Desktop/Integration QT/sans ghada (1)/nour+sirine/historique.txt");
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
                     QFile file("C:/Users/ASUS/Desktop/Integration QT/sans ghada (1)/nour+sirine/historique.txt");
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
         QFile file("C:/Users/ASUS/Desktop/Integration QT/sans ghada (1)/nour+sirine/historique.txt");
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

void MainWindow::on_g_comm_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->commande);
}




void MainWindow::on_qr_clicked()
{
    if(ui->tab_employes->currentIndex().row()==-1)
                   QMessageBox::information(nullptr, QObject::tr("QrCode"),
                                            QObject::tr("Veuillez Choisir un client du Tableau.\n"
                                                        "Click Ok to exit."), QMessageBox::Ok);
               else
               {
                    int id=ui->tab_employes->model()->data(ui->tab_employes->model()->index(ui->tab_employes->currentIndex().row(),0)).toInt();
                    const QrCode qr = QrCode::encodeText(std::to_string(id).c_str(), QrCode::Ecc::LOW);
                    std::ofstream myfile;
                    myfile.open ("qrcode.svg") ;
                    myfile << qr.toSvgString(1);
                    myfile.close();
                    QSvgRenderer svgRenderer(QString("qrcode.svg"));
                    QPixmap pix( QSize(90, 90) );
                    QPainter pixPainter( &pix );
                    svgRenderer.render( &pixPainter );
                    ui->label_qr_2->setPixmap(pix);


               }
}

void MainWindow::on_insertion_photo_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this,tr("choose"),"",tr("Image(*.png *.jpeg *.jpg *.bmp *.gif)"));
    if (QString::compare(filename,QString()) !=0)
    {
        QImage image;
        bool valid = image.load(filename);
        if(valid)
        {
            image=image.scaledToWidth(ui->img_label->width(), Qt::SmoothTransformation);
                    ui->img_label->setPixmap(QPixmap::fromImage(image));

        }

     }
}
void MainWindow::leer()
{
    QByteArray buffer;
    buffer.resize(mSocket->bytesAvailable());
    mSocket->read(buffer.data(),buffer.size());
    ui->plainTextEdit->setReadOnly(true);
    ui->plainTextEdit->appendPlainText(QString(buffer));
}
void MainWindow::on_CHAT_clicked()
{
    mSocket->write(ui->lineEdit->text().toLatin1().data(),ui->lineEdit->text().size());
    ui->plainTextEdit->appendPlainText(ui->lineEdit->text());
    ui->lineEdit->clear();
}

void MainWindow::on_ard_clicked()
{
    di = new dialog(this);
               di->show();
}

/*SqlQueryModel * employes::tri_fonc()
{   QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from employes order by fonc");
    return model;}

void MainWindow::on_tri_resp_clicked()
{

    QMessageBox::information(nullptr, QObject::tr("Ok"),
             QObject::tr("tri effectué avec succès.\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);
    ui->tab_employes->setModel(e.tri_fonc());
}*/
QSqlQueryModel * employes::tri_nom()
{   QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from employes order by nom");
    return model;}
void MainWindow::on_tri_nom2_clicked()
{

    QMessageBox::information(nullptr, QObject::tr("Ok"),
             QObject::tr("tri effectué avec succès.\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);
    ui->tab_employes->setModel(e.tri_nom());
}
QSqlQueryModel * employes::tri_prenom()
{   QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from employes order by prenom");
    return model;}
void MainWindow::on_tri_prenom_clicked()
{
    QMessageBox::information(nullptr, QObject::tr("Ok"),
             QObject::tr("tri effectué avec succès.\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);
    ui->tab_employes->setModel(e.tri_prenom()); }
void employes::rechercher(QTableView *table, int id)
{
   QSqlQueryModel *model=new QSqlQueryModel();
   QSqlQuery *query =new QSqlQuery;
   query->prepare("select * from employes where regexp_like(id,:id);");
   query->bindValue(":id",id);

   if(id==0)
   {
       query->prepare("select * from employes");
   }
   query->exec();
   model->setQuery(*query);
   table->setModel(model);
   table->show();
}
void MainWindow::on_cherche_textChanged(const QString &arg1)
{
    e.clear_employes(ui->tab_employes);
            int id=ui->cherche->text().toInt();
            e.rechercher(ui->tab_employes,id);
}

void MainWindow::on_ara_clicked()
{

    di = new dialog(this);
               di->show();
}
bool commande::history_file(int idc,int idcl, int prix,QDate date_c)
{
    QFile file("C:/Users/ASUS/Desktop/Integration QT/sans ghada (1)/nour+sirine/histo.txt");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        qCritical() << file.errorString();
        return false;
    }
    QTextStream stream(&file);
    stream <<idc << "\t" <<idcl << "\t" <<prix << "\t" << "\n" ;
    file.close();
    QSqlQuery query;
    query.prepare("INSERT INTO HISTORIQUE (IDCMD,IDCT, PRIX,DATEE) "
                        "VALUES (:idc, :idcl, :prix, :date_c)");
          query.bindValue(0, idc);
          query.bindValue(1, idcl);
          query.bindValue(2, prix);
          query.bindValue(3, date_c);

          return  query.exec();
}

QSqlQueryModel* commande::display_history()
{
        QSqlQueryModel* model=new QSqlQueryModel();
        model->setQuery("SELECT * FROM HISTORIQUE");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant Commande"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Identifiant Client"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prix"));
        return model;
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->table_histo->setModel(c.display_history());
}

void MainWindow::on_PDF_clicked()
{
    //QPdfWriter pdf("C:/Users/ASUS/Desktop/copieee/Commande.pdf");
    QPdfWriter pdf("C:/Users/ASUS/Desktop/Integration QT/sans ghada (1)/nour+sirine/commande.pdf");


    QPainter painter(&pdf);
    const QImage image("C:/Users/nourb/OneDrive/Bureau/atconnex/nour+sirine/logo.png");
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
        QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/nourb/OneDrive/Bureau/atconnex/nour+sirine/commande.pdf"));

        painter.end();
    }
    if (reponse == QMessageBox::No)
    {
        painter.end();
    }
}
QSqlQueryModel* commande::calcul (QString mm)
{
        QSqlQueryModel* model=new QSqlQueryModel();
        model->setQuery("select sum(PRIX),COUNT(*) from ( SELECT * FROM HISTORIQUE WHERE TO_CHAR(datee,'MM') = "+mm+" );");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Chiffre d'aff"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nbr Commande"));
        return model;
}
void commande::clear_commande(QTableView *table)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->clear();
    table->setModel(model);
}

void MainWindow::on_tabWidget_4_currentChanged(int index)
{
    ui->table_commande_3->setModel(c.afficher());
    ui->table_histo->setModel(c.display_history());
}

void MainWindow::on_pushButton_4_clicked()
{
    QString month=ui->comboBox->currentText();
    ui->table_histo_2->setModel(c.calcul(month));
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
void MainWindow::on_chercher_3_textChanged(const QString &arg1)
{
    c.clear_commande(ui->table_commande_3);
                int idc=ui->chercher_3->text().toInt();
                c.recherche(ui->table_commande_3,idc);
}


//////////////////////////////Fournisseurssss//////////////////////////////
void MainWindow::on_g_four_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->Fournisseurs);
}

void MainWindow::on_btn_add_clicked()
{
    //récupération des informations saisies
    int id=ui->id_add->text().toInt();
    QString nom=ui->nom_add->text();
    QDate date_deb=ui->deb_add->date();
    QDate date_fin=ui->fin_add->date();
    QString adresse= ui->adresse_add->text();
    QString rfid= ui->rfid_add->currentText();
    fournisseurs f(id,nom,date_deb,date_fin,adresse,rfid);
    bool test=f.ajouter();
    if(test)
    {
        //REFRESH
        ui->tab_frnss->setModel(f.afficher());
        ui->id_tab->setModel(f.load());
        ui->del_id_5->setModel(f.load());
        ui->tab_id_2->setModel(f.afficher_id());
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

void MainWindow::on_tri_pr_nom_clicked()
{
    ui->tab_frnss->setModel(f.tri_nom());
        QMessageBox::information(nullptr, QObject::tr("Ok"),
                 QObject::tr("tri effectué.\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_tri_pr_id_clicked()
{
    ui->tab_frnss->setModel(f.tri_id());
        QMessageBox::information(nullptr, QObject::tr("Ok"),
                 QObject::tr("tri effectué.\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_tri_pr_fin_clicked()
{
    ui->tab_frnss->setModel(f.tri_date_fin());
        QMessageBox::information(nullptr, QObject::tr("Ok"),
                 QObject::tr("tri effectué.\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);
}


void MainWindow::on_tri_pr_deb_clicked()
{
    ui->tab_frnss->setModel(f.tri_date_deb());
        QMessageBox::information(nullptr, QObject::tr("Ok"),
                 QObject::tr("tri effectué.\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_search_id_textChanged(const QString &arg1)
{
    f.clear_fournisseurs(ui->tab_frnss);
            int id=ui->search_id->text().toInt();
            f.rechercher(ui->tab_frnss,id);

}


void MainWindow::on_btn_del_clicked()
{
    int id=ui->del_id_5->currentText().toInt();
     bool test=f.supprimer(id);
     if(test)
     {
         //REFRESH
         ui->tab_frnss->setModel(f.afficher());
         //ui->tab_id_2->setModel(f.load());
         ui->del_id_5->setModel(f.load());
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


void MainWindow::on_btn_del_all_clicked()
{
    bool test=f.supprimerTout();
    if(test)
    {
        //REFRESH
        ui->tab_frnss->setModel(f.afficher());
        //ui->tab_id_2->setModel(f.load());
        ui->del_id_5->setModel(f.load());
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

void MainWindow::on_id_tab_activated(const QModelIndex &index)
{
    QSqlQuery query;
    QString id=ui->id_tab->model()->data(index).toString();
    query.prepare("select * from fournisseurs where id='"+id+"'");
    if(query.exec())
    {
        while (query.next())
        {
            ui->update_id->setText(query.value(0).toString());
            ui->nvNom->setText(query.value(1).toString());
            ui->nvDebut->setDate(query.value(2).toDate());
            ui->nvFin->setDate(query.value(3).toDate());
            ui->nvAdresse->setText(query.value(4).toString());
            ui->nvRfid->setCurrentText(query.value(5).toString());
        }
     }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Failed"),
                        QObject::tr("Impossible.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
}

void MainWindow::on_btn_update_clicked()
{
    //récupération des informations saisies
    int id=ui->nvID->text().toInt();
       QString nom=ui->nvNom->text();
       QDate date_deb=ui->nvDebut->date();
       QDate date_fin=ui->nvFin->date();
       QString adresse=ui->nvAdresse->text();
       QString rfid=ui->nvRfid->currentText();
    bool test=f.modifier(id,nom,date_deb,date_fin,adresse,rfid);
    if(test)
    {
        //REFRESH
        ui->tab_frnss->setModel(f.afficher());
        ui->id_tab->setModel(f.load());
        ui->del_id_5->setModel(f.load());
        ui->tab_id_2->setModel(f.afficher_id());
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

void MainWindow::on_btn_browse_clicked()
{
    QString filename= QFileDialog::getOpenFileName(this, tr("Choose"),"",tr("Images (*.png *.jpg *.jpeg *.bmp *.gif)"));
    if(QString::compare(filename, QString())!=0)
    {
        QImage image;
        bool valid =image.load(filename);
        if(valid)
        {
            image= image.scaledToWidth(ui->img_add->width(), Qt::SmoothTransformation);
            ui->img_add->setPixmap(QPixmap::fromImage(image));
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Failed"),
                        QObject::tr("Impossible d'inserer l'image.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
    }
}
void MainWindow::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file_3->setText( fileListString );

}

void MainWindow::sendMail()
{
    Smtp* smtp = new Smtp(ui->uname_3->text(), ui->paswd_3->text(), ui->server_3->text(), ui->port_3->text().toInt());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail(ui->uname_3->text(), ui->rcpt_3->text() , ui->subject_3->text(),ui->msg_3->toPlainText(), files );
    else
        smtp->sendMail(ui->uname_3->text(), ui->rcpt_3->text() , ui->subject_3->text(),ui->msg_3->toPlainText());
}

void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}



void MainWindow::on_fournisseurs1_3_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.usinenouvelle.com/expo/"));
}

void MainWindow::on_fournisseurs2_3_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.companeo.com/"));
}

void MainWindow::on_fournisseurs3_3_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.affariyet.com/"));
}

void MainWindow::on_fournisseurs4_3_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.tunisianet.com.tn/"));
}

void MainWindow::on_fournisseurs5_3_clicked()
{
    QDesktopServices::openUrl(QUrl("https://print-value.fr/"));
}
void MainWindow::update_label_uid()
{
    data.append(Ar.read_from_arduino());
if(data.length()==11){
    QString message="";
    if (f.rechCarte(data) )
       { QSqlQuery q("select * from fournisseurs where rfid='"+data+"'");
        while (q.next()) {

            message="Le fournisseurs de rfid "+q.value(5).toString()+" existe dans notre base de données";
}

       /* QMessageBox::information(nullptr, QObject::tr(""),
         QObject::tr(message"click cancel to exit . ") , QMessageBox::Cancel);*/
        QMessageBox::information(this,"Fournisseurs existant " , message,QMessageBox::Ok);
         Ar.write_to_arduino("1");


    data.clear();
        }
    else
    {    QMessageBox::critical(nullptr, QObject::tr("Fournisseur n'existe pas"),
         QObject::tr("Fournisseur n'existe pas.\n"
                     "click cancel to exit . ") , QMessageBox::Cancel);
        Ar.write_to_arduino("0");

    data.clear();
    }
}

}

void MainWindow::on_pushButton_29_clicked()
{
      ui->stackedWidget->setCurrentWidget(ui->menu);
}

void MainWindow::on_pushButton_28_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->menu);
}

void MainWindow::on_pushButton_26_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->menu);
}

void MainWindow::on_pushButton_23_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->menu);
}

void MainWindow::on_pushButton_22_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->menu);
}

void MainWindow::on_pushButton_30_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->menu);
}

void MainWindow::on_pushButton_39_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->menu);
}

void MainWindow::on_pushButton_38_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->menu);
}

void MainWindow::on_pushButton_37_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->menu);
}

void MainWindow::on_pushButton_31_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->menu);
}

void MainWindow::on_pushButton_44_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->menu);
}

void MainWindow::on_pushButton_43_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->menu);
}

void MainWindow::on_pushButton_42_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->menu);
}

void MainWindow::on_pushButton_41_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->menu);
}

void MainWindow::on_pushButton_40_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->menu);
}
