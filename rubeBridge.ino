/*
  Yún HTTP Client

 This example for the Arduino Yún shows how create a basic
 HTTP client that connects to the internet and downloads
 content. In this case, you'll connect to the Arduino
 website and download a version of the logo as ASCII text.

 created by Tom igoe
 May 2013

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/HttpClient

 */

#include <Bridge.h>
#include <HttpClient.h>
int myId = 1;
int meStatus = 0;
int sensorVal = 0;

#include <Stepper.h>
const int stepsPerRevolution = 90;  // change this to fit the number of steps per revolution
Stepper myStepper1(stepsPerRevolution, 8, 9, 10, 11);

#define SOUND_SENSOR A5
#define THRESHOLD_VALUE 600

void setup() {
  // Bridge takes about two seconds to start up
  // it can be helpful to use the on-board LED
  // as an indicator for when it has initialized
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();
  digitalWrite(13, HIGH);

  Serial.begin(9600);

  myStepper1.setSpeed(200);

  while (!Serial); // wait for a serial connection
}

void loop() {
  /*Serial.print("meStatus: ");
  Serial.println(meStatus);*/
  if (meStatus == 0) {
    checkStatus();
  } else if (meStatus == 1) {
    doThing();
  }
  //delay(5000);
}

void doThing() {
    Serial.println("!!!");
    for (int i = 0; i < 5; i++) {
      myStepper1.step(stepsPerRevolution);
      delay(50);
      myStepper1.step(-stepsPerRevolution);
      delay(50);
    }
    if (meStatus < 2) {
      doneWithThing();
    }
}

void checkStatus() {
  int sensorValue = analogRead(SOUND_SENSOR);//use A0 to read the electrical signal
  //Serial.print("sensorValue ");
  //Serial.println(sensorValue);
  if(sensorValue > THRESHOLD_VALUE) {
    //Matt put what u want to happen here plz
    meStatus = 1;
    doThing();
  }
  // Initialize the client library
  /*HttpClient client;

  // Make a HTTP request:
  client.get("http://im-rubegoldberg.herokuapp.com/devices/SB0/");
  Serial.println("???");
  // if there are incoming bytes available
  // from the server, read them and print them:
  while (client.available()) {
    char c = client.read();
    Serial.println(c);
    Serial.print("meStatus: ");
    Serial.println(meStatus);
    //Serial.println(int(c));
    //Serial.println(int(48+myId-1));
    if (int(c) == 49) {
      //doThing();
      meStatus = 1;
    }
  }
  Serial.flush();*/
}

void doneWithThing() {
  Serial.println("---");
  HttpClient client;
  client.get("http://im-rubegoldberg.herokuapp.com/devices/SE0/");
  while (client.available()) {
    char c = client.read();
    Serial.println(c);
  }
  Serial.flush();
  meStatus = 0;
}

