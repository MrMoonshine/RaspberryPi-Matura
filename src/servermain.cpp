#include <servermain.hpp>

ServerMain::ServerMain() : QTcpServer(){
  //Push all gpios into a queue
  openQueue.push(new GPIO(FB_LED_0));
  openQueue.push(new GPIO(FB_LED_1));
  openQueue.push(new GPIO(FB_LED_2));
  openQueue.push(new GPIO(FB_LED_3));
  //port is 0 means server is not running
  port = 0;
}

void ServerMain::incomingConnection(qintptr socketDescriptor){
  if(openQueue.empty()){
    clog << "All LEDs are used. Denying further connections." << endl;
    QTcpSocket *failsock = new QTcpSocket();
    failsock->setSocketDescriptor(socketDescriptor);
    failsock->write("No free LED available\r\n");
    failsock->close();
    return;
  }
  qDebug() << socketDescriptor << " is connecting...";

  ServerThr *thr = new ServerThr(openQueue.front(),socketDescriptor);
  openQueue.pop();
  connect(this,&ServerMain::terminate,thr,&ServerThr::serverDisconnect);
  connect(thr,&ServerThr::freeLed,this,&ServerMain::shift2open);
  connect(thr,&QThread::finished,thr,&QObject::deleteLater);
  thr->start();
}

void ServerMain::shift2open(GPIO* gpio){
  openQueue.push(gpio);
}

void ServerMain::start(unsigned short portnum){
  if(port > 0)
  return;

  port = portnum;
  if(!this->listen(QHostAddress::Any, port))
      cerr << "Failed to start the server!" << endl;
  else
      cout << "Started the server Successfully!" << endl;
}

void ServerMain::stop(){
  port = 0;
  emit terminate();
  close();
}
