#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_g_client_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}

void MainWindow::on_pushButton_21_clicked()
{
   ui->stackedWidget->setCurrentWidget(ui->page_2);
}

void MainWindow::on_pushButton_27_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}

void MainWindow::on_pushButton_25_clicked()
{
  ui->stackedWidget->setCurrentWidget(ui->page_2);
}
