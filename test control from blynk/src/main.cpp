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
#define BLYNK_TEMPLATE_ID "TMPL6BWJWKFpk"
#define BLYNK_TEMPLATE_NAME "example"  
#define BLYNK_AUTH_TOKEN "gA42bMPFxTyPo_oEvCvll0llETv6frtk"      //ใส่ token ที่ได้จาก blynk

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <VL53L1X.h>
int Relay_pin = 14;
// int Led_pin = 4;
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "myguyisguy";   //ใส่ชื่อ wifi ที่เราจะใช้เชื่อมต่อ
char pass[] = "godguy2004";   //ใส่รหัส wifi ที่เราจะใช้เชื่อมต่อ
VL53L1X sensor;
void setup()
{
  // Debug console
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  pinMode(Relay_pin,OUTPUT);
  Wire.begin();
  Wire.setClock(400000); // use 400 kHz I2C

  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1);
  }

  // Use long distance mode and allow up to 50000 us (50 ms) for a measurement.
  // You can change these settings to adjust the performance of the sensor, but
  // the minimum timing budget is 20 ms for short distance mode and 33 ms for
  // medium and long distance modes. See the VL53L1X datasheet for more
  // information on range and timing limits.
  sensor.setDistanceMode(VL53L1X::Long);
  sensor.setMeasurementTimingBudget(50000);

  // Start continuous readings at a rate of one measurement every 50 ms (the
  // inter-measurement period). This period should be at least as long as the
  // timing budget.
  sensor.startContinuous(50);
}

void loop()
{
  Blynk.run();
  int distance = sensor.read()/10;
  Serial.print(distance);
  if (sensor.timeoutOccurred()){
     Serial.print(" TIMEOUT"); 
  }
  if(distance <= 10){
    digitalWrite(Relay_pin,LOW);
  }else{
    digitalWrite(Relay_pin,HIGH);
  }
  Blynk.virtualWrite(V2,distance);
  Serial.println();
  delay(2000);
}
BLYNK_WRITE(V1) // this command is listening when something is written to V1
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  
  if (pinValue == 1){
    digitalWrite(Relay_pin,LOW);
    Serial.println("Relay on");
  } else if (pinValue == 0) {
    digitalWrite(Relay_pin,HIGH);
    Serial.println("Relay off");
  }
  
  Serial.print("V1 button value is: "); // printing value to serial monitor
  Serial.println(pinValue);
}

//-----------------------------------

// #include <Wire.h>
// #include <Arduino.h>
// // Set I2C bus to use: Wire, Wire1, etc.
// #define WIRE Wire

// void setup() {
//   WIRE.begin();

//   Serial.begin(115200);
//   while (!Serial)
//      delay(10);
//   Serial.println("\nI2C Scanner");
// }


// void loop() {
//   byte error, address;
//   int nDevices;

//   Serial.println("Scanning...");

//   nDevices = 0;
//   for(address = 1; address < 127; address++ )
//   {
//     // The i2c_scanner uses the return value of
//     // the Write.endTransmisstion to see if
//     // a device did acknowledge to the address.
//     WIRE.beginTransmission(address);
//     error = WIRE.endTransmission();

//     if (error == 0)
//     {
//       Serial.print("I2C device found at address 0x");
//       if (address<16)
//         Serial.print("0");
//       Serial.print(address,HEX);
//       Serial.println("  !");

//       nDevices++;
//     }
//     else if (error==4)
//     {
//       Serial.print("Unknown error at address 0x");
//       if (address<16)
//         Serial.print("0");
//       Serial.println(address,HEX);
//     }
//   }
//   if (nDevices == 0)
//     Serial.println("No I2C devices found\n");
//   else
//     Serial.println("done\n");

//   delay(5000);           // wait 5 seconds for next scan
// }
