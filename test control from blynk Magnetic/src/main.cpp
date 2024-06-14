// /*************************************************************
//   Blynk is a platform with iOS and Android apps to control
//   ESP32, Arduino, Raspberry Pi and the likes over the Internet.
//   You can easily build mobile and web interfaces for any
//   projects by simply dragging and dropping widgets.

//     Downloads, docs, tutorials: https://www.blynk.io
//     Sketch generator:           https://examples.blynk.cc
//     Blynk community:            https://community.blynk.cc
//     Follow us:                  https://www.fb.com/blynkapp
//                                 https://twitter.com/blynk_app

//   Blynk library is licensed under MIT license
//   This example code is in public domain.

//  *************************************************************
//   This example runs directly on ESP32 chip.

//   NOTE: This requires ESP32 support package:
//     https://github.com/espressif/arduino-esp32

//   Please be sure to select the right ESP32 module
//   in the Tools -> Board menu!

//   Change WiFi ssid, pass, and Blynk auth token to run :)
//   Feel free to apply it to any other example. It's simple!
//  *************************************************************/

// /* Comment this out to disable prints and save space */
// #define BLYNK_PRINT Serial

/* Fill in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "xxxxx"
#define BLYNK_TEMPLATE_NAME "xxxxxx"  
#define BLYNK_AUTH_TOKEN "xxxxxxx"      //ใส่ token ที่ได้จาก blynk

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <VL53L1X.h>
//int Relay_pin = 14;
int Relay_pin1 = 18;
int Relay_pin2 = 19;

// int Led_pin = 4;
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "xxxxxx";   //ใส่ชื่อ wifi ที่เราจะใช้เชื่อมต่อ
char pass[] = "xxxxxx";   //ใส่รหัส wifi ที่เราจะใช้เชื่อมต่อ
VL53L1X sensor;
void setup()
{
  // Debug console
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  pinMode(Relay_pin,OUTPUT);
  pinMode(Relay_pin1,OUTPUT);
  pinMode(Relay_pin2,OUTPUT);
  Wire.begin();
  Wire.setClock(400000); // use 400 kHz I2C

  // sensor.setTimeout(500);
  // if (!sensor.init())
  // {
  //   Serial.println("Failed to detect and initialize sensor!");
  //   while (1);
  // }
  // sensor.setDistanceMode(VL53L1X::Long);
  // sensor.setMeasurementTimingBudget(50000);
  // sensor.startContinuous(50);
  

  
}

void loop()
{
  Blynk.run();
  // digitalWrite(Relay_pin2,HIGH);
  // // digitalWrite(Relay_pin1,HIGH);
  // delay(100);
  // digitalWrite(Relay_pin1,HIGH);
  // delay(100);
  // digitalWrite(Relay_pin2,LOW);
  // digitalWrite(Relay_pin1,LOW);

//   int distance = sensor.read()/10;
//   Serial.print(distance);
//   if (sensor.timeoutOccurred()){
//      Serial.print(" TIMEOUT"); 
//   }
//   if(distance <= 10){             //ถ้าLaser วัดได้น้อยกว่า10 Relay จะทำงาน
//     digitalWrite(Relay_pin,LOW);
//   }else{
//     digitalWrite(Relay_pin,HIGH);
//   }
//   Blynk.virtualWrite(V2,distance);  //ส่งค่าขึ้นBlynk
//   Serial.println();
//   delay(2000);
}
BLYNK_WRITE(V3) //Red Switch
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  
  if (pinValue == 1){
    digitalWrite(Relay_pin1,HIGH);
    delay(100);
    digitalWrite(Relay_pin1,LOW);
    Serial.println("Relay on");
  } else if (pinValue == 0) {
    digitalWrite(Relay_pin1,HIGH);
    delay(100);
    digitalWrite(Relay_pin1,LOW);
    Serial.println("Relay off");
  }
  
  Serial.print("Red button value is: "); // printing value to serial monitor
  Serial.println(pinValue);
}
BLYNK_WRITE(V4) // Green Switch
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  
  if (pinValue == 1){
    digitalWrite(Relay_pin2,HIGH);
    delay(100);
    digitalWrite(Relay_pin2,LOW);
    Serial.println("Relay on");
  } else if (pinValue == 0) {
    digitalWrite(Relay_pin2,LOW);
    delay(100);
    Serial.println("Relay off");
  }
  
  Serial.print("Green button value is: "); // printing value to serial monitor
  Serial.println(pinValue);
}
