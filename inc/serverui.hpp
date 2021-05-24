#pragma once

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHostInfo>
#include <QPushButton>
#include <climits>

#include <servermain.hpp>

class ServerUI : public QWidget{
  Q_OBJECT
public:
  explicit ServerUI(QWidget *parent = 0);
private:
  QHBoxLayout *portInput();
  QHBoxLayout *srvCtrlUi();

  QSpinBox *portBox;
  QPushButton *startb, *stopb;
  ServerMain* server;
signals:
  void portNumber(unsigned short port);
public slots:
  void portNumberHelper();
};
