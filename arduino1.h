#ifndef ARDUINO1_H
#define ARDUINO1_H
#include<QDateTime>

class arduino1{
public:
    arduino1 (int nb,QString date1){this->nbr=nb;this->date_ajout=date1;};
bool ajouter();
int nbr;
QString date_ajout;
};
#endif // ARDUINO1_H
