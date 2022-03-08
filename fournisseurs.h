#ifndef FOURNISSEURS_H
#define FOURNISSEURS_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QDate>
#include<QTableView>
class fournisseurs
{
    int id;
    QString nom;
    QDate date_deb;
    QDate date_fin;
    QString adresse;


public:
 //Conctructeurs
    fournisseurs();
    fournisseurs(int,QString,QDate,QDate,QString);
 //Getters
    int getId() {return id;}
    QString getNom(){return nom;}
    QDate getDateDeb(){return date_deb;}
    QDate getDateFin(){return date_fin;}
    QString getAdresse(){return adresse;}

 //Setters
    void setId(int id){this->id=id;}
    void setNom(QString n){nom=n;}
    void setDateDeb(QDate dd){date_deb=dd;}
    void setDateFin(QDate df){date_fin=df;}
    void setAdresse(QString a){adresse=a;}

 //Fonctionnalités du CRUD
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool supprimerTout();
    bool modifier(int,QString,QDate,QDate,QString);
 //Autres fonctionnalités
    QSqlQueryModel* load();
    QSqlQueryModel* fetch_nom();
    QSqlQueryModel* afficher_id();
 //Métiers
    QSqlQueryModel * tri_id();
    QSqlQueryModel * tri_nom();
    QSqlQueryModel * tri_date_deb();
    QSqlQueryModel * tri_date_fin();
    void rechercher(QTableView*, int);

    bool import(int);
};

#endif // FOURNISSEURS_H
