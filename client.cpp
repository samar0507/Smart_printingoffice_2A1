#include "client.h"

client::client()
{cin=0; nom="";prenom="";
}

client::client(int cin,QDate date_naissance,QString nom,QString prenom,QString adresse,QString QRL)

{ this->cin=cin;
    this->date_naissance=date_naissance;
   this->nom=nom;
       this->prenom=prenom;
this->QRL=QRL;
   this->adresse=adresse;
}
bool client::ajouter()
{
    QSqlQuery query;
    QString res =QString ::number(cin);

    query.prepare("INSERT INTO client (cin,adresse,date_naissance,nom,prenom,QRL)""values(:cin,:adresse,:date_naissance,:nom,:prenom,:QRL) ");

    query.bindValue(":cin",res);
    query.bindValue(":nom",nom);
    query.bindValue(":date_naissance",date_naissance);
    query.bindValue(":adresse",adresse);
    query.bindValue(":prenom",prenom);
     query.bindValue(":QRL",QRL);
    return query.exec();
}
QSqlQueryModel *client::afficher()
{
    QSqlQueryModel * model =new QSqlQueryModel();
        model->setQuery("select * from client");
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("Cin"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("Adresse"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("Date de naissance"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("Nom"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("Prénom"));
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
          query.prepare("UPDATE client SET nom= :nom , prenom= :prenom,date_naissance= :date_naissance,adresse=:adresse,QRL=:QRL WHERE cin=:cin ");
          query.bindValue(":cin",res);
          query.bindValue(":nom", nom);
          query.bindValue(":prenom", prenom);
   query.bindValue(":date_naissance",date_naissance);
          query.bindValue(":adresse",adresse );
query.bindValue(":QRL",QRL );
        return query.exec();
}
QSqlQueryModel *client::affichersearch(int cin,QString nom,QString prenom)
{
    QString res=QString::number(cin);
     QSqlQueryModel * model =new QSqlQueryModel();
    model->setQuery("select * from client where cin like '%"+res+"%'or nom like'%"+nom+"%'or prenom like '%"+prenom+"%';");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Cin"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Adresse"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Date de Naissance"));
 return model;
}
