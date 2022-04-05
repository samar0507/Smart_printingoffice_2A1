#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include <QTranslator>
#include <QMessageBox>
#include <QInputDialog>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator t;
    QStringList languages;
    languages << "English" << "French" << "Arabic" << "Chinois" ;
    QString lang= QInputDialog::getItem(NULL,"Select Language",
                                      "Language", languages);
    if(lang == "English")
    {
        t.load(":/english.qm");
        a.installTranslator(&t);
    }else if(lang == "Arabic")
    {
        t.load(":/arabic.qm");
        a.installTranslator(&t);
    }else if(lang != "French")
    {
        a.installTranslator(&t);
    }

    Connection c;//instance de la classe connection
    bool test=c.createconnect();// etablir la connexion
    MainWindow w;
    if(test) //verifier si la connexion est établie
    {w.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else// echec de connexion
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);




    return a.exec();
}
