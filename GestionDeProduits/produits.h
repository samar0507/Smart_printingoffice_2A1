#ifndef PRODUITS_H
#define PRODUITS_H
#include <QString>
#include <QSqlQueryModel>
#include <QMessageBox>
#include<QDebug>
#include<QIntValidator>
#include <QLineEdit>
#include <QDateTime>
#include <QDate>
class Produits
{
public:
     Produits();
     Produits(int ,QString,QDate,int,int);
     int getid();
     QString getnom();
     QDate getdate_p();
     int getprix();
     int getquantite();
     void setid(int);
     void setnom(QString);
     void setdate_p(QDate);
     void setprix(int);
     void setquantite(int);
     bool ajouter();
     QSqlQueryModel* afficher();
     bool supprimer(int);
     bool modifier(Produits);

private:
     int id,prix,quantite;
     QString nom ;
     QDate date_p;
};

#endif // PRODUITS_H
