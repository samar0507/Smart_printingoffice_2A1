//#ifndef DIALOG_H
#define DIALOG_H
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QMainWindow>

#include <QDialog>

namespace Ui {
class dialog;
}

class dialog : public QDialog
{
    Q_OBJECT

public:
    explicit dialog(QWidget *parent = nullptr);
    ~dialog();

private slots:
    void on_pushButton_ON_clicked();

    void on_pushButton_OFF_clicked();

    void serial_read();


    //void on_lcdNumber_overflow();

    void update_dist(const QString );
private:
    Ui::dialog *ui;
    QSerialPort *serial;
    QString portname;
    quint16 vendorId;
    quint16 productId;
    bool arduino_available;
    void arduino_init();
    QByteArray serialData;
    QString serialBuffer;
};
