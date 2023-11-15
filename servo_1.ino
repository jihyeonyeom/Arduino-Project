#include <LiquidCrystal_I2C.h>
#include<Servo.h>

Servo myservo;
LiquidCrystal_I2C lcd(0x27,16,2);

int seconds;
int prevtime = 0;

int hours = 0;
int mins = 0;

int ahours = 0;
int amins = 0;

void setup(){
  lcd.init();
  lcd.backlight();
  lcd.begin(16,2);
  Serial.begin(9600);
  Serial.begin(9600);
  myservo.attach(9);
  pinMode(8,OUTPUT);
  pinMode(10,INPUT);
}//setup()

void loop(){
  char theDay[4];
  int a = 0;
  int i = 0;
  int day;
  
  myservo.write(0);
  //시간 변경
  seconds = (millis() / 1000);
     if(prevtime < (seconds - 59))
     {
      mins++;
      prevtime = seconds;
     }
  
  //현재 시간 표시
  if(mins > 59)
     {
      hours++;
      mins = 0;
     } 
     
     if(hours > 23)
     {
      hours = 0; 
     }
  
  lcd.setCursor(1,0);
  lcd.print("Time ");
  if (hours < 10)
  {
    lcd.print("0");
    lcd.print(hours);
  }
  else
  {
    lcd.print(hours);
  }
    
    lcd.print(":");
    
  if (mins < 10)
  {
    lcd.print("0");
      lcd.print(mins);
  }
  else
  {
      lcd.print(mins);
  }
  
   lcd.print(":");
  
  if (seconds >59)
  {
    seconds = seconds-prevtime;
  }
  
  
  if (seconds < 10)
  {
    lcd.print("0");
    lcd.print(seconds);
  }
  else 
  {
    lcd.print(seconds);
  }
  
  //알람 시간
  lcd.setCursor(0,1);
  lcd.print("Alarm ");
  if(ahours < 10)
  {
    lcd.print("0");
    lcd.print(ahours);
  }
  else
    lcd.print(ahours);
    
    lcd.print(":");
    
  if (amins < 10)
  {
    lcd.print("0");
    lcd.print(amins);
  }
  else
  {
     lcd.print(amins);
  }
  if(amins > 59){
    ahours++;
    amins = 0;
  }
  if(ahours > 23){
    ahours = 0;
  }
    
  lcd.print(":00");
  delay(500);
  
  //시리얼 통신을 통해 알람시간을 입력받고 시리얼 모니터에 출력
  if(Serial.available()) {
    while(Serial.available()) {
      theDay[i] = Serial.read();
      i++;
    }
    day = atoi(theDay);
    ahours = day/100;
    amins = day%100;
    if(ahours > 23){
      ahours = 0;
      amins = 0;
    }
    if(amins > 60){
      ahours = 0;
      amins = 0;
    }
  }
  
  //알람이 울릴시간인지 체크
  if(ahours == hours && amins == mins && amins != 0){
    myservo.write(179);
    while(a<4){
      tone(8, 1000);
      delay(100);
      noTone(8);
      delay(100);
      tone(8, 1000);
      delay(100);
      noTone(8);
      delay(100);
      tone(8, 1000);
      delay(100);
      noTone(8);
      delay(100);
      tone(8, 1000);
      delay(100);
      noTone(8);
      delay(1000);
      a++;
    }
    ahours = 0;
    amins = 0;
  }
}//loop()
