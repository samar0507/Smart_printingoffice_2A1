#include "connection.h"

connection::connection()
{

}

bool connection::createconnect()
{bool test=false;
db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Source_Projet2A");
db.setUserName("spot");//inserer nom de l'utilisateur
db.setPassword("spot");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;
    return  test;
}
 void connection::closeconnection()
 {
    db.close();
 }
