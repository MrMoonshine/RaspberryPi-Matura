#ifndef SERVERTHR_HPP
#define SERVERTHR_HPP

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QTcpServer>
#include <QTimer>
#include <gpio.hpp>
#include <iostream>
#include <chrono>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <ratio>

using namespace std;

static const string motd = "<->-<->-Templateserver-<->-<->\r\n";
static const string goodbye = "<->-<->-Goodbye-<->-<->\r\n";

class ServerThr : public QThread{
  Q_OBJECT
public:
  ServerThr(GPIO* gpio_i, qintptr sockid, QObject *parent = nullptr);
  void run() override;
private:
  qintptr sockdesc;
  QTcpSocket* mSocket;
  QTcpServer* eServer;
  QTimer *timerf, *timerdc;
  GPIO* gpio;
  std::chrono::milliseconds period, thigh;
public slots:
  void clientDisconnect();
  void serverRead();
  void serverDisconnect();
private slots:
  void ledEnable();
  void ledDisable();
signals:
  void freeLed(GPIO* led);
};

#endif // SERVERTHR_HPP
