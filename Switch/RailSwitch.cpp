#include "RailSwitch.h"
#include <Arduino.h>

RailSwitch::RailSwitch(int _pin) {
  pin = _pin;
  delay = 1000;
}

RailSwitch::RailSwitch(int _pin, unsigned long _delay) {
  pin = _pin;
  delay = _delay;
}

void RailSwitch::begin(void) {
  pinMode(pin, INPUT_PULLUP);
  attachInterruptArg(pin, &on_interrupt, this, FALLING);
}

void IRAM_ATTR on_interrupt(void *arg) {
  RailSwitch* s = static_cast<RailSwitch*>(arg);
  s->set_pushed();
}

void RailSwitch::set_pushed(void) {
  t = millis();
  pushed = true;
}

void RailSwitch::reset_pushed(void) {
  t = 0;
  pushed = false;
}

bool RailSwitch::is_pushed(void) {
  unsigned long now;

  if (pushed) {
    now = millis();
    if (now - t < delay) {
      return true;
    }
    else {
      reset_pushed();
      return false;
    }
  }
  else {
    return false;
  }
}
