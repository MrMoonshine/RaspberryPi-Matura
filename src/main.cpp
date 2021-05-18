#include <QApplication>
#include <QGridLayout>
#include <QLabel>
#include <iostream>
#include <QPushButton>
#include <QCoreApplication>
#include <wiringPi.h>
#include <ctime>
#include <csignal>

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
    wiringPiSetupGpio();

    signal(SIGINT, cleanLeds);

    srand(time(NULL));

    //ExampleButton *b1 = new ExampleButton();
    Wcollection *mainw = new Wcollection();
    mainw->show();

    //programm runs infinitely
    return a.exec();
}
