#ifndef WCOLLECTION_HPP
#define WCOLLECTION_HPP

#include <QWidget>
#include <QToolBox>
#include <QLabel>

#include <examplebutton.hpp>
#include <checkboxes.hpp>
#include <lcd.hpp>

class Wcollection : public QToolBox
{
  Q_OBJECT
public:
  explicit Wcollection(QWidget *parent = 0);
private:

signals:

public slots:
};

#endif // WCOLLECTION_HPP
