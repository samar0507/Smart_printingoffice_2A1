#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "client.h"
#include "commande.h"
#include "arduino.h"
#include "humidite.h"
#include "produits.h"
#include "employes.h"
#include "dialog.h"
#include "fournisseurs.h"
#include "notification.h"
#include "statistiques.h"
#include "rfid.h"
#include<QWidget>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class QCamera;
class QCameraViewfinder;
class QCameraImageCapture;
class QVBoxLayout;
class QMenu;
class QAction;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
arduino a;
private slots:

void on_add_btn_3_clicked();

void on_button_supprimer_3_clicked();

void on_button_modifier_3_clicked();












    void update_label();

    void on_g_client_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_27_clicked();

    void on_pushButton_25_clicked();

    void on_ajout_cl_clicked();

    void on_modif_cl_clicked();

    void on_lineEdit_search_cl_cursorPositionChanged(int arg1, int arg2);

    void on_excel_cl_clicked();

    void on_supp_cl_clicked();

    void on_fidelite_clicked();

    void on_qrcode_cl_clicked();

    void on_tab_cl_activated(const QModelIndex &index);

    void on_g_produit_clicked();

    void on_pb_ajouter_clicked();

    void on_pb_modifier_clicked();

    void on_l_idm_currentIndexChanged(const QString &arg1);

    void on_pb_supprimer_clicked();

    void on_pb_import_image_clicked();

    void on_pb_supprimer_tout_clicked();

    void on_tri_nom_clicked();

    void on_tri_date_clicked();

    void on_tri_id_clicked();

    void on_pb_pdf_clicked();

    void on_stat_clicked();

    void on_rech_textEdited(const QString &arg1);

    void on_refresh_mod_clicked();




    void on_pushButton_32_clicked();

    void on_pushButton_33_clicked();

    void on_pushButton_34_clicked();

    void on_pushButton_35_clicked();

    void on_pushButton_36_clicked();

    void on_g_emp_clicked();




    /*employés*/
    void on_add_btn_clicked();

    void on_del_btn_clicked();

    void on_mod_btn_clicked();

    void on_load_butt_clicked();

    void on_tab_id_2_activated(const QModelIndex &index);

    void leer();

    void on_qr_clicked();

    void on_insertion_photo_clicked();

    void on_ard_clicked();

    void on_CHAT_clicked();

    //void on_tri_resp_clicked();

    void on_tri_nom2_clicked();

    void on_tri_prenom_clicked();

    void on_cherche_textChanged(const QString &arg1);




   /* void on_insertion_photo_clicked();

      void on_tri_resp_clicked();



      void on_tri_prenom_clicked();

/    void on_rechercher_clicked();

      void on_enviar_clicked();

      void on_tab_id_2_activated(const QModelIndex &index);

      void on_qr_clicked();

      void on_tab_employes_activated(const QModelIndex &index);

      void  on_connexion_clicked();
      void leer();

      void on_CHAT_clicked();

      void on_cherche_textChanged(const QString &arg1);

      void on_pushButton_clicked();*/

    void on_g_comm_clicked();

//    void on_add_btn2_clicked();

//    void on_del_btn2_clicked();

//    void on_update_btn_clicked();

//    void on_delete_all_btn_clicked();
//    void on_tab_id_21_activated(const QModelIndex &index);


    void on_g_four_clicked();

//    void on_del_btn_2_clicked();

//    void on_delete_2_clicked();

//    void on_addto_clicked();

   void on_ara_clicked();

    void on_pushButton_2_clicked();

    void on_PDF_clicked();


    void on_tabWidget_4_currentChanged(int index);

    void on_pushButton_4_clicked();

  void on_tri_prix_3_clicked();
  void on_tri_idc_3_clicked();
  void on_tri_date_3_clicked();
  //void on_chercher_3_cursorPositionChanged(int arg1, int arg2);
  void on_chercher_3_textChanged(const QString &arg1);

//Fournisseurs
  void on_btn_add_clicked();

  void on_tri_pr_nom_clicked();

  void on_tri_pr_id_clicked();

  void on_tri_pr_fin_clicked();


  void on_tri_pr_deb_clicked();

  void on_search_id_textChanged(const QString &arg1);

  void on_btn_del_clicked();

  void on_btn_del_all_clicked();

  void on_id_tab_activated(const QModelIndex &index);

  void on_btn_update_clicked();

  void on_btn_browse_clicked();

  void sendMail();

  void mailSent(QString);

  void browse();

  void on_fournisseurs1_3_clicked();

  void on_fournisseurs2_3_clicked();

  void on_fournisseurs3_3_clicked();

  void on_fournisseurs4_3_clicked();

  void on_fournisseurs5_3_clicked();

  void update_label_uid();

  void on_pushButton_29_clicked();

  void on_pushButton_28_clicked();

  void on_pushButton_26_clicked();

  void on_pushButton_23_clicked();

  void on_pushButton_22_clicked();

  void on_pushButton_30_clicked();

  void on_pushButton_39_clicked();

  void on_pushButton_38_clicked();

  void on_pushButton_37_clicked();

  void on_pushButton_31_clicked();

  void on_pushButton_44_clicked();

  void on_pushButton_43_clicked();

  void on_pushButton_42_clicked();

  void on_pushButton_41_clicked();

  void on_pushButton_40_clicked();

  void on_tablecom_activated(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    client cl;
humidite h;
    QCamera *mCamera;
   QCameraViewfinder *mQCameraViewfinder;
    QCameraImageCapture *mQCameraImageCapture;
   QVBoxLayout   *mLayout;
   QMenu *mOptionsMenu;
   QAction *mEncenderAction;
   QAction *mApAction;
   QAction *mCaptureAction;

   Produits P;
   arduino A;
   Notification n; QSystemTrayIcon *mysystem;
   int alert;

   /*employés*/
   employes e;
   QTcpSocket*mSocket;
   dialog *di;

   /*commande*/
   commande c;

   /* Fournisseurs */

   fournisseurs f;
   QStringList files;
   QString data;
   Arduino Ar;
   QString uid;
};
#endif // MAINWINDOW_H
