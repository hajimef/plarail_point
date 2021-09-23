#include <ESP32Servo.h>

Servo servo;

int servoPin = 5;
int c_angle = 110;

void setup() {
	servo.setPeriodHertz(50);
	servo.attach(servoPin, 500, 2500);
}

void loop() {
  servo.write(90);
  delay(2000);
  servo.write(c_angle);
  delay(2000);
}
