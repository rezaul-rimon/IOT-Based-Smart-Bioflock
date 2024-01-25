#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 4
// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

int pump_p=11, pump_n=10, com_p=12, com_n=13;
float ph_var = 0, tds_var = 0, oxy_var = 0, temp_var = 0;
float ph=0, tds=0, oxy=0, temp=0;

void setup() {
  lcd.init();
  lcd.clear();
  lcd.backlight();

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);

  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);

  digitalWrite(pump_p, 0);
  digitalWrite(pump_n, 0);
  digitalWrite(com_p, 0);
  digitalWrite(com_n, 0);

  lcd.setCursor(0,0);
  lcd.print("LCD Test");
  delay(2000);

  sensors.begin();
  Serial.begin(9600);
}

void loop() {
//  lcd.setCursor(0,0);
//  lcd.print(analogRead(A0));
//  lcd.print(" ");
//  lcd.print(analogRead(A1));
//  lcd.print(" ");
//  lcd.setCursor(0,1);
//  lcd.print(analogRead(A2));
//  lcd.print(" ");
//  lcd.print(analogRead(A3));

  sensors.requestTemperatures();
  Serial.print(sensors.getTempCByIndex(0));
  Serial.println();
  delay(1000); 

//  digitalWrite(pump_p, 1);
//  digitalWrite(pump_n, 0);
//  delay(5000);
//  
//  digitalWrite(com_p, 1);
//  digitalWrite(com_n, 0);
//  delay(5000);

//  digitalWrite(pump_p, 0);
//  digitalWrite(pump_n, 0);
//  delay(5000);
//  
//  digitalWrite(com_p, 0);
//  digitalWrite(com_n, 0);
//  delay(5000);
  
  
  //delay(500);

}
