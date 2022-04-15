#include "humidite.h"

humidite::humidite()
{

}
humidite::humidite(QDateTime hum)
{
this->hum=hum;
}

bool humidite::ajouter()
{
    QSqlQuery query;

    query.prepare("INSERT INTO humidite (hum)""values(:hum) ");

    query.bindValue(":hum",hum);
    return query.exec();
}
