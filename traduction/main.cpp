#include "mainwindow.h"
#include<QTranslator>
#include <QApplication>
#include <QInputDialog>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QStringList languages;
    QTranslator t;
    languages << "English" << "French"  ;
    QString lang= QInputDialog::getItem(NULL,"Select Language",
                                    "Language", languages);
    if(lang == "French")
    {
        t.load(":/french.qm");
    }else if(lang != "English")
    {
        a.installTranslator(&t);
    }


    MainWindow w;
    w.show();
    return a.exec();
}
