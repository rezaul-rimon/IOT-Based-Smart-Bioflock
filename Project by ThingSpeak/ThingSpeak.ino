#include <WiFi.h>
#include <ThingSpeak.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);

#include <OneWire.h>
#include <DallasTemperature.h>
OneWire oneWire(4);
DallasTemperature sensors(&oneWire);
#include <ESP32Servo.h>
Servo myservo;
int servoPin = 25;

const char *ssid = "Habib";
const char *password = "LA1020ib";

const long channelID = 2378027;
const char *apiKey = "WL86Y91JT3OPOLPI";

WiFiClient client;

int pump_p = 16, pump_n = 17, com_p = 5, com_n = 18;
int ph_pin = 32, tds_pin = 33, oxy_pin = 34, neutro_pin = 35;
int ph_var = 0, tds_var = 0, oxy_var = 0, neutro_var = 0;
float ph = 0, oxy = 0, temp = 0;
int tds = 0, neutro = 0;
float prevPh = -1,  prevOxy = -1, prevTemp = -1;
int prevTds = -1, prevNeutro = -1;

int wifi_try_limit = 0;
unsigned long sendDataPrevMillis = 0;

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

  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);
  myservo.attach(servoPin, 1000, 2000);
  myservo.write(0);

  sensors.begin();

  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("Welcome To");
  lcd.setCursor(0,1);
  lcd.print("Smart Bio-Flock");
  delay(5000);
  lcd.clear();

  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    wifi_try_limit+=1;
    if(wifi_try_limit > 45){
      break;
    }
    lcd.setCursor(0, 0);
    lcd.print("Connecting WiFi");
    lcd.setCursor(0, 1);
    lcd.print("Please wait...");
    Serial.println("Connecting to WiFi...");
  }
  
  lcd.clear();

  //Initialize ThingSpeak
  // if (WiFi.status() != WL_CONNECTED) {
  //   lcd.setCursor(3,0);
  //   lcd.print("Oh! Sorry!");
  //   lcd.setCursor(0,1);
  //   lcd.print("WiFi Not Conctd");

  //   Serial.println("Connect Failed WiFi");
  //   delay(4000);
  // }
  // else{
  //   lcd.setCursor(0,0);
  //   lcd.print("Congratulations!");
  //   lcd.setCursor(1,1);
  //   lcd.print("WiFi Connected");

  //   Serial.println("Connected to WiFi");
  //   delay(2000);
  // }

  lcd.clear();
  ThingSpeak.begin(client);
  
}


void loop() {
  ph_var = analogRead(ph_pin);
  tds_var = analogRead(tds_pin);
  oxy_var = analogRead(oxy_pin);
  neutro_var = analogRead(neutro_pin);

  sensors.requestTemperatures();
  temp = sensors.getTempCByIndex(0);
  ph = map(ph_var, 0, 4095, 0, 14);
  tds = map(tds_var, 0, 4095, 0, 500);
  oxy = map(oxy_var, 0, 4095, 0, 18);
  neutro = map(neutro_var, 0, 4095, 0, 100);

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
    lcd.print(tds);
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

  // Action Logic
  if(tds > 250){
    digitalWrite(pump_p, HIGH);
    digitalWrite(pump_n, LOW);
  }
  else{
    digitalWrite(pump_p, LOW);
    digitalWrite(pump_n, LOW);
  }

  if(oxy < 9.0){
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

  // Print sensor values to Serial Monitor
  Serial.print("PH Value: ");
  Serial.println(ph);
  Serial.print("TDS Value: ");
  Serial.println(tds);
  Serial.print("OXY Value: ");
  Serial.println(oxy);
  Serial.print("Neutro Value: ");
  Serial.println(neutro);

  // Update ThingSpeak every 15 seconds
  if (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0) {
    sendDataPrevMillis = millis();
      ThingSpeak.setField(1, temp);
      ThingSpeak.setField(2, ph);
      ThingSpeak.setField(3, tds);
      ThingSpeak.setField(4, oxy);
      ThingSpeak.setField(5, neutro);
      ThingSpeak.writeFields(channelID, apiKey);
      Serial.println("Updated ThingSpeak with analog values");
  }

  delay(250);
}
