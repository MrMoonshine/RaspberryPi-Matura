#include <serverui.hpp>

ServerUI::ServerUI(QWidget *parent) : QWidget(parent){
  server = new ServerMain();
  QVBoxLayout *vlay = new QVBoxLayout();
  vlay->addLayout(portInput());
  vlay->addLayout(srvCtrlUi());
  vlay->addWidget(new QLabel("Each GPIO LED can be controlled\nby a server-slot; example:\npwm <f> <dc>\n(no) shutdown\n\nYou can also read the CPU temperature:\nshow temp"));
  setLayout(vlay);
}

QHBoxLayout *ServerUI::portInput(){
  portBox = new QSpinBox();
  //ports 0 to 1023 are reserved
  portBox->setRange(1024,USHRT_MAX);
  portBox->setValue(42069);

  QHostInfo info = QHostInfo::fromName("monschein.local");

  QHBoxLayout *hlay = new QHBoxLayout();
  hlay->addWidget(new QLabel(info.addresses().first().toString() + " on Port: "));
  hlay->addWidget(portBox);
  return hlay;
}

QHBoxLayout *ServerUI::srvCtrlUi(){
  startb = new QPushButton(QIcon::fromTheme("media-playback-start"),"start");
  stopb = new QPushButton(QIcon::fromTheme("process-stop"),"stop");

  connect(startb, &QPushButton::clicked,this,&ServerUI::portNumberHelper);
  connect(this,&ServerUI::portNumber,server,&ServerMain::start);
  connect(stopb, &QPushButton::clicked,server,&ServerMain::stop);

  QHBoxLayout *hlay = new QHBoxLayout();
  hlay->addWidget(startb);
  hlay->addWidget(stopb);
  return hlay;
}

void ServerUI::portNumberHelper(){
  emit portNumber(portBox->value());
}
