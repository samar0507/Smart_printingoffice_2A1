#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFontDialog>
#include <QMessageBox>
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


void MainWindow::on_font_btn_clicked()
{
    bool ok;
      QFont font = QFontDialog::getFont(&ok, this);
      if (ok) {
          // font is set to the font the user selected
      } else {
          // the user canceled the dialog; font is set to the default
          // application font, QApplication::font()
      }
}

void MainWindow::on_submit_btn_clicked()
{
    QMessageBox::information(NULL,tr("message"),tr("User %1 %2 is %3 years old and works as %4")
                             .arg(ui->lineEdit->text())
                             .arg(ui->lineEdit_2->text())
                             .arg(ui->lineEdit_3->text())
                             .arg(ui->lineEdit_4->text()));
}
