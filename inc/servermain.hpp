#ifndef SERVERMAIN_HPP
#define SERVERMAIN_HPP
#include <QTcpServer>
#include <QObject>
#include <QLabel>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHostInfo>
#include <QPushButton>
#include <climits>
#include <algorithm>
#include <string>
#include <sstream>
#include <list>
#include <queue>
#include <vector>

#include <franzboard.h>
#include <serverthr.hpp>
#include <gpio.hpp>

using namespace std;

class ServerMain : public QTcpServer{
  Q_OBJECT
public:
  ServerMain();
protected:
  void incomingConnection(qintptr socketDescriptor) override;
private:
  queue <GPIO*> openQueue;
  unsigned short port;
public slots:
  void start(unsigned short portnum);
  void stop();
  void shift2open(GPIO* gpio);
signals:
  void terminate();
};

#endif // SERVERMAIN_HPP
