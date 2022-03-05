#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include "client.h"
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
    void on_pushButton_4_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_19_clicked();

    void on_lineEdit_search_cursorPositionChanged(int arg1, int arg2);

    void on_pushButton_2_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_3_clicked();

    void on_tab_cl_activated(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    client cl;
};
#endif // MAINWINDOW_H
