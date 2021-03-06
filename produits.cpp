#include "produits.h"
#include <QSqlQuery>
#include<QDebug>
#include <QSqlQueryModel>
#include<QObject>

Produits::Produits()
{
    id=0 ; nom=" "; prix=0; quantite=0;
}

Produits::Produits(int id ,QString nom ,QDate date_p,int prix ,int quantite)
{   this->id=id;
    this->nom=nom ;
    this->date_p=date_p ;
    this->prix=prix ;
    this->quantite=quantite ;
}
 int Produits::getid()
 {return id;}
 QString Produits::getnom()
 {return nom;}
 QDate Produits::getdate_p()
 {return date_p;}
 int Produits::getprix()
 {return prix;}
 int Produits::getquantite()
 {return quantite;}

 void Produits::setid(int id)
 {this->id=id ;}
 void Produits::setnom(QString nom)
 {this->nom=nom ;}
 void Produits::setdate_p(QDate date_p)
 {this->date_p=date_p ;}
 void Produits::setprix(int prix)
 {this->prix=prix ;}
 void Produits::setquantite(int quantite)
 {this->quantite=quantite ;}

bool Produits::ajouter()
{

    QSqlQuery query;
    QString id_string=QString::number(id);
    query.prepare("INSERT INTO produits (id, nom,date_p, prix,quantite) "
                        "VALUES (:id, :nom,:date_p, :prix,:quantite)");
          query.bindValue(":id", id_string);
          query.bindValue(":nom", nom);
          query.bindValue(":date_p", date_p);
          query.bindValue(":prix", prix);
          query.bindValue(":quantite", quantite);

          return   query.exec();

}


QSqlQueryModel * Produits ::afficher()
{ QSqlQueryModel * model=new QSqlQueryModel();


        model->setQuery("SELECT * FROM produits");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATE_P"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRIX"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("QUANTITE"));


return model;
}

bool Produits::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE from produits where id=:id");
          query.bindValue(":id",id);
          return   query.exec();
}

bool Produits::supprimerTout()
{ QSqlQuery query;

   query.prepare("delete from produits ");

  return query.exec();
}

bool Produits::modifier(Produits P2)
{
    QSqlQuery query;
    query.prepare("UPDATE produits SET nom= :nom ,date_p = :date_p, prix= :prix , quantite= :quantite WHERE id= :id");
    query.bindValue(":id",P2.getid());
    query.bindValue(":nom",P2.getnom());
    query.bindValue(":date_p",P2.getdate_p());
    query.bindValue(":prix",P2.getprix());
    query.bindValue(":quantite",P2.getquantite());

    return query.exec();
}

QSqlQueryModel *Produits::trierID() //tri par ID
{
                     QSqlQuery * q = new  QSqlQuery ();
                     QSqlQueryModel * model = new  QSqlQueryModel ();
                     q->prepare("SELECT * FROM produits order by id ASC");
                     q->exec();
                     model->setQuery(*q);
                     return model;

}

QSqlQueryModel *Produits::trierN() //tri par nom
{
                     QSqlQuery * q = new  QSqlQuery ();
                     QSqlQueryModel * model = new  QSqlQueryModel ();
                     q->prepare("SELECT * FROM produits order by nom ASC");
                     q->exec();
                     model->setQuery(*q);
                     return model;

}
QSqlQueryModel *Produits::trierD() //tri par date
{

              QSqlQuery * q = new  QSqlQuery ();
                     QSqlQueryModel * model = new  QSqlQueryModel ();
                     q->prepare("SELECT * FROM produits order by date_p DESC");
                     q->exec();
                     model->setQuery(*q);
                     return model;

}


QSqlQueryModel * Produits::rechercher(QSqlQuery q)
{
    QSqlQueryModel *model4= new QSqlQueryModel();
    model4->setQuery(q);
    return (model4);
}
void Produits::statistique(QVector<double>* ticks,QVector<QString> *labels)
{
    QSqlQuery q;
    int i=0;
    q.exec("select QUANTITE from produits");
    while (q.next())
    {
        QString id = q.value(0).toString();
        i++;
        *ticks<<i;
        *labels <<id;
    }
}
