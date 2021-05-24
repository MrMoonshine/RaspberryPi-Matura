#include <QApplication>
#include <QGridLayout>
#include <QLabel>
#include <iostream>
#include <QPushButton>
#include <QCoreApplication>
#include <wiringPi.h>
#include <ctime>
#include <csignal>

#include <gpio.hpp>
#include <franzboard.h>
#include <wcollection.hpp>
#include <examplebutton.hpp>

static const unsigned short maxConnections = 32;

void cleanLeds(int signum){
    std::cout << std::endl << "Closing Server. Goodbye ~<3" << std::endl;
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon::fromTheme("start-here"));

    signal(SIGINT, cleanLeds);

    srand(time(NULL));
    GPIO::init();

    //ExampleButton *b1 = new ExampleButton();
    Wcollection *mainw = new Wcollection();
    mainw->show();

    //programm runs infinitely
    return a.exec();
}
