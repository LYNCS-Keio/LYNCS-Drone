#include <Arduino.h>
double Duration = 0; //受信した間隔
double Distance = 0; //距離

#define echoPin 2 // Echo Pin
#define trigPin 15 // Trigger Pin

void setup() {
Serial.begin( 9600 );
pinMode( echoPin, INPUT );
pinMode( trigPin, OUTPUT );
}

void loop() {
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite( trigPin, HIGH ); //超音波を出力
  delayMicroseconds( 10 ); //
  digitalWrite( trigPin, LOW );
  Duration = pulseIn( echoPin, HIGH ); //センサからの入力
  if (Duration > 0) {
    Duration = Duration/2; //往復距離を半分にする
    Distance = Duration*340*100/1000000; // 音速を340m/sに設定
    Serial.print("Distance:");
    Serial.print(Distance);
    Serial.println(" cm");
  }
  delay(500);
}