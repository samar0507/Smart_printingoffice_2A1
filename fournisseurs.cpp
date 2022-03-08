#include "fournisseurs.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QDate>
fournisseurs::fournisseurs()
{
    id=0; nom=""; date_deb=QDate(); date_fin=QDate(); adresse="";
}
fournisseurs::fournisseurs(int id, QString nom, QDate date_deb, QDate date_fin, QString adresse)
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
bool fournisseurs::modifier(int id,QString nom, QDate date_deb, QDate date_fin, QString adresse)
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
QSqlQueryModel * fournisseurs::load()
{
    QSqlQueryModel* model= new QSqlQueryModel();
model->setQuery("SELECT id FROM fournisseurs");
return model;
}
QSqlQueryModel * fournisseurs::fetch_nom()
{
    QSqlQuery query;
    QSqlQueryModel* model= new QSqlQueryModel();
//    QString res=QString::number(id);
    model->setQuery("select nom from fournisseurs where ID= :id");
    query.bindValue(":id",id);
    return model;
}
QSqlQueryModel* fournisseurs ::afficher_id()
{
 QSqlQueryModel* model=new QSqlQueryModel();
 model->setQuery("select id from fournisseurs");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
 return model;

}

QSqlQueryModel * fournisseurs::tri_id()
{   QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from fournisseurs order by id");
    return model;
}
QSqlQueryModel * fournisseurs::tri_nom()
{   QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from fournisseurs order by nom");
    return model;
}
QSqlQueryModel * fournisseurs::tri_date_deb()
{   QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from fournisseurs order by date_deb");
    return model;
}
QSqlQueryModel * fournisseurs::tri_date_fin()
{   QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from fournisseurs order by date_fin");
    return model;
}
void fournisseurs::rechercher(QTableView *table, int id)
{
   QSqlQueryModel *model=new QSqlQueryModel();
   QSqlQuery *query =new QSqlQuery;
   query->prepare("select * from fournisseurs where regexp_like(id,:id);");
   query->bindValue(":id",id);

   if(id==0)
   {
       query->prepare("select * from fournisseurs");
   }
   query->exec();
   model->setQuery(*query);
   table->setModel(model);
   table->show();
}
//int import(int id)
//{
//    QSqlQuery query("SELECT Name, Group FROM Teacher");
//    int nameID = query.record().indexOf("Name");
//    int groupID = query.record().indexOf("Group");
//    while (query.next()) {
//          ui->comboBox->addItem(query.value(nameID).toString());
//          ui->comboBox->addItem(query.value(groupID).toString());
//        }
//return id;
//}









