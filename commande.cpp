#include "commande.h"
#include "ui_commande.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QDate>
#include <QTableView>
#include "historique.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>



commande::commande()
{
   idc=0;
   idcl=0;
   prix=0;
   date_c=QDate();
   demande=" ";
}

commande::commande(int idc,int idcl, int prix,QDate date_c,QString demande)
{ this->idc=idc ; this->idcl=idcl ; this->prix=prix;this->date_c=date_c ; this->demande=demande;}
int commande::getidc(){return idc;}
int commande::getidcl(){return idcl;}
int commande::getprix(){return prix;}
QDate commande::getdate_c(){return date_c;}
QString commande::getdemande(){return demande;}
void commande::setidc(int idc){ this->idc=idc;}
void commande::setidcl(int idcl){this->idcl=idcl;}
void commande::setprix(int prix){this->prix=prix;}
void commande::setdate_c(QDate date_c){this->date_c=date_c;}
void commande::setdemande(QString demande){this->demande=demande;}
bool commande::ajouter()
{
    QString idc_QString=QString::number(idc);
    QSqlQuery query;
          query.prepare("INSERT INTO commande (idc,idcl, prix, date_c, demande) "
                        "VALUES (:idc, :idcl, :prix, :date_c, :demande)");
          query.bindValue(0, idc_QString);
          query.bindValue(1, idcl);
          query.bindValue(2, prix);
          query.bindValue(3, date_c);
          query.bindValue(4, demande);
        return  query.exec();

}
bool commande::supprimer(int idc)
{
    QSqlQuery query;
          query.prepare(" Delete from commande where idc=:idc");
          query.bindValue(0, idc);
        return  query.exec();


}
QSqlQueryModel* commande::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

        model->setQuery("SELECT * FROM commande");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant commande"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("idc"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prix"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date de commande"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Demande de client"));



    return model;
}
bool commande::modifier()
    {




        QSqlQuery query;
            query.prepare("UPDATE commande SET idc=:idc, idcl=:idcl, prix=:prix, date_c=:date_c,demande=:demande WHERE idc=:idc ");
            query.bindValue(":idc", idc);
            query.bindValue(":idcl", idcl);
            query.bindValue(":prix", prix);
            query.bindValue(":date_c", date_c);
            query.bindValue(":demande", demande);
             return query.exec();

    }
QSqlQueryModel * commande::tri_prix()
{   QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from commande order by prix");
    return model;
}
QSqlQueryModel * commande::tri_idc()
{   QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from commande order by idc");
    return model;
}
QSqlQueryModel * commande::tri_date()
{   QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from commande order by date");
    return model;
}
/*QSqlQueryModel * commande::recherche(int idc)
{
    QSqlQuery query ;
        QSqlQueryModel* model=new QSqlQueryModel();
       query.prepare("select * from commande where idc =:idc");
        query.bindValue(0,idc);
        query.exec();
        model->setQuery(query);
    return model;
} */

QSqlQueryModel*  commande ::afficher_id()
{
    QSqlQueryModel* model=new QSqlQueryModel();
model->setQuery("select idc from commande");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("idc"));
return model;
}
/*
void commande::recherche(QTableView *table, int idc)
{
   QSqlQueryModel *model=new QSqlQueryModel();
   QSqlQuery *query =new QSqlQuery;
   query->prepare("select * from COMMANDE where regexp_like(idc,:idc);");
   query->bindValue(":idc",idc);
   if(idc==0)
      {
          query->prepare("select * from COMMANDE");
      }

   query->exec();
   model->setQuery(*query);
   table->setModel(model);
   table->show();
}*/
/*QSqlQueryModel *commande::recherche(int idc)
{
    QString res=QString::number(idc);
     QSqlQueryModel * model =new QSqlQueryModel();
    model->setQuery("select * from COMMANDE where idc like '"+res+"%';");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant commande"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("idc"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prix"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date de commande"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Demande de client"));
 return model;
}*/
/*void commande::addToHistory()
{

    QSqlQuery query1;
    query1.prepare("select * from COMMANDE where (TO_CHAR(date,'dd/mm/yyyy') = TO_CHAR(sysdate,'dd/mm/yyyy'))");
    query1.exec();

    QSqlQuery query,qry;
    QString date=QDateTime::currentDateTime().toString("dddd, dd MMMM yyyy");
    QString date1=QDateTime::currentDateTime().toString("dd/MM/yy");
    QString time=QDateTime::currentDateTime().toString("hh:mm");
    QString activity;

    activity="\n    "+date1+"   -   "+time+" \t   \n";


} */
/*QSqlQueryModel* commande::afficherHistorique()
{   QSqlQueryModel* model=new QSqlQueryModel();

    model->setQuery("SELECT * from COMMANDE where (TO_CHAR(date,'dd/mm/yyyy') = TO_CHAR(sysdate,'dd/mm/yyyy'))");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant commande"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("idc"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prix"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date de commande"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Demande de client"));

}*/

bool commande::history_file(int idc,int idcl, int prix,QDate date_c)
{
    QFile file("C:\\Users\\ASUS\\Desktop\\projet\\copieee\\copieee\\file.txt");
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
