#include <examplebutton.hpp>

ExampleButton::ExampleButton(QWidget *parent) : QWidget(parent){
  button = new QPushButton("Alter Colour");
  rainbow = new QLabel("UwU Rainbow OxO");
  colourinfo = new QLabel("Default Colour");

  //Connect button click with colour change
  connect(
        button,
        &QPushButton::clicked,
        this,
        &ExampleButton::alterColour
  );

  QVBoxLayout *vlay = new QVBoxLayout();
  vlay->addWidget(rainbow);
  vlay->addWidget(button);
  vlay->addWidget(colourinfo);
  vlay->addWidget(new QLabel("QPushbutton emits clicked(void).\nThis needs to be connected to the desired slot function"));
  vlay->addWidget(new QLabel("The button gets connected to the function \nwhich sets the stylesheet of the QLabel above"));
  setLayout(vlay);
}

void ExampleButton::alterColour(){
  unsigned int colour = rand() % 0xFFFFFF;

  //sometimes a 5 digit colour gets generated. the program doesn't handle them to keep it brief
  if(colour < 0x100000){
    colour += 0x100000;
  }

  std::stringstream ss;
  ss << std::hex << colour;
  colourinfo->setText(QString(ss.str().c_str()));  
  rainbow->setStyleSheet("background-color: #" + QString(ss.str().c_str()));
}
