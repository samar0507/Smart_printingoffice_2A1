#include "historique.h"

historique::historique()
{

}
void historique::save(QString idc,QString prix)
{    QFile file ("C:/Users/ASUS/Documents/histo.txt");
     if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
      qDebug()<<"erreur";
     QTextStream out(&file);
     out << idc+"\n"+prix << "\n";


}
QString historique::load()
{   tmp="";
    QFile file("C:/Users/ASUS/Documents/histo.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
      tmp="";

    QTextStream in(&file);

   while (!in.atEnd()) {

         QString myString = in.readLine();
         tmp+=myString+"\n";

   }
   return tmp;
}
