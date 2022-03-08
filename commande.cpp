#include "commande.h"
#include "ui_commande.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QDate>


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
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Identifiant client"));
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

            query.bindValue(":idc", idc);

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
QSqlQueryModel * commande::recherche(int idc)
{
    QSqlQuery query ;
    QSqlQueryModel* model=new QSqlQueryModel();
   query.prepare("select * from commande where idc =:idc");
    query.bindValue(0,idc);
    query.exec();
    model->setQuery(query);
return model;
}
QSqlQueryModel*  commande ::afficher_id()
{
    QSqlQueryModel* model=new QSqlQueryModel();
model->setQuery("select idc from commande");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("idc"));
return model;
}

