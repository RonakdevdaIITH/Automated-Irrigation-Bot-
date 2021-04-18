bl#include<LiquidCrystal.h>
#include<DHT.h>
#include<Wire.h>
#include <BH1750.h>

float sensorValue = 0;
int isMotorOn = 0;
int changeInMotor =0;
int c1,buttonctr =1;
float temp,hum;
int buttonState=0;
int buttonChange =0;
int ledPin = 13,motorPin = 6,buttonPin =2,DHTPin = 3;
float lux;

LiquidCrystal lcd(7,8,9,10,11,12);
DHT dht(3,DHT11);
BH1750 lightMeter;

void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);
  dht.begin();
  Wire.begin();
  lcd.noBlink();
  lightMeter.begin();
  pinMode(ledPin,OUTPUT); //3W LED
  pinMode(buttonPin,OUTPUT); //Push Button
  pinMode(motorPin,OUTPUT); //Motor
  lcd.print("Welcome To IDP Project");
  delay(400);
  for(int i=0;i<7;i++){
    lcd.scrollDisplayLeft();
    delay(400);
  }
  lcd.clear();
  delay(100);
  lcd.print("Soil Moisture: ");
  lcd.print(sensorValue);
  c1=0;
}

void loop()
{
  lux = lightMeter.readLightLevel();
  buttonState = digitalRead(buttonPin);
  temp = dht.readTemperature();
  hum = dht.readHumidity();
  sensorValue = analogRead(A0);

  Serial.println("lux : ");
  Serial.println(lux);
   Serial.println("temp : ");
  Serial.println(temp);
   Serial.println("hum : ");
  Serial.println(hum);
   Serial.println("moisture : ");
  Serial.println(sensorValue);

  if(buttonState ==HIGH){
    buttonctr++;
  }
  if(buttonctr == 4){
    buttonctr = 1;
  }
  
  if(lux <54)
  {
    digitalWrite(ledPin,HIGH);
  }
  else{
    digitalWrite(ledPin,LOW);
  }


    if(sensorValue <600){
    if(isMotorOn == 1){
      changeInMotor =1;
    }
    isMotorOn = 0;
    digitalWrite(6,HIGH);
    
  }
  else{
    if(isMotorOn == 0){
      changeInMotor =1;
    }
    isMotorOn = 1;
    digitalWrite(6,LOW);
  }
  
  if(c1>=40 || changeInMotor ==1 || buttonChange ==1){
    changeInMotor = 0;
    lcd.clear();
    delay(50);
    if(buttonctr == 1){
      lcd.print("Soil Moisture:");
      lcd.print(sensorValue);
    }
    else if(buttonctr == 2){
      lcd.print("Light Sensor:");
      lcd.print(lux);
    }
    else if(buttonctr == 3){
      lcd.print("Temperature:");
      lcd.print(temp);
    }
    else if(buttonctr == 4){
      lcd.print("Humidity:");
      lcd.print(hum);
    }
    lcd.setCursor(0,1);
    if(isMotorOn == 0){
      lcd.print("Motor is Off");
    }
    else{
      lcd.print("Motor is On");
    }
    delay(400);
  for(int i=0;i<2;i++){
    lcd.scrollDisplayLeft();
    delay(400);
    c1=0;
  }
   
  }

  
  ++c1;
  delay(50);

  delay(2500);
}
