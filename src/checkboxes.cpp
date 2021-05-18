#include <checkboxes.hpp>

CheckBoxes::CheckBoxes(QWidget *parent) : QWidget(parent){
    QHBoxLayout *hlay = new QHBoxLayout();
    hlay->addLayout(cbLay());
    hlay->addLayout(rbLay());
    setLayout(hlay);
}

QVBoxLayout *CheckBoxes::cbLay(){
    QVBoxLayout *vlay = new QVBoxLayout();
    cbl = new QLabel();
    vlay->addWidget(new QLabel("Checkboxes"));
    vlay->addWidget(new QLabel("Checkbox 3 is a\nTristate Checkbox"));

    QCheckBox *cb1 = new QCheckBox("Check &1",this);
    QCheckBox *cb2 = new QCheckBox("Check &2",this);
    QCheckBox *cb3 = new QCheckBox("Check &3",this);
    cb3->setTristate(true);

    connect(cb1,&QCheckBox::stateChanged,this,&CheckBoxes::setLabel);
    connect(cb2,&QCheckBox::stateChanged,this,&CheckBoxes::setLabel);
    connect(cb3,&QCheckBox::stateChanged,this,&CheckBoxes::setLabel);

    vlay->addWidget(cb1);
    vlay->addWidget(cb2);
    vlay->addWidget(cb3);

    vlay->addWidget(cbl);

    return vlay;
}

QVBoxLayout *CheckBoxes::rbLay(){
    QVBoxLayout *vlay = new QVBoxLayout();
    vlay->addWidget(new QLabel("Radiobuttons"));
    vlay->addWidget(new QLabel("Buttons were generated\nin a for loop"));
    rbg = new QButtonGroup();
    rbl = new QLabel();

    for(int a = 0; a < 3; a++){
      QRadioButton *rb = new QRadioButton("Radio &" + QString::number(a));
      vlay->addWidget(rb);
      rbg->addButton(rb,a);

      if(a==0)
      rb->setChecked(true);
    }
    setRLabel(0);

    //Unluckily in QT5.7 you need an Overload
    connect(
          rbg,
          qOverload<int>(&QButtonGroup::buttonClicked),
          this,
          &CheckBoxes::setRLabel
    );

    vlay->addWidget(rbl);
    return vlay;
}

void CheckBoxes::setLabel(int state){
  cbl->setText(QString("Checkbox state is: ") + QString::number(state));
}

void CheckBoxes::setRLabel(int state){
  rbl->setText(QString("Selected Radiobutton: ") + QString::number(state));
}
