#include "connection.h"

connection::connection()
{

}

bool connection::createconnect()
{bool test=false;
db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Projet_2A1");
db.setUserName("sam");//inserer nom de l'utilisateur
db.setPassword("sam");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;
    return  test;
}
 void connection::closeconnection()
 {
    db.close();
 }
