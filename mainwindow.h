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
    void on_add_btn_clicked();

    void on_button_supprimer_clicked();

    void on_button_modifier_clicked();

private:
    Ui::MainWindow *ui;
    commande c;
};

#endif // MAINWINDOW_H
