#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fournisseurs.h"
#include<QMessageBox>
#include<QIntValidator>
#include <QPainter>
#include <QPdfWriter>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include <QPoint>
#include <QImage>
#include <QDesktopServices>
#include <QUrl>
#include<ctime>
//test git
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->id->setValidator(new QIntValidator(0,9999999,this));
    //ui->del_id->setValidator(new QIntValidator(0,9999999,this));
    ui->tab_fournisseurs->setModel(f.afficher());
    ui->tab_id_2->setModel(f.afficher_id());
    //ui->tab_id->setModel(f.load());
    ui->del_id->setModel(f.load());
    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->exitBtn, SIGNAL(clicked()),this, SLOT(close()));
    connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));
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
    QDate date_deb=ui->deb->date();
    QDate date_fin=ui->fin->date();
    QString adresse= ui->adresse->text();
    fournisseurs f(id,nom,date_deb,date_fin,adresse);
    bool test=f.ajouter();
    if(test)
    {
        //REFRESH
        ui->tab_fournisseurs->setModel(f.afficher());
        ui->tab_id_2->setModel(f.afficher_id());
        ui->tab_id_2->setModel(f.load());
        ui->del_id->setModel(f.load());
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
    // int imp=f.import(imp);
    int id=ui->del_id->currentText().toInt();
     bool test=f.supprimer(id);
     //ui->del_id.
     if(test)
     {
         //REFRESH
         ui->tab_fournisseurs->setModel(f.afficher());
         //ui->tab_id->setModel(f.afficher_id());
         ui->tab_id_2->setModel(f.load());
         ui->del_id->setModel(f.load());
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
    //int id=ui->tab_id_2->currentText().toInt();
    int id=ui->update_id->text().toInt();
//    e.setId(ui->update_id->text().toInt())
       QString nom=ui->new_nom->text();
       QDate date_deb=ui->new_deb->date();
       QDate date_fin=ui->new_fin->date();
       QString adresse=ui->new_adresse->text();

//    e.setNom(ui->new_nom->text());
//    e.setPrenom(ui->new_prenom->text());
//    etudiant e(id,nom,prenom);
    bool test=f.modifier(id,nom,date_deb,date_fin,adresse);
    if(test)
    {
        //REFRESH
        ui->tab_fournisseurs->setModel(f.afficher());
        ui->tab_id_2->setModel(f.load());
        ui->del_id->setModel(f.load());
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


void MainWindow::on_delete_all_btn_clicked()
{
    //int id=ui->del_id->text().toInt();
     bool test=f.supprimerTout();
     if(test)
     {
         //REFRESH
         ui->tab_fournisseurs->setModel(f.afficher());
         ui->tab_id_2->setModel(f.load());
         ui->del_id->setModel(f.load());
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
//void MainWindow::on_table_id_currentIndexChanged(int index )
//{

//        int id=ui->tab_id->currentText().toInt();
//        QString id_string=QString::number(id);

//        QSqlQuery query;
//        query.prepare("SELECT * FROM fournisseurs where id='"+id_string+"'");

//        if(query.exec())
//        {
//            while (query.next())
//            {
//              ui->update_id->setText(query.value(0).toString()) ;
//              ui->new_nom->setText(query.value(1).toString()) ;
//              ui->new_deb->setDate(query.value(2).toDate()) ;
//              ui->new_fin->setDate(query.value(3).toDate()) ;
//              ui->new_adresse->setText(query.value(4).toString()) ;


//            }
//        }
//        else
//        {
//            QMessageBox::critical(nullptr, QObject::tr("NOT OK "),
//                        QObject::tr("Echec.\n"
//                                    "Click Cancel to exit."), QMessageBox::Cancel);
//        }
//    }

void MainWindow::on_browse_btn_clicked()
{
    QString filename= QFileDialog::getOpenFileName(this, tr("Choose"),"",tr("Images (*.png *.jpg *.jpeg *.bmp *.gif)"));

    if(QString::compare(filename, QString())!=0)
    {
        QImage image;
        bool valid =image.load(filename);
        if(valid)
        {
            image= image.scaledToWidth(ui->img->width(), Qt::SmoothTransformation);
            ui->img->setPixmap(QPixmap::fromImage(image));
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

    ui->file->setText( fileListString );

}

void MainWindow::sendMail()
{
    Smtp* smtp = new Smtp(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toInt());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}

void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}


void MainWindow::on_tab_id_2_activated(const QModelIndex &index)
{
    QSqlQuery query;
    QString id=ui->tab_id_2->model()->data(index).toString();
    query.prepare("select * from fournisseurs where id='"+id+"'");
    if(query.exec())
    {
        while (query.next())
        {
            ui->update_id->setText(query.value(0).toString());
            ui->new_nom->setText(query.value(1).toString());
            ui->new_deb->setDate(query.value(2).toDate());
            ui->new_fin->setDate(query.value(3).toDate());
            ui->new_adresse->setText(query.value(4).toString());
        }
     }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Failed"),
                        QObject::tr("Impossible.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
}

void MainWindow::on_tri_nom_btn_clicked()
{
    ui->tab_fournisseurs->setModel(f.tri_nom());
        QMessageBox::information(nullptr, QObject::tr("Ok"),
                 QObject::tr("tri effectué.\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);
}


void MainWindow::on_tri_id_btn_clicked()
{
    ui->tab_fournisseurs->setModel(f.tri_id());
        QMessageBox::information(nullptr, QObject::tr("Ok"),
                 QObject::tr("tri effectué.\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_tri_deb_btn_clicked()
{
    ui->tab_fournisseurs->setModel(f.tri_date_deb());
        QMessageBox::information(nullptr, QObject::tr("Ok"),
                 QObject::tr("tri effectué.\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_tri_fin_btn_clicked()
{
    ui->tab_fournisseurs->setModel(f.tri_date_fin());
        QMessageBox::information(nullptr, QObject::tr("Ok"),
                 QObject::tr("tri effectué.\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_search_btn_clicked()
{
    ui->tab_fournisseurs->setModel(f.afficher());
         int id=ui->search->text().toInt();
         f.rechercher(ui->tab_fournisseurs,id);
}

void MainWindow::on_pdf_export_clicked()
{

    QPdfWriter pdf("C:/projet/Smart_printingoffice_2A1-Fournisseurs/fournisseurs");

        QPainter painter(&pdf);
        const QImage image("C:/projet/Smart_printingoffice_2A1-Fournisseurs - Copie (2)/spot.png");
        const QPoint imageCoordinates(0,0);
        painter.drawImage(imageCoordinates,image);
        int i = 4000;
        painter.setPen(Qt::blue);
        painter.setFont(QFont("Arial", 30));
        painter.drawText(3000,1500,"Liste des Fournisseurs");
        painter.setPen(Qt::black);
        painter.setFont(QFont("Arial", 50));
        // painter.drawText(1100,2000,afficheDC);
        painter.drawRect(500,200,700,200);
        painter.drawRect(0,3000,9600,500);
        painter.setFont(QFont("Arial", 9));
        painter.drawText(300,3300,"Identifiant Fournisseurs");
        painter.drawText(2300,3300,"Nom Fournisseurs");
        painter.drawText(4300,3300,"Date Début Contrat");
        painter.drawText(6300,3300,"Date Fin Contrat");
        painter.drawText(8000,3300,"Adresse");
        QSqlQuery query;
                     query.prepare("<SELECT CAST( GETDATE() AS Date ) ");
                     time_t tt;
                     struct tm* ti;
                     time(&tt);
                     ti=localtime(&tt);
                     asctime(ti);
                     painter.drawText(500,300, asctime(ti));
        query.prepare("select * from fournisseurs");
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

        int reponse = QMessageBox::question(this, "Export PDF avec succés", "Voulez-vous Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
        if (reponse == QMessageBox::Yes)
        {
            QDesktopServices::openUrl(QUrl::fromLocalFile("C:/projet/Smart_printingoffice_2A1-Fournisseurs/fournisseurs"));

            painter.end();
        }
        if (reponse == QMessageBox::No)
        {
            painter.end();
        }
}
