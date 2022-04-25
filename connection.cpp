#include "connection.h"

connection::connection()
{

}

bool connection::createconnect()
{bool test=false;
db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("projet_2a");//inserer le nom de la source de données ODBC
db.setUserName("sirine");//inserer nom de l'utilisateur
db.setPassword("sirine");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;
    return  test;
}
 void connection::closeconnection()
 {
    db.close();
 }
