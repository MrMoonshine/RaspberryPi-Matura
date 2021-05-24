#ifndef GPIO_HPP
#define GPIO_HPP
#include <iostream>
#include <QObject>
#include <chrono>
#include <wiringPi.h>
#include <franzboard.h>

typedef uint8_t gpio_num_t;
typedef enum {IN,OUT} gpio_dir_t;

class GPIO : public QObject{
  Q_OBJECT
public:
  GPIO(gpio_num_t pin_i, gpio_dir_t direction_i = OUT, QObject *parent = nullptr);
  ~GPIO();
  static void init();
  static void delayChrono(std::chrono::milliseconds msec);
  uint8_t read();
  uint8_t getPin();
  void operator=(const uint8_t state);
  void operator!();
  int attach(void (*isr)(void), uint8_t edge);
private:
  gpio_num_t pin;
  gpio_dir_t direction;
public slots:
  void write(uint8_t state);
};
#endif // GPIO_HPP
