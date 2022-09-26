#define BLYNK_TEMPLATE_ID "*********"
#define BLYNK_DEVICE_NAME "*********"
#define BLYNK_AUTH_TOKEN "*********************"
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "Your SSID";  // type your wifi name
char pass[] =  "Your Password";  // type your wifi password

#define DHTPIN 2

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
int mq2 = A0;
int data =0;
BlynkTimer timer;


void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
 
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V1,t);
  Blynk.virtualWrite(V2, h);
 
}
void getSendData()
{

int data = analogRead(mq2);
  Blynk.virtualWrite(V3, data);
 
}
 
void setup()
{
 
 Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  timer.setInterval(1000L, sendSensor);
  Serial.begin(115200);
  timer.setInterval(1000L, getSendData);
}

void loop()
{
  Blynk.run();
  timer.run();
}
