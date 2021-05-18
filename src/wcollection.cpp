#include <wcollection.hpp>

Wcollection::Wcollection(QWidget *parent) : QToolBox(parent){
  addItem(new ExampleButton(this),"Push-Button");
  addItem(new CheckBoxes(this),"Checkboxes");
  addItem(new Lcd(this),"Displays W.I.P");
  addItem(new QLabel("Oida"),"Oida");
}
