#include "login.h"
#include <QMessageBox>
#include "connection.h"
#include <QApplication>
#include <QTranslator>
#include <QInputDialog>

int main(int argc, char *argv[])
{ QApplication a(argc, argv);
    QTranslator t;
    QStringList languages;
    languages << "English" << "French" << "Arabic" << "Chinois" ;
    QString lang= QInputDialog::getItem(NULL,"Select Language",
                                      "Language", languages);
    if(lang == "English")
    {
        t.load(":/anglaiss.qm");
        a.installTranslator(&t);
    }else if(lang == "Arabic")
    {
        t.load(":/arbi.qm");
        a.installTranslator(&t);
    }else if(lang != "French")
    {
        a.installTranslator(&t);
    }
    connection c;

    bool test=c.createconnect();
     login w;
   //  a.setStyle("fusion");
    if(test)
    {w.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



    return a.exec();
}
