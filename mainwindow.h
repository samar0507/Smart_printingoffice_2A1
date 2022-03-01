#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "fournisseurs.h"
#include <QMainWindow>

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

    void on_detele_all_btn_clicked();

private:
    Ui::MainWindow *ui;
    fournisseurs f;
};
#endif // MAINWINDOW_H
