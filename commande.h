#ifndef COMMANDE_H
#define COMMANDE_H

#include <QString>
#include <QMessageBox>
#include <QSqlQueryModel>


class commande
{ int idc;
  int idcl;
  int prix;
  QString date_c;
  QString demande;


public:
    commande();
    commande(int idc,int idcl, int prix,QString date_c,QString demande);
    int getidc();
    int getidcl();
    int getprix();
    QString getdate_c();
    QString getdemande();
    void setidc(int);
    void setidcl(int);
    void setprix(int);
    void setdate_c(QString);
    void setdemande(QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier();

};



#endif // COMMANDE_H
