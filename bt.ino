#include <AFMotor.h>
#define Speed 170

AF_DCMotor M1(1);
AF_DCMotor M2(2);

const int TRIG_PIN = 23;
const int ECHO_PIN = 22;
const int DISTANCE_TRESHOLD = 30;
int ledPin = 24;
//const int buzzer = 5;

float duration_us, distance_cm;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(ledPin, OUTPUT);
  //pinMode(buzzer, OUTPUT);

  M1.setSpeed(Speed);
  M2.setSpeed(Speed);


}


void loop() {
  bluetoothControl();
}

void bluetoothControl() {
  //Get the Bluetooth control remote values

  if (Serial1.available() > 0) {
    char value = Serial1.read();
    Serial1.println(value);

    if (value == 'U') {
      forward();
    } else if (value == 'D') {
      backward();
    } else if (value == 'L') {
      left();
    } else if (value == 'R') {
      right();
    } else if (value == 'S') {
      Stop();
    }
  }
}

/******************Motor functions*****************/
void forward() {
  Serial.println("Forward");

  M1.run(BACKWARD);
  M2.run(FORWARD);

}


void backward() {


  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration_us = pulseIn(ECHO_PIN, HIGH);
  distance_cm = 0.017 * duration_us;

  Serial.println(distance_cm);

  if (distance_cm <  DISTANCE_TRESHOLD)
  {// tone(buzzer, 1000);
    digitalWrite(ledPin, HIGH);
    delay(100);
     digitalWrite(ledPin, LOW);
    Stop();
  }
  else
  {
    //noTone(buzzer);
     M1.run(FORWARD);
     M2.run(BACKWARD);
    delay(1000);
  }

  Serial.println("Backward");
  
}



void right() {
  Serial.println("Right");
  M1.run(BACKWARD);
  M2.run(BACKWARD);
}

void left() {
  Serial.println("Left");
  M1.run(FORWARD);
  M2.run(FORWARD);
}

void Stop() {
  Serial.println("Stop");
  M1.run(RELEASE);
  M2.run(RELEASE);
}
