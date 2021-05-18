#pragma once

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLCDNumber>
#include <QSlider>
#include <QDial>

class Lcd : public QWidget{
  Q_OBJECT
public:
  explicit Lcd(QWidget *parent = nullptr);
private:
  QVBoxLayout *buildDialDisplay();
  QVBoxLayout *buildRangeDisplay();

  QLCDNumber *dnumd, *rnumd;
  QDial *dial;
  QSlider *range;
signals:

public slots:
};
