#ifndef EMPLOYES_H
#define EMPLOYES_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QDate>
#include<QTableView>
class employes
{
    int id;
    QString nom;
    QString prenom;
    QDate date_naiss;
    QString pass;


public:
 //Conctructeurs
  employes();
  employes(int,QString,QString,QDate,QString);
 //Getters
    int getId() {return id;}
    QString getNom(){return nom;}
    QString getPrenom(){return prenom;}
    QDate getDatedenaissance(){return date_naiss;}
    QString getFonctionnalite(){return pass;}

 //Setters
    void setId(int id){this->id=id;}
    void setNom(QString n){nom=n;}
    void setPrenom(QString pr){prenom=pr;}
    void setDatedenaissance(QDate dn){date_naiss=dn;}
    void setFonctionnalite(QString f){pass=f;}

 //Fonctionnalités du CRUD
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier(int,QString,QString,QDate,QString);
    QSqlQueryModel *tri_fonc();
    QSqlQueryModel * tri_nom();
    QSqlQueryModel * tri_prenom();
//    QSqlQueryModel * recherche(int id);
    QSqlQueryModel *  afficher_id();
     void rechercher(QTableView*, int);
     void clear_employes(QTableView *);
};

#endif // employe_H
