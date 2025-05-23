#include <LiquidCrystal.h>
const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int ir1=5;
int ir2=4;

int count=0;
#include <SimpleDHT.h>
int pinDHT11 = 2;
SimpleDHT11 dht11(pinDHT11);

int l1=A0;
int l2=A1;
int l3=A2;
int l4=A3;
void setup() 
{
  pinMode(l1,OUTPUT);pinMode(l2,OUTPUT);pinMode(l3,OUTPUT);pinMode(l4,OUTPUT);
  digitalWrite(l1,LOW);digitalWrite(l2,LOW);digitalWrite(l3,LOW);digitalWrite(l4,LOW);
  pinMode(ir1,INPUT);pinMode(ir2,INPUT);
  analogWrite(3,60);Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("WELCOME");
}

void loop()
{
 int ir1val=digitalRead(ir1);delay(10);
 int ir2val=digitalRead(ir2);delay(10);
 if(ir1val==LOW)
 {
 count=count+1;delay(100);  
 }
 if(ir2val==LOW)
 {
 count=count-1;
 if(count<0)
  count=0;
 delay(100);
 }

 if(ir1val==LOW || ir2val==LOW)
 {
 lcd.clear();lcd.setCursor(0,0);lcd.print("C:");lcd.print(count);
 // read without samples.
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) 
  {
   // Serial.print("Read DHT11 failed, err="); Serial.print(SimpleDHTErrCode(err));
   // Serial.print(","); Serial.println(SimpleDHTErrDuration(err)); delay(1000);
    return;
  }
  int temp=((int)temperature);
  int hum=((int)humidity);delay(150);
lcd.print(" T:");lcd.print(temp);lcd.print(" H:");lcd.print(hum);  lcd.print("   ");
String iot="Count:"+String(count)+" Temp:"+String(temp)+" Hum:"+String(hum);
if(count==0)
{
digitalWrite(l1,LOW);digitalWrite(l2,LOW);digitalWrite(l3,LOW);digitalWrite(l4,LOW);
analogWrite(3,0);
lcd.setCursor(0,1);lcd.print("ALL LOADS OFF"); 
iot=iot+" ALL LOADS OFF";delay(10); 
}
if(count==1)
{
digitalWrite(l1,HIGH);digitalWrite(l2,LOW);digitalWrite(l3,LOW);digitalWrite(l4,LOW);  
analogWrite(3,100);
lcd.setCursor(0,1);lcd.print("L1 F:30%");
iot=iot+" L1 F:30% ON";delay(10);
}
if(count==2)
{
digitalWrite(l1,HIGH);digitalWrite(l2,HIGH);digitalWrite(l3,LOW);digitalWrite(l4,LOW); 
analogWrite(3,150); 
lcd.setCursor(0,1);lcd.print("L1 L2 F:60%");
iot=iot+" L1 L2 F:60% ON";delay(10);
}
if(count==3)
{
digitalWrite(l1,HIGH);digitalWrite(l2,HIGH);digitalWrite(l3,HIGH);digitalWrite(l4,LOW); 
analogWrite(3,200);
lcd.setCursor(0,1);lcd.print("L1 L2 L3 F:80%"); 
iot=iot+" L1 L2 L3 F:80% ON";delay(10);
}
if(count>=4)
{
digitalWrite(l1,HIGH);digitalWrite(l2,HIGH);digitalWrite(l3,HIGH);digitalWrite(l4,HIGH);
analogWrite(3,250);
lcd.setCursor(0,1);lcd.print("L1 L2 L3 L4 F:99%"); 
iot=iot+" L1 L2 L3 L4 F:99% ON";delay(10); 
}
if(count>=5)
{
iot="Count:"+String(count)+" Temp:"+String(temp)+" Hum:"+String(hum)+" L1 L2 L3 L4 F:99% ON";delay(10);  
}
Serial.print(iot);delay(1000);

 }
}
