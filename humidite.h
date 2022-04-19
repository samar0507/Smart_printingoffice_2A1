#ifndef HUMIDITE_H
#define HUMIDITE_H

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
class humidite
{
   QDateTime hum;
public:
    humidite();
    humidite(QDateTime);
    void ajouter();
};

#endif // HUMIDITE_H
