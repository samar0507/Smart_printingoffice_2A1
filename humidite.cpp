#include "humidite.h"

humidite::humidite()
{

}
humidite::humidite(QDateTime hum)
{
this->hum=hum;
}

void humidite::ajouter()
{
    QSqlQuery query;

    query.prepare("INSERT INTO arduino (hum)""values(:hum) ");

    query.bindValue(":hum",hum);
     query.exec();
}
