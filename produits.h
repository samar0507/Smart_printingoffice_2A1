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
#include <QComboBox>
#include <QSqlQuery>

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
     bool supprimerTout();
     bool modifier(Produits);

     QSqlQueryModel * trierID();
     QSqlQueryModel * trierN();
     QSqlQueryModel *trierD();
     QSqlQueryModel* rechercher_id(int);
     QSqlQueryModel* rechercher_nom(QString);


private:
     int id,prix,quantite;
     QString nom ;
     QDate date_p;
};

#endif // PRODUITS_H
