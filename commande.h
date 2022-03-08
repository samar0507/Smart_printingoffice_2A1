#ifndef COMMANDE_H
#define COMMANDE_H

#include <QString>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QDate>



class commande
{ int idc;
  int idcl;
  int prix;
  QDate date_c;
  QString demande;


public:
    commande();
    commande(int idc,int idcl, int prix,QDate date_c,QString demande);
    int getidc();
    int getidcl();
    int getprix();
    QDate getdate_c();
    QString getdemande();
    void setidc(int);
    void setidcl(int);
    void setprix(int);
    void setdate_c(QDate);
    void setdemande(QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel* tri_prix();
    QSqlQueryModel* tri_idc();
    QSqlQueryModel* tri_date();
    QSqlQueryModel * recherche(int idc);
    QSqlQueryModel*  afficher_id();



};



#endif // COMMANDE_H
