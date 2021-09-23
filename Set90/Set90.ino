#include <ESP32Servo.h>

Servo servo;

int servoPin = 5;

void setup() {
	servo.setPeriodHertz(50);
	servo.attach(servoPin, 500, 2500);
  servo.write(90);
}

void loop() {
}
