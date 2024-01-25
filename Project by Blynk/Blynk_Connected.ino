//Tech Trends Shameer

#define BLYNK_TEMPLATE_ID "TMPL6BNEabfmn"
#define BLYNK_TEMPLATE_NAME "Fish Firm"
#define BLYNK_AUTH_TOKEN "t3I_trsCYvVyN6BUHJA7Hv1k3R1cjOsI"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Habib";
char pass[] = "LA1020ib";

BlynkTimer timer;

void sendSensor()
{
  // Placeholder values for testing, replace these with actual sensor readings.
  float ph = 8.0, oxy = 12.6, temp = 24.5;
  int tds = 400, neutro = 40;

  Blynk.virtualWrite(V0, temp);
  Blynk.virtualWrite(V1, ph);
  Blynk.virtualWrite(V2, oxy);
  Blynk.virtualWrite(V3, tds);
  Blynk.virtualWrite(V4, neutro);
}

void setup()
{
  Serial.begin(115200);
  delay(100);

  // Blynk begin statement
  Blynk.begin(auth, ssid, pass);

  // Place your setup code here.
  int pump_p = 16, pump_n = 17, com_p = 5, com_n = 18;
  int ph_pin = 26, tds_pin = 27, oxy_pin = 14, neutro_pin = 12;
  int ph_var = 0, tds_var = 0, oxy_var = 0, neutro_var = 0;

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

  // End of setup code.
}

void loop()
{
  // Blynk connection status debugging.
  if (Blynk.connected()) {
    Serial.println("Blynk is connected");
  } else {
    Serial.println("Blynk is NOT connected");
  }

  Blynk.run();
  timer.run();
}
