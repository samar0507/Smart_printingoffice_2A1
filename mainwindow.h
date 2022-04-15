#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "client.h"
#include "arduino.h"
#include "humidite.h"
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
};
#endif // MAINWINDOW_H
