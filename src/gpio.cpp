#include <gpio.hpp>
GPIO::GPIO(gpio_num_t pin_i, gpio_dir_t direction_i) : QObject(){
  pin = pin_i;
  direction = direction_i;

  switch (direction) {
    case OUT:
      pinMode(pin,OUTPUT);
      break;
    case IN:
      pinMode(pin,INPUT);
      break;
    default:
      break;
    }
}

GPIO::~GPIO(){
  digitalWrite(pin,LOW);
}

void GPIO::write(uint8_t state){
  digitalWrite(pin,state & 1);
}

void GPIO::operator=(const uint8_t state){
  write(state);
}

void GPIO::operator!(){
  write(~read());
}

uint8_t GPIO::read(){
  return digitalRead(pin);
}

uint8_t GPIO::getPin(){
  return pin;
}

int GPIO::attach(void (*isr)(void), uint8_t edge){
  return wiringPiISR(pin, edge, isr);
}

void GPIO::delayChrono(std::chrono::milliseconds msec){
  delay(msec.count());
}

void GPIO::init(){
  wiringPiSetupGpio();
}
