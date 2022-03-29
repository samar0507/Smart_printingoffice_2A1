#include "connection.h"

Connection::Connection()
{}

bool Connection::createconnect()
{
 db = QSqlDatabase::addDatabase("QODBC");
 bool test=false;
db.setDatabaseName("projet_2a");
db.setUserName("sirine");//inserer nom de l'utilisateur
db.setPassword("sirine");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
