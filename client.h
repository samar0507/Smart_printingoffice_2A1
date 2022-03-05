#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
class client
{
    QString nom,prenom,adresse;
    int cin,date_naissance;
public:
    client();
    client(int,int,QString,QString,QString);
    QString getNom(){return nom;}
    QString getPrenom(){return prenom;}
    QString getAdresse(){return adresse;}
    int getcin(){return cin;}
    int getdate_naissance(){return date_naissance;}
    void setNom(QString n){nom=n;}
    void setPrenom(QString p){prenom=p;}
    void setCin(int cin){this ->cin=cin;}
    void setAdresse(QString a){adresse=a;}
    void setdate_naissance(int date_naissance){this ->date_naissance=date_naissance;}
    bool ajouter();
    QSqlQueryModel *afficher();
    bool supprimer(int);
    bool modifier(int);
    bool search(int);
    QSqlQueryModel *affichersearch(int );

};



#endif // CLIENT_H
