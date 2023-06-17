#include "BluetoothSerial.h"
#include <Servo.h>

Servo wingR;  // create a servo object for wing 1
Servo wingL;  // create a servo object for wing 2

char t;
int wingLpin = 22;
int wingRpin = 23;

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

void setup() {
  wingR.attach(wingRpin);  // attaches wing 1 on pin 9 to the servo object
  wingL.attach(wingLpin); // attaches wing 2 on pin 10 to the servo object

  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    t = SerialBT.read();
    Serial.write(t);
    if(t == 'F'){
      flap();
    }
    if(t == 'U'){
      rise();
    }
    if(t == 'D'){
      fall();
    }
    if(t == 'L'){
      left();
    }
    if(t == 'R'){
      right();
    }
  }
  delay(20);
}
void flap(){
  for(int i=0; i<3; i++){
    Serial.println("FLAPPING");
    wingL.write(30);   // sets wing 1 position to 60 degrees
    Serial.println("wingL = 30");
    wingR.write(180);  // sets wing 2 position to -30 degrees
    Serial.println("wingR = 180");
    delay(200);       // waits for 1 second
    wingL.write(120);    // sets wing 1 position to 0 degrees
    Serial.println("wingL = 120");
    wingR.write(90);  // sets wing 2 position to 180 degrees
    Serial.println("wingR = 90");
    delay(500);       // waits for 1 second
  }
}
void rise(){
  //Rising function
  Serial.println("RISING");
  wingL.write(90);
  Serial.println("wingL = 90");
  wingR.write(140);
  Serial.println("wingR = 140");
}
void right(){
  //Right Turn Function
  Serial.println("TURN RIGHT");
  wingL.write(120);
  Serial.println("wingL = 120");
  wingR.write(180);
  Serial.println("wingR = 180");
}
void fall(){
  //Falling function
  Serial.println("FALLING");
  wingL.write(50);
  Serial.println("wingL = 50");
  wingR.write(180);
  Serial.println("wingR = 180");
}
void left(){
  //Left Turn function
  Serial.println("TURN LEFT");
  wingL.write(45);
  Serial.println("wingL = 45");
  wingR.write(110);
  Serial.println("wingR = 110");
}
