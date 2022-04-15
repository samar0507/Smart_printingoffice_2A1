#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
class client
{
    QString nom,prenom,adresse,QRL;
    int cin;
    QDate date_naissance;
public:
    client();
    client(int,QDate,QString,QString,QString,QString);
    QString getNom(){return nom;}
     QString getQRL(){return QRL;}
    QString getPrenom(){return prenom;}
    QString getAdresse(){return adresse;}
    int getcin(){return cin;}
    QDate getdate_naissance(){return date_naissance;}
    void setNom(QString n){nom=n;}
    void setQRL(QString q){QRL=q;}
    void setPrenom(QString p){prenom=p;}
    void setCin(int cin){this ->cin=cin;}
    void setAdresse(QString a){adresse=a;}
    void setdate_naissance(QDate date_naissance){this ->date_naissance=date_naissance;}
    bool ajouter();
    QSqlQueryModel *afficher();
    bool supprimer(int);
    bool modifier(int);
    bool search(int);
    QSqlQueryModel *affichersearch(int,QString,QString );

};



#endif // CLIENT_H
