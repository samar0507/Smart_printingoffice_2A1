#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include "connection.h"
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
#include <QPdfWriter>
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
using qrcodegen::QrCode;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
      ui->CAM->setMenu(mOptionsMenu);
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
}
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_4_clicked()
{

    if(ui->tab_cl->currentIndex().row()==-1)
                  QMessageBox::information(nullptr, QObject::tr("QrCode"),
                                           QObject::tr("Veuillez Choisir un client du Tableau.\n"
                                                       "Click Ok to exit."), QMessageBox::Ok);
              else
              {
                   int cin=ui->tab_cl->model()->data(ui->tab_cl->model()->index(ui->tab_cl->currentIndex().row(),0)).toInt();
    bool test=cl.supprimer(cin);
    if(test)
    { ui->tab_cl->setModel(cl.afficher());//refresh
       ui->lineEdit_search->clear();
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
void MainWindow::on_pushButton_20_clicked()
{
    int cin = ui->lineEdit_cin->text().toInt();
    QString nom=ui->lineEdit_nom->text();
    QDate date_naissance = ui->dateEdit->date();
    QString adresse=ui->lineEdit_adresse->text();
      QString prenom=ui->lineEdit_prenom->text();
      client cl(cin,date_naissance,nom,prenom,adresse);
      if(cin!=0 && nom!=""  && prenom!="" && adresse!="")
      {
       bool test=cl.ajouter();
       if(test)
       { ui->tab_cl->setModel(cl.afficher());//refresh

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

void MainWindow::on_pushButton_19_clicked()
{


}





void MainWindow::on_lineEdit_search_cursorPositionChanged(int arg1, int arg2)
{
    int cin = ui->lineEdit_search->text().toInt();
     QString nom=ui->lineEdit_search->text();
     QString prenom=ui->lineEdit_search->text();
    if(arg2!= 0)
    {
    ui->tab_cl->setModel(cl.affichersearch(cin,nom,prenom));
    }
    else{
ui->tab_cl->setModel(cl.afficher());
    }}

void MainWindow::on_pushButton_2_clicked()
{
    QTableView *table;
       table = ui->tab_cl;

       QString filters("xls files (*.xls);;All files (*.*)");
       QString defaultFilter("xls files (*.xls)");
       QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                          filters, &defaultFilter);
       QFile file(fileName);

       QAbstractItemModel *model =  table->model();
       if (file.open(QFile::WriteOnly | QFile::Truncate)) {
           QTextStream data(&file);
           QStringList strList;
           for (int i = 0; i < model->columnCount(); i++) {
               if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                   strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
               else
                   strList.append("");
           }
           data << strList.join("|  |") << "\n";
           for (int i = 0; i < model->rowCount(); i++) {
               strList.clear();
               for (int j = 0; j < model->columnCount(); j++) {

                   if (model->data(model->index(i, j)).toString().length() > 0)
                       strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                   else
                       strList.append("");
               }
               data << strList.join("|") + "\n";
           }
           file.close();
           QMessageBox::information(this,"Exporter To Excel","Exporter En Excel Avec Succées ");
       }
   }

void MainWindow::on_pushButton_24_clicked()
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
                   ui->label_2->setPixmap(pix);

              }
}

void MainWindow::on_pushButton_3_clicked()
{
    if(ui->tab_cl->currentIndex().row()==-1)
                  QMessageBox::information(nullptr, QObject::tr("QrCode"),
                                           QObject::tr("Veuillez Choisir un client du Tableau.\n"
                                                       "Click Ok to exit."), QMessageBox::Ok);
              else
              {
        int cin=ui->tab_cl->model()->data(ui->tab_cl->model()->index(ui->tab_cl->currentIndex().row(),0)).toInt();

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

void MainWindow::on_pushButton_22_clicked()
{
    int cin = ui->lineEdit_cin_2->text().toInt();
    QString nom=ui->lineEdit_nom_2->text();
    QDate date_naissance = ui->dateEdit_2->date();
    QString adresse=ui->lineEdit_adresse_2->text();
      QString prenom=ui->lineEdit_prenom_2->text();
      client cl(cin,date_naissance,nom,prenom,adresse );
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
