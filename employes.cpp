#include "employes.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
employes::employes()
{
    id=0; nom=""; prenom=""; date_naiss=""; fonc="";
}
employes::employes(int id, QString nom, QString prenom, QString date_naiss , QString fonc)
{

    this->id=id;
    this->nom=nom;
    this->prenom=prenom;
    this->date_naiss=date_naiss;
    this->fonc=fonc;
}



bool employes::ajouter()
{
 QSqlQuery query;
 QString res = QString::number(id);
 //prend la requête en paramètre pour préparer son execution
 query.prepare("insert into employes(id, nom, prenom, date_naiss, fonc)" "values(:id, :nom, :prenom, :date_naiss, :fonc)");
 //creation des variables liées
 query.bindValue(0,res);
 query.bindValue(1,nom);
 query.bindValue(2,prenom);
 query.bindValue(3,date_naiss);
 query.bindValue(4,fonc);
 return query.exec(); //envoie la requete pour l'executer
}
QSqlQueryModel * employes::afficher()
{
    QSqlQueryModel* model= new QSqlQueryModel();
model->setQuery("SELECT * FROM employes");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("date_naiss"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("fonc"));
return model;
}
bool employes::supprimer(int id)
{
    QSqlQuery query;
//    QString res=QString::number(id);
    query.prepare("Delete from employes where ID= :id");
    query.bindValue(0,id);

    return query.exec();
}
bool employes::modifier(int id,QString nom, QString prenom, QString date_naiss, QString fonc)
{     QSqlQuery query;
    //prend la requête en paramètre pour préparer son execution
        query.prepare("update employes set id = :id, nom= :nom , prenom= :prenom, date_naiss= :date_naiss, fonc= :fonc where ID= :id");

        //creation des variables liées
        query.bindValue(":id",id);
        query.bindValue(":nom",nom);
        query.bindValue(":prenom",prenom);
        query.bindValue(":date_naiss", date_naiss);
        query.bindValue(":fonc", fonc);
        return query.exec(); //envoie la requete pour l'executer

}
