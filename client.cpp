#include "client.h"

client::client()
{cin=0; nom="";prenom="";
}

client::client(int cin,QDate date_naissance,QString nom,QString prenom,QString adresse)

{ this->cin=cin;
    this->date_naissance=date_naissance;
   this->nom=nom;
       this->prenom=prenom;

   this->adresse=adresse;
}
bool client::ajouter()
{
    QSqlQuery query;
    QString res =QString ::number(cin);
    query.prepare("INSERT INTO client (cin,adresse,date_naissance,nom,prenom)""values(:cin,:adresse,:date_naissance,:nom,:prenom) ");

    query.bindValue(":cin",res);
    query.bindValue(":nom",nom);
    query.bindValue(":date_naissance",date_naissance);
    query.bindValue(":adresse",adresse);
    query.bindValue(":prenom",prenom);
    return query.exec();
}
QSqlQueryModel *client::afficher()
{
    QSqlQueryModel * model =new QSqlQueryModel();
        model->setQuery("select * from client");
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("Cin"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("Adresse"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("Date de Naissance"));
    return model;
}
bool client::supprimer(int cin)
{
    QSqlQuery query;
    QString res=QString::number(cin);
    query.prepare("Delete from client where cin= :cin");
    query.bindValue(":cin",res);
    return query.exec();
}
bool client::modifier(int cin)
{
    QSqlQuery query;

          QString res=QString::number(cin);
          query.prepare("UPDATE client SET nom= :nom , prenom= :prenom,date_naissance= :date_naissance,adresse=:adresse WHERE cin=:cin ");
          query.bindValue(":cin",res);
          query.bindValue(":nom", nom);
          query.bindValue(":prenom", prenom);
   query.bindValue(":date_naissance",date_naissance);
          query.bindValue(":adresse",adresse );

        return query.exec();
}
QSqlQueryModel *client::affichersearch(int cin)
{
    QString res=QString::number(cin);
     QSqlQueryModel * model =new QSqlQueryModel();
    model->setQuery("select * from client where cin like '%"+res+"%';");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Cin"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Adresse"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Date de Naissance"));
 return model;
}
