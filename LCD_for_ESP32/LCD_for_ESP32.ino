
int pump_p = 16, pump_n = 17, com_p = 5, com_n = 18;
int ph_pin = 26, tds_pin = 27, oxy_pin = 14, neutro_pin = 12;
int ph_var = 0, tds_var = 0, oxy_var = 0, neutro_var = 0;
float ph = 0, oxy = 0, temp = 0;
int tds = 0, neutro = 0;

float prevPh = -1,  prevOxy = -1, prevTemp = -1;
int prevTds = -1, prevNeutro = -1;

#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

#include <ESP32Servo.h>
Servo myservo;
int servoPin = 25;

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);


void setup() {

  pinMode(ph_pin, INPUT);
  pinMode(tds_pin, INPUT);
  pinMode(oxy_pin, INPUT);
  pinMode(neutro_pin, INPUT);

  pinMode(pump_p, OUTPUT);
  pinMode(pump_n, OUTPUT);
  pinMode(com_p, OUTPUT);
  pinMode(com_n, OUTPUT);

  digitalWrite(pump_p, LOW);
  digitalWrite(pump_n, LOW);
  digitalWrite(com_p, LOW);
  digitalWrite(com_n, LOW);
  
  lcd.init();
  lcd.clear();
  lcd.backlight();
  
  sensors.begin(); 

  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);
  myservo.attach(servoPin, 1000, 2000);
  myservo.write(0);
}

void loop() {
  
  ph_var = analogRead(ph_pin);
  tds_var = analogRead(tds_pin);
  oxy_var = analogRead(oxy_pin);
  neutro_var = analogRead(neutro_pin);

  ph = map(ph_var, 0, 4095, 0, 14);
  tds = map(tds_var, 0, 4095, 0, 500);
  oxy = map(oxy_var, 0, 4095, 0, 18);
  neutro = map(neutro_var, 0, 4095, 0, 100);
  sensors.requestTemperatures(); 
  temp = sensors.getTempCByIndex(0);


  // Action Logic
  if(tds > 250){
    digitalWrite(pump_p, HIGH);
    digitalWrite(pump_n, LOW);
  }
  else{
    digitalWrite(pump_p, LOW);
    digitalWrite(pump_n, LOW);
  }

  if(oxy < 9){
    digitalWrite(com_p, HIGH);
    digitalWrite(com_n, LOW);
  }
  else{
    digitalWrite(com_p, LOW);
    digitalWrite(com_n, LOW);
  }

  if(neutro < 40){
    myservo.write(90);
  }
  else{
    myservo.write(0);
  }

  ///Printing Logic
  if (prevPh != ph) {
    lcd.setCursor(0,0);
    lcd.print("     ");
    lcd.setCursor(0,0);
    lcd.print(ph, 1);
    lcd.print(" ");
    prevPh = ph;
  }

  if (prevOxy != oxy) {
    lcd.setCursor(5, 0);
    lcd.print("     ");
    lcd.setCursor(5,0);
    lcd.print(oxy, 1);
    lcd.print(" ");
    prevOxy = oxy;
  }

  if (prevTemp != temp) {
    lcd.setCursor(12, 0);
    lcd.print("     ");
    lcd.setCursor(12,0);
    lcd.print(temp, 1);
    lcd.print(" ");
    prevTemp = temp;
  }

  if (prevTds != tds) {
    lcd.setCursor(0, 1);
    lcd.print("     ");
    lcd.setCursor(0, 1);
    lcd.print(tds_var);
    lcd.print(" ");
    prevTds = tds;
  } 

  if (prevNeutro != neutro) {
    lcd.setCursor(8, 1);
    lcd.print("     ");
    lcd.setCursor(8, 1);
    lcd.print(neutro);
    prevNeutro = neutro;
  } 

  delay(500);
}

