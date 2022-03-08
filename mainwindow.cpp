#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employes.h"
#include<QMessageBox>
#include<QIntValidator>
#include<QFileDialog>
#include<QImage>
#include <QFile>
#include <QUdpSocket>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->id->setValidator(new QIntValidator(0,9999999,this));
    ui->tab_employes->setModel(e.afficher());
    ui->tab_id_2->setModel((e.afficher_id()));
    mSocket = new QUdpSocket(this);
}
MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_add_btn_clicked()
{
    int id=ui->id->text().toInt();
        QString nom=ui->nom->text();
        QString prenom=ui->per->text();
        QString date_naiss=ui->date->text();
        QString fonc= ui->fonc->text();
        employes e(id,nom,prenom,date_naiss,fonc);
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
           QString date_naiss=ui->date_mod->text();
           QString fonc=ui->fonc_mod->text();
        bool test=e.modifier(id,nom,prenom,date_naiss,fonc);
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

void MainWindow::on_load_butt_clicked()
{
    QSqlQueryModel* modal= new QSqlQueryModel();
       modal->setQuery("SELECT id  FROM employes");
       ui->combo->setModel(modal);
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

QSqlQueryModel * employes::tri_fonc()
{   QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from employes order by fonc");
    return model;}

void MainWindow::on_tri_resp_clicked()
{

    QMessageBox::information(nullptr, QObject::tr("Ok"),
             QObject::tr("tri effectué avec succès.\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);
    ui->tab_employes->setModel(e.tri_fonc());
}
QSqlQueryModel * employes::tri_nom()
{   QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from employes order by nom");
    return model;}
void MainWindow::on_tri_nom_clicked()
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
    ui->tab_employes->setModel(e.tri_prenom());
}
QSqlQueryModel * employes::recherche(int id)
{
    QSqlQuery query ;
    QSqlQueryModel* model=new QSqlQueryModel();
   query.prepare("select * from employes where id =:id");
    query.bindValue(":id",id);
    query.exec();
    model->setQuery(query);
return model;
}
void MainWindow::on_rechercher_clicked()
{
    {
         int id=ui->cherche->text().toInt();
         ui->tab_employes->setModel(e.recherche(id));
         QMessageBox::information(nullptr,QObject::tr("OK"),
                                   QObject::tr("recherche effectuée.\n"
                                               "clic cancel to exit."),QMessageBox::Cancel);
                }
}

QSqlQueryModel*  employes ::afficher_id()
{ QSqlQueryModel *model=new QSqlQueryModel();
model->setQuery("select id from employes");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
return model;
}


void MainWindow::on_enviar_clicked()
{   auto datagrama = ui->msj->text().toLatin1();
    mSocket->writeDatagram(datagrama, QHostAddress::Broadcast,ui->puerto->value());
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
                ui->date_mod->setText(query.value(3).toString());
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
