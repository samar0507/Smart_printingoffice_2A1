#include "connection.h"

Connection::Connection()
{}

bool Connection::createconnect()
{
db = QSqlDatabase::addDatabase("QODBC");
 bool test=false;
db.setDatabaseName("projet_2a");//inserer le nom de la source de données ODBC
db.setUserName("nour");//inserer nom de l'utilisateur
db.setPassword("nour");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;

    return  test;
}
void Connection::closeconnect(){db.close();}
