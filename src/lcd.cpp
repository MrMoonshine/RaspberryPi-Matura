#include <lcd.hpp>

Lcd::Lcd(QWidget *parent) : QWidget(parent){
  QHBoxLayout *hlay = new QHBoxLayout();
  hlay->addLayout(buildDialDisplay());
  hlay->addLayout(buildRangeDisplay());
  setLayout(hlay);
}

QVBoxLayout *Lcd::buildDialDisplay(){
  QVBoxLayout *vlay = new QVBoxLayout();
  dnumd = new QLCDNumber();
  dial = new QDial();
  dial->setRange(0,100);

  connect(
        dial,
        &QDial::valueChanged,
        dnumd,
        qOverload<int>(&QLCDNumber::display)
  );

  vlay->addWidget(new QLabel("QDial-Value"));
  vlay->addWidget(dnumd);
  vlay->addWidget(dial);
  return vlay;
}

QVBoxLayout *Lcd::buildRangeDisplay(){
  QVBoxLayout *vlay = new QVBoxLayout();
  rnumd = new QLCDNumber();
  //Otherwise it is vertical
  range = new QSlider(Qt::Horizontal);
  range->setRange(0,100);

  connect(
        range,
        &QSlider::valueChanged,
        rnumd,
        qOverload<int>(&QLCDNumber::display)
  );

  vlay->addWidget(new QLabel("QSlider-Value"));
  vlay->addWidget(rnumd);
  vlay->addWidget(range);
  return vlay;
}
