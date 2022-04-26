#include "connection.h"

connection::connection()
{

}

bool connection::createconnect()
{bool test=false;
db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Projet_2a1");//inserer le nom de la source de données ODBC
db.setUserName("Ghada");//inserer nom de l'utilisateur
db.setPassword("ghada");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;
    return  test;
}
 void connection::closeconnection()
 {
    db.close();
 }
