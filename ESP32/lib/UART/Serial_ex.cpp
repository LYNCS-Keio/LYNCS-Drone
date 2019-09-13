#include <Arduino.h>

//HardwareSerial Serial1(1)
//HardwareSerial Serial2(2);//UART2 IO16,17

#define RXD2 16
#define TXD2 17

void setup() {
  // Note the format for setting a serial port is as follows: Serial2.begin(baud-rate, protocol, RX pin, TX pin);
  Serial.begin(9600);
  //Serial1.begin(115200, SERIAL_8N1, RXD2, TXD2);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  //Serial.println("Serial Txd is on pin: "+String(TX));
  //Serial.println("Serial Rxd is on pin: "+String(RX));
}

void loop() { //Choose Serial1 or Serial2 as required
/*
  while (Serial2.available()) {
  Serial.print(char(Serial2.read()));
  }
*/
Serial.println("UART1");
Serial2.println("UART2");

}
