#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "employes.h"
#include <QMainWindow>
#include <QTcpSocket>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class QUdpSocket;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    void on_add_btn_clicked();

    void on_del_btn_clicked();

    void on_mod_btn_clicked();

    void on_load_butt_clicked();

    void on_insertion_photo_clicked();



      void on_tri_resp_clicked();

      void on_tri_nom_clicked();

      void on_tri_prenom_clicked();

//      void on_rechercher_clicked();

      void on_enviar_clicked();

      void on_tab_id_2_activated(const QModelIndex &index);

      void on_qr_clicked();

      void on_tab_employes_activated(const QModelIndex &index);

      void  on_connexion_clicked();
      void leer();

      void on_CHAT_clicked();

      void on_cherche_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    employes e;
//    QUdpSocket *mSocket;
      QTcpSocket*mSocket;
};
#endif // MAINWINDOW_H
