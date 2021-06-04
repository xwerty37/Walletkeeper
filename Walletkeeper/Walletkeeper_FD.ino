//#include <stdio.h>   필요없음
#include <SoftwareSerial.h>
#define RED 9
#define GREEN 10
#define BLUE 11
#define Tx 7      //0,1은 쓸수없음 7,8로 바꾸기
#define Rx 8      //0,1은 쓸수없음

SoftwareSerial bluetooth(Tx,Rx);

int echoPin1 = 2;   // 핀번호는 원래대로 바꿔도됨 원래 2
int trigPin1 = 4;   //
int buzzer = 6;
char val;
int functionON=0;  //기능 off 로 시작

void setup(){
  Serial.begin(9600);
  bluetooth.begin(9600);
  pinMode(trigPin1,OUTPUT);  //써주어야함
  pinMode(echoPin1,INPUT);  //써주어야함
  
}
void loop(){
  val=0;      //초기화 해줌
  
  if(bluetooth.available()){
    val=bluetooth.read(); 
  
  // val = bluetooth.read();
    Serial.print("입력값:"); 
    Serial.println(val);
    if(val == 'a')   //기능 on
        functionON=1;
    else
        functionON=0;
  }    
  // 초음파를 보낸다. 다 보내면 echo가 HIGH 상태로 대기하게 된다.

    if(functionON==1){
        //digitalWrite(trigPin1, LOW);
        //digitalWrite(echoPin1, LOW);
        //delayMicroseconds(2);
        digitalWrite(trigPin1, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin1, LOW);
        // echoPin 이 HIGH를 유지한 시간을 저장 한다.
          unsigned long duration = pulseIn(echoPin1, HIGH);
          
        float distance1 = ((float)(340.0 * duration) / 10000.0) / 2.0; 
        
        Serial.print("1번:"); 
        Serial.print(distance1);
        Serial.println("cm");
          if (distance1 > 1 && distance1 <= 6) {
          analogWrite(buzzer,20);
          analogWrite(RED, 255);       // 빨간색 조절
          analogWrite(GREEN,0);  // 초록색 조절
          analogWrite(BLUE, 255);      // 파란색 조절
          }
          else if (distance1 > 6 && distance1 <= 15) {
            analogWrite(buzzer,100);
            analogWrite(RED, 255);       // 빨간색 조절
            analogWrite(GREEN,255);  // 초록색 조절
            analogWrite(BLUE, 0);      // 파란색 조절
          }
          else if (distance1 > 15 && distance1 <= 50) {  //300->30으로 줄임 도로 원위치시키기
            analogWrite(buzzer,150);
            analogWrite(RED, 0);       // 빨간색 조절
            analogWrite(GREEN,255);  // 초록색 조절
            analogWrite(BLUE, 255);      // 파란색 조절
          } 
          else {                          //function off시
            analogWrite(RED, 255);       // 끄기- 기능 off시 끄기
            analogWrite(GREEN,255);  // 끄기
            analogWrite(BLUE, 255);  //끄기
            analogWrite(buzzer,0);//끄기
          }
          delay(300);
    }
  }
