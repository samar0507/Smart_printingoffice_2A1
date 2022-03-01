#ifndef FOURNISSEURS_H
#define FOURNISSEURS_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>

class fournisseurs
{
    int id;
    QString nom;
    QString date_deb;
    QString date_fin;
    QString adresse;


public:
 //Conctructeurs
    fournisseurs();
    fournisseurs(int,QString,QString,QString,QString);
 //Getters
    int getId() {return id;}
    QString getNom(){return nom;}
    QString getDateDeb(){return date_deb;}
    QString getDateFin(){return date_fin;}
    QString getAdresse(){return adresse;}

 //Setters
    void setId(int id){this->id=id;}
    void setNom(QString n){nom=n;}
    void setDateDeb(QString dd){date_deb=dd;}
    void setDateFin(QString df){date_fin=df;}
    void setAdresse(QString a){adresse=a;}

 //Fonctionnalités du CRUD
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool supprimerTout();
    bool modifier(int,QString,QString,QString,QString);
};

#endif // FOURNISSEURS_H
