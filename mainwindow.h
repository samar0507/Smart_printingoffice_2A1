#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "client.h"
#include "arduino.h"
#include "humidite.h"
#include "produits.h"
#include "notification.h"
#include "statistiques.h"
#include<QWidget>
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
};
#endif // MAINWINDOW_H
