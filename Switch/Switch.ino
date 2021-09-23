#include <ESP32Servo.h>
#include "RailSwitch.h"

int c_angle = 110;
int servoPin = 5;
int swPin = 25;

bool stat = false;
bool is_pushed = false;
RailSwitch sw(swPin);
Servo servo1;

void setup() {
  sw.begin();
  servo1.setPeriodHertz(50);
  servo1.attach(servoPin, 500, 2500);
  servo1.write(90);
}

void loop() {
  if (sw.is_pushed() && !is_pushed) {
    is_pushed = true;
    stat = !stat;
    if (stat) {
      servo1.write(c_angle);
    }
    else {
      servo1.write(90);
    }
  }
  else if (!sw.is_pushed()) {
    is_pushed = false;
  }
}
