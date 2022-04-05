#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "fournisseurs.h"
#include <QMainWindow>
#include <QFileDialog>
#include "smtp.h"
#include <QtWidgets/QMessageBox>
#include <QPainter>
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
    void on_add_btn_clicked();

    void on_del_btn_clicked();

    void on_update_btn_clicked();

    void on_delete_all_btn_clicked();

    void on_browse_btn_clicked();

    void sendMail();

    void mailSent(QString);

    void browse();

    void on_tab_id_2_activated(const QModelIndex &index);


    void on_tri_nom_btn_clicked();


    void on_tri_id_btn_clicked();

    void on_tri_deb_btn_clicked();

    void on_tri_fin_btn_clicked();

    void on_search_btn_clicked();

    void on_pdf_export_clicked();

    void on_pushButton_clicked();

    void on_search_textChanged(const QString &arg1);

    void on_fournisseur1_linkActivated(const QString &link);

    void on_fournisseurs1_clicked();

    void on_fournisseurs2_clicked();

    void on_fournisseurs3_clicked();

    void on_fournisseurs4_clicked();

    void on_fournisseurs5_clicked();

private:
    Ui::MainWindow *ui;
    fournisseurs f;
    QStringList files;
};
#endif // MAINWINDOW_H
