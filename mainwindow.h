#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "commande.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_tableView_3_activated(const QModelIndex &index);

    void on_add_btn_3_clicked();

    void on_button_supprimer_3_clicked();

    void on_button_modifier_3_clicked();

    void on_tri_prix_3_clicked();

    void on_tri_idc_3_clicked();

    void on_tri_date_3_clicked();

    void on_rechercher_3_clicked();

    void on_PDF_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_tabWidget_4_currentChanged(int index);

    void on_chercher_3_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    commande c;
};

#endif // MAINWINDOW_H
