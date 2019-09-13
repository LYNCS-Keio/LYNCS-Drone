#include <Arduino.h>


//HardwareSerial Serial1(1)
//HardwareSerial Serial2(2);//UART2 IO16,17

#define RXD2 16
#define TXD2 17

void setup() {
  // Note the format for setting a serial port is as follows: Serial2.begin(baud-rate, protocol, RX pin, TX pin);
  Serial.begin(9600);
  //Serial1.begin(115200, SERIAL_8N1, RXD2, TXD2);
  //Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  //Serial.println("Serial Rxd is on pin: "+String(RX));

}


void loop(){

   if (Serial.available() > 0){
   // シリアルポートより1文字読み込む
   String str = Serial.readStringUntil(';');
   Serial.println(str);
   }

}
