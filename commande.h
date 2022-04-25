#ifndef COMMANDE_H
#define COMMANDE_H
/*#include "historique.h"*/
#include <QString>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QDate>
#include <QTableView>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>



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

    void recherche(QTableView *table, int idc);
    QSqlQueryModel* tri_prix();
    QSqlQueryModel* tri_idc();
    QSqlQueryModel* tri_date();
    QSqlQueryModel *recherche(int idc);
    void rechercher(QTableView *, int);
    QSqlQueryModel*  afficher_id();
    commande PDF();



    ////
    bool history_file(int idc,int idcl, int prix,QDate date_c);
    QSqlQueryModel* display_history ();
    QSqlQueryModel* calcul (QString mm);
    void clear_commande(QTableView *);

};



#endif // COMMANDE_H
