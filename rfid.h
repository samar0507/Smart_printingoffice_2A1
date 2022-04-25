#ifndef RFID_H
#define RFID_H
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class Arduino
{
public:
    Arduino();
    int connect_arduino(); //Connecter le pc à arduino
    int close_arduino(); //fermer la connexion
    int write_to_arduino(QByteArray); //envoyer des donnees vers arduino
    QByteArray read_from_arduino(); //recevoir des donnees de la carte arduino
    QSerialPort* getSerial(); //accesseur
    QString getArduino_port_name();
    int checkCard(QString, QSerialPort *);
private:
    QSerialPort * serial;//rassemble les informations et des fonctions (envoi,lecture de récéption...) sur ce qu'est une voie pour Arduino
    static const quint16 arduino_uno_vendor_id=9025;
    static const quint16 arduino_uno_product_id=67;
    QString arduino_port_name;
    bool arduino_is_available;
    QByteArray data;
};

#endif // RFID_H
