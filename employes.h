#ifndef EMPLOYES_H
#define EMPLOYES_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>

class employes
{
    int id;
    QString nom;
    QString prenom;
    QString date_naiss;
    QString fonc;


public:
 //Conctructeurs
  employes();
  employes(int,QString,QString,QString,QString);
 //Getters
    int getId() {return id;}
    QString getNom(){return nom;}
    QString getPrenom(){return prenom;}
    QString getDatedenaissance(){return date_naiss;}
    QString getFonctionnalite(){return fonc;}

 //Setters
    void setId(int id){this->id=id;}
    void setNom(QString n){nom=n;}
    void setPrenom(QString pr){prenom=pr;}
    void setDatedenaissance(QString dn){date_naiss=dn;}
    void setFonctionnalite(QString f){fonc=f;}

 //Fonctionnalités du CRUD
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier(int,QString,QString,QString,QString);
    QSqlQueryModel *tri_fonc();
    QSqlQueryModel * tri_nom();
    QSqlQueryModel * tri_prenom();
    QSqlQueryModel * recherche(int id);
    QSqlQueryModel *  afficher_id();
};

#endif // employe_H
