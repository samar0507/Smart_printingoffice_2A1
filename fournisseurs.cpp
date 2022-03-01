#include "fournisseurs.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
fournisseurs::fournisseurs()
{
    id=0; nom=""; date_deb=""; date_fin=""; adresse="";
}
fournisseurs::fournisseurs(int id, QString nom, QString date_deb, QString date_fin, QString adresse)
{
    this->id=id;
    this->nom=nom;
    this->date_deb=date_deb;
    this->date_fin=date_fin;
    this->adresse=adresse;
}

bool fournisseurs::ajouter()
{
 QSqlQuery query;
 QString res = QString::number(id);
 //prend la requête en paramètre pour préparer son execution
 query.prepare("insert into fournisseurs(id, nom, date_deb, date_fin, adresse)" "values(:id, :nom, :date_deb, :date_fin, :adresse)");
 //creation des variables liées
 query.bindValue(0,res);
 query.bindValue(1,nom);
 query.bindValue(2,date_deb);
 query.bindValue(3,date_fin);
 query.bindValue(4,adresse);
 return query.exec(); //envoie la requete pour l'executer
}
QSqlQueryModel * fournisseurs::afficher()
{
    QSqlQueryModel* model= new QSqlQueryModel();
model->setQuery("SELECT * FROM fournisseurs");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date Début Contrat"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date Fin Contrat"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse"));
return model;
}
bool fournisseurs::supprimer(int id)
{
    QSqlQuery query;
//    QString res=QString::number(id);
    query.prepare("Delete from fournisseurs where ID= :id");
    query.bindValue(0,id);

    return query.exec();
}
bool fournisseurs::supprimerTout()
{
    QSqlQuery query;
//    QString res=QString::number(id);
    query.prepare("TRUNCATE TABLE fournisseurs");
    //query.bindValue(0,id);

    return query.exec();
}
bool fournisseurs::modifier(int id,QString nom, QString date_deb, QString date_fin, QString adresse)
{
    QSqlQuery query;

//    nom=getNom();
//    prenom=getPrenom();
    //prend la requête en paramètre pour préparer son execution
    query.prepare("update fournisseurs set id = :id, nom= :nom , date_deb= :date_deb, date_fin= :date_fin, adresse= :adresse where ID= :id");

    //creation des variables liées
    query.bindValue(":id",id);
    query.bindValue(":nom",nom);
    query.bindValue(":date_deb",date_deb);
    query.bindValue(":date_fin", date_fin);
    query.bindValue(":adresse", adresse);
    return query.exec(); //envoie la requete pour l'executer
}
