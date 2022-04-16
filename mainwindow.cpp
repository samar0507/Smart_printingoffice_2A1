#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include "humidite.h"
#include "connection.h"
#include "arduino.h"
#include "produits.h"
#include "statistiques.h"
#include "notification.h"

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


using qrcodegen::QrCode;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   centralWidget()->setStyleSheet("{background-image:url(qrc:/img/img/djjjj.jpg)}");

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
           ui->tab_cl->setModel(cl.afficher());//refresh

           ui->lineEdit_cin->clear();
           ui->lineEdit_nom->clear();
           ui->lineEdit_prenom->clear();
           ui->dateEdit->clear();
           ui->lineEdit_adresse->clear();
           QMessageBox::information(nullptr, QObject::tr("done"),
                                  QObject::tr("ajout effectue.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);

              }
                  else
                      QMessageBox::critical(nullptr, QObject::tr("error"),
                                  QObject::tr("ajout non effectue.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);
       }else
          QMessageBox::critical(nullptr, QObject::tr("error"),
                      QObject::tr("ajout non effectue.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
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
      { ui->tab_cl->setModel(cl.afficher());//refresh
          ui->lineEdit_cin_2->clear();
          ui->lineEdit_nom_2->clear();
          ui->lineEdit_prenom_2->clear();
          ui->dateEdit_2->clear();
          ui->lineEdit_adresse_2->clear();
      QMessageBox::information(nullptr, QObject::tr("done "),
                        QObject::tr("modification effectué!\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);



      }
        else
            QMessageBox::critical(nullptr, QObject::tr("error"),
                        QObject::tr("modification non effectué !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
      }else
          QMessageBox::critical(nullptr, QObject::tr("error"),
                      QObject::tr("modification non effectué !.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);

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
           QMessageBox::information(this,"Exporter To Excel","Exporter En Excel Avec Succées ");
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
        QMessageBox::information(nullptr, QObject::tr("done"),
                               QObject::tr("suppression effectue.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);

           }
               else
                   QMessageBox::critical(nullptr, QObject::tr("error"),
                               QObject::tr("suppression non effectue.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);


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

// produits
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
