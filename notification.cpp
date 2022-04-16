#include "notification.h"
#include <QSystemTrayIcon>
#include<QString>

  Notification::Notification()
  {
      num=0;
  }
  Notification::Notification(QString titre,QString text)
  {
      this->text=text;
      this->titre=titre;
  }

  void Notification::afficher()
  {

      QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
      notifyIcon->setIcon(QIcon(":/new/prefix1/notif.png"));
      notifyIcon->show();;
      notifyIcon->showMessage(titre,text,QSystemTrayIcon::Information,20000);
  }
