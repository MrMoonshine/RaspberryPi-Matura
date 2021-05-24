#include <serverthr.hpp>

ServerThr::ServerThr(GPIO* gpio_i, qintptr sockid, QObject *parent) : QThread(parent){
  sockdesc = sockid;
  gpio = gpio_i;
  timerf = new QTimer();
  timerdc = new QTimer();

  timerf->moveToThread(this);
  timerdc->moveToThread(this);

  connect(timerf,&QTimer::timeout,this,&ServerThr::ledEnable);
  connect(timerdc,&QTimer::timeout,this,&ServerThr::ledDisable);
}

void ServerThr::run(){
    mSocket = new QTcpSocket();
    if(!mSocket->setSocketDescriptor(this->sockdesc)){
        // something's wrong, we just emit a signal
        qDebug() << "Error occurred during socket creation.";
        return;
    }

    connect(mSocket, &QTcpSocket::disconnected, this, &ServerThr::clientDisconnect);
    connect(mSocket, &QTcpSocket::readyRead, this, &ServerThr::serverRead,Qt::DirectConnection);
    qDebug() << sockdesc << " got connected";

    mSocket->write(motd.c_str());
    exec();
}

void ServerThr::clientDisconnect(){
    *gpio = 0;
    emit freeLed(gpio);
    qDebug() << sockdesc << " disconnected";
    mSocket->deleteLater();
    mSocket->close();
    exit(0);
}

void ServerThr::serverDisconnect(){
  mSocket->write(goodbye.c_str());
  mSocket->close();
}

void ServerThr::serverRead(){
 //qDebug() << "Server Reading";
    string recv = "";
    while (mSocket->bytesAvailable()){
        QString qstr = mSocket->readAll();
        qDebug() << qstr;
        recv = qstr.toStdString();
    }

    if(timerdc->isActive())
      timerdc->stop();
    if(timerf->isActive())
      timerf->stop();

    if(string::npos != recv.find("exit")){
      *gpio = 0;
      serverDisconnect();
    }

    if(string::npos != recv.find("no shut")){
      *gpio = 1;
    }else if(string::npos != recv.find("shut")){
      *gpio = 0;
    }else if(string::npos != recv.find("toggle")){
      !(*gpio);
    }else if(string::npos != recv.find("pwm")){
      int f = 0, dc = 0;
      sscanf(recv.c_str() ,"pwm %d %d",&f,&dc);

      if(f > 0){
        period = std::chrono::milliseconds(
              (int)(std::kilo::num/(float)f)
        );

        thigh = std::chrono::milliseconds(
              (int)(period.count()*((float)dc/100.0))  //dc is in percent
        );

        cout << "Starting pwm at ";
        cout << std::to_string(period.count());
        cout << "ms" << endl;
        timerf->start(period.count());
        GPIO::delayChrono(thigh);
        timerdc->start(period.count());
      }
    }else if(string::npos != recv.find("temp")){
       string line;
       stringstream ss;
       //round to 2 commas
       ss << std::fixed << std::setprecision(2);
       ifstream tempFile (TEMPERATURE_FILE);
       if (tempFile.is_open()){
           while ( getline (tempFile,line) ){
             ss << stof(line)/std::milli::den;
           }
           tempFile.close();
           ss << "°C";
           ss << endl;
           cout << ss.str();
           mSocket->write(ss.str().c_str());
       }else{
           mSocket->write("Error while reading Temperature\r\n");
       }
    }
}

void ServerThr::ledEnable(){
  *gpio = 1;
}

void ServerThr::ledDisable(){
  *gpio = 0;
}
