#include <LiquidCrystal_I2C.h>
#include<Wire.h>
#include <Servo.h>
LiquidCrystal_I2C lcd(0x27 , 16,4);
Servo motorgiris;
Servo motorcikis;
int ac=15;
int btn=0;
int IR_alici[11]={3,4,5,6,7,8,9,10,2,A0};//3 Kapi algilama giris , 4 kapı algilama cıkıs 5,6,7,8,9,10 arac icin... 
int otopark_led[16]={23,24,26,28,30,32,34,36,38,40,35,25,27,29,31,33};//23-32 Arası Otopark aydınlatma ile otopark araç dolu yer tespit ledleri... 23-28 otopark araç tespit yer tespiti için 
int alarm=22;
int tespit=0;
int kntj = 6;
void setup() {
  pinMode(22,OUTPUT);
  digitalWrite(22,LOW);
  motorgiris.attach(11);//Giris kapısı...
  motorcikis.attach(12);//Cıkıs kapısı...
  lcd.begin();
  Serial.begin(9600);//Seri port başlatma işlemi ...
  
  for(int i=0;i<11;i++){
      pinMode(IR_alici[i],INPUT);
    }
  for(int y=0;y<16;y++){
      pinMode(otopark_led[y],OUTPUT);
    }
  for(int j=0;j<2;j++){
  lcd.home();
  lcd.print("Hosgeldiniz");
  lcd.setCursor(0,1);
  lcd.print("Smart Park");
  delay(2000);
  lcd.clear();
  delay(2000);
  }
  lcd.clear();
}
void Alev_Tespit(){
  for(int z=0;z<5;z++){
    lcd.home();
    lcd.print("DIKKAT YANGIN VAR");
    lcd.setCursor(3,1);
    lcd.print("ALARM ALARM");
    digitalWrite(22,HIGH);
    digitalWrite(23,HIGH);
    digitalWrite(24,HIGH);
    digitalWrite(26,HIGH);
    digitalWrite(28,HIGH);
    digitalWrite(30,HIGH);
    digitalWrite(32,HIGH);
    motorgiris.write(0);
    motorcikis.write(0);
    delay(1000);
    digitalWrite(23,LOW);
    digitalWrite(24,LOW);
    digitalWrite(26,LOW);
    digitalWrite(28,LOW);
    digitalWrite(30,LOW);
    digitalWrite(32,LOW);
    digitalWrite(22,LOW);
    delay(1000);
    lcd.clear();
  }}
void Kapi_giris(){
  if(digitalRead(5) == 0 && digitalRead(6) == 0 && digitalRead(7) == 0 && digitalRead(8) == 0 && digitalRead(9) == 0 && digitalRead(10) == 0){
    digitalWrite(23,HIGH);
    lcd.setCursor(2,1);
    lcd.print("Kapi Acilamaz");
    delay(3000);
    lcd.clear();
  }
 else {
  kntj--;
  lcd.setCursor(0,0);
  lcd.print("Kontenjan = ");
  lcd.setCursor(13,0);
  lcd.print(kntj);
  lcd.setCursor(3,1);
  lcd.print("Giris Kapisi .");
  motorgiris.write(90);
  if(digitalRead(3) == 0){
  motorgiris.write(0);}
  delay(5000);
  motorgiris.write(90);
  delay(2000);
  lcd.clear();
  }
  }
void Kapi_cikis(){
  lcd.setCursor(3,1);
  lcd.print("Cikis Kapisi .");
  kntj++;
  lcd.setCursor(0,0);
  lcd.print("Kontenjan = ");
  lcd.setCursor(13,0);
  lcd.print(kntj);
  motorcikis.write(90);
  if(digitalRead(4) == 0){
  motorcikis.write(0);}
  delay(5000);
  motorcikis.write(90);
  delay(2000);
  lcd.clear();
  }

void loop() {
  
  digitalWrite(23,LOW);
    if(digitalRead(3)==0){
      Kapi_giris();
      lcd.clear();
    }
     if(digitalRead(4)==0){
      Kapi_cikis();
      lcd.clear();
    }
     if(digitalRead(5)==0){
       digitalWrite(23,HIGH);//Kırmızı
       digitalWrite(35,LOW);
        
    }
     if(digitalRead(5)==1){
            digitalWrite(23,LOW);
            digitalWrite(35,HIGH);//yesil
            
          }
     if(digitalRead(6)==0){
      digitalWrite(24,HIGH);//Kırmızı
      digitalWrite(25,LOW);
       
    }
     if(digitalRead(6)==1){
            digitalWrite(24,LOW);
            digitalWrite(25,HIGH);
            
          }
     if(digitalRead(7)==0){
     // Serial.println(digitalRead(7));
      digitalWrite(26,HIGH);//yesil
      digitalWrite(27,LOW);
       
       
    }
     if(digitalRead(7)==1){
            digitalWrite(26,LOW);
            digitalWrite(27,HIGH);
             
          }
     if(digitalRead(8)==0){
      //Serial.println(digitalRead(8));
      digitalWrite(28,HIGH);//Kırmızı
      digitalWrite(29,LOW);     
       
    }
     if(digitalRead(8)==1){
            digitalWrite(28,LOW);
            digitalWrite(29,HIGH);
             
          }
     if(digitalRead(9)==0){
      //Serial.println(digitalRead(9));
     digitalWrite(30,HIGH);// Kırmızı
     digitalWrite(31,LOW);
      
      
    }
    if(digitalRead(9)==1){
            digitalWrite(30,LOW);
            digitalWrite(31,HIGH);
             
          }
     if(digitalRead(10)==0){
     // Serial.println(digitalRead(10));
     digitalWrite(32,HIGH);//Kırmızı
     digitalWrite(33,LOW);
      
    }
     if(digitalRead(10)==1){
            digitalWrite(32,LOW);
            digitalWrite(33,HIGH);
            
          }
      if(digitalRead(2)==0){
      Alev_Tespit();
      lcd.clear();
    }
     if(digitalRead(ac)==1){
      delay(250);
      btn++;
      if(btn==1){
      digitalWrite(34,HIGH);
      digitalWrite(36,HIGH);
      digitalWrite(38,HIGH);
      digitalWrite(40,HIGH);
      }
       if(btn==2){
        digitalWrite(34,LOW);
        digitalWrite(36,LOW); 
        digitalWrite(38,LOW);
        digitalWrite(40,LOW);
        btn=0;
        }
      }
    if (analogRead(A0)>700){
    //Serial.println(analogRead(A0));
    digitalWrite(34,HIGH);
    digitalWrite(36,HIGH);
    digitalWrite(38,HIGH);
    digitalWrite(40,HIGH);
    }
     if(analogRead(A0)<800){
      //Serial.println(analogRead(A0));
        digitalWrite(34,LOW);
        digitalWrite(36,LOW); 
        digitalWrite(38,LOW);
        digitalWrite(40,LOW); 
      }
     if(digitalRead(5) == 0 && digitalRead(6) == 0 && digitalRead(7) == 0 && digitalRead(8) == 0 && digitalRead(9) == 0 && digitalRead(10) == 0 ){
      lcd.setCursor(2,0);
      lcd.print("Otopark dolu");
      lcd.setCursor(2,1);
      lcd.print("Kontenjan = 0 ");
      digitalWrite(33,LOW);
      digitalWrite(31,LOW);
      digitalWrite(29,LOW);
      digitalWrite(27,LOW);
      digitalWrite(25,LOW);
      digitalWrite(23,HIGH);
      kntj=0;
      motorgiris.write(90);
      delay(2000);
      lcd.clear();
      }
    else {
      lcd.setCursor(5,0);
      lcd.print("OTONOM");
      lcd.setCursor(5,1);
  lcd.print("OTOPARK");
  lcd.blink();
      delay(500);
      lcd.clear();
      }
}
