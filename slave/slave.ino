#include <AccelStepper.h>
#define LED 13 //debug用
#define motorInterfaceType 1
#define MAX_MOTOR 6
#define MAX_STEP 1500
int No = 3; // 個体番号 使っていない
//char target = {'0', '1', '2', '3', '4'}; //NO=1
//char target = {'5', '6', '7', '8', 'd'}; //NO=2
char target[] = {'a', 'b', 'c', 'd', 'e', 'f'}; //NO=3
int flags[MAX_MOTOR]; //向き

AccelStepper steppers[MAX_MOTOR];

void setup(){
  pinMode(LED, OUTPUT); //debug用
  
  //mortor initialize
  for(int i=0; i<MAX_MOTOR; i++){
    //AccelStepper(motorInterfaceType, stepPin, dirPin)
    steppers[i] = AccelStepper(motorInterfaceType, (i+1)*2+1, (i+1)*2); 
    steppers[i].setMaxSpeed(500.0);
    steppers[i].setAcceleration(100.0);
  }
  //flagの初期化
  for(int i=0; i<6; i++){
    flags[i] = 0;
  }

  Serial.begin(9600); // シリアル通信の設定

}

int find_array(char c){
  for(int i=0; i<MAX_MOTOR; i++){
    if(c == target[i]){
      return i;
    }
  }
  return -1;
}


void loop(){
  while(Serial.available()){ // 受信データがある時
    char s = (char)Serial.read(); // 信号を読み取り、"s"に収納
    int n;
    if((n = find_array(s)) >= 0){
      steppers[n].moveTo(MAX_STEP * (1 - flags[n])); //flag=0ならMAX_STEPへ　flag=1なら0へ
      flags[n] ^= 1;
      digitalWrite(LED, HIGH); 
    }
  }

  for(int i=0; i<MAX_MOTOR; i++){
    if(steppers[i].distanceToGo() != 0){
      steppers[i].run();
    }
  }
  digitalWrite(LED, LOW);
}
