#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QObject>
#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QLabel>
#include<QFileDialog>

#include "produits.h"

#include "notification.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void refresh();

    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_modifier_clicked();

    void on_l_idm_currentIndexChanged(const QString &arg1);


    void on_pb_import_image_clicked();

    void on_pb_supprimer_tout_clicked();

    void on_refresh_2_clicked();

    void on_tri_nom_clicked();

    void on_tri_date_clicked();

    void on_tri_id_clicked();

    void on_pb_rech_id_clicked();

    void on_pb_pdf_clicked();

    void on_pb_rech_nom_clicked();

    void on_stat_clicked();

    void on_rech_textEdited(const QString &arg1);

    void on_tabWidget_currentChanged(int index);

    void on_refresh_mod_clicked();

private:
    Ui::MainWindow *ui;
    Produits P;

 Notification n; QSystemTrayIcon *mysystem;

};
#endif // MAINWINDOW_H
