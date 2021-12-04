#include <SoftwareSerial.h>
#define LED 13

SoftwareSerial mySerial(2, 3); // RX, TX

void setup(){
  pinMode(LED, OUTPUT); //debug用
  Serial.begin(9600); //シリアル通信の設定(子機と同じ番号で)
  mySerial.begin(9600);
}

char c;

void loop(){
  //PCから受け取る
  if(Serial.available()){
    c = (char)Serial.read();
    Serial.print(c);

    //子機へ送る
    mySerial.listen();
    mySerial.write(c);
    digitalWrite(LED, HIGH); 
  }else{
    digitalWrite(LED, LOW);
  }
}
