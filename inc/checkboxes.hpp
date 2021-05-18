#pragma once

#include <QWidget>
#include <QButtonGroup>
#include <QRadioButton>
#include <QCheckBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

class CheckBoxes : public QWidget{
    Q_OBJECT
public:
  CheckBoxes(QWidget *parent = nullptr);
private:
  QVBoxLayout *cbLay();
  QVBoxLayout *rbLay();
  //Button Group for checkboxes and radio buttons
  QButtonGroup *rbg;
  QLabel *cbl, *rbl;
private slots:
  void setLabel(int state);
  void setRLabel(int state);
};
