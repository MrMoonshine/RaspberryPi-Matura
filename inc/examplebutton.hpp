#ifndef EXAMPLEBUTTON_HPP
#define EXAMPLEBUTTON_HPP

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

#include <sstream>

class ExampleButton : public QWidget{
  Q_OBJECT
public:
  explicit ExampleButton(QWidget *parent = 0);
private:
    QPushButton *button;
    QLabel *rainbow, *colourinfo;
signals:

public slots:
    void alterColour();
};

#endif // EXAMPLEBUTTON_HPP
