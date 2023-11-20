#define BLYNK_TEMPLATE_ID "TMPLwbek50AG"
#define BLYNK_DEVICE_NAME "DHT11 SENSOR"
#define BLYNK_AUTH_TOKEN "0Bx5myp6PE4FFRLh5MqBKRK46uyWpNsE"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "YOUR HOTSPOT USERNAME";
char pass[] = "YOUR HOTSPOT PASSWORD";

#include<DHT.h>
#define Dpin 23
#define Dtype DHT11


#define moistana 35
#define motor 17

#define ldrana 34
#define buz 18

DHT dht(Dpin,Dtype);

BlynkTimer timer;

float t, h;
int mdata = 0;
int ldrdata=0;

void sendSensor()
{
  h = dht.readHumidity();
  t = dht.readTemperature(); 
  if(isnan(t) || isnan(h)){
    Serial.println("Check the connection of DHT11");
    return;
  }
Serial.print("Humi = ");
Serial.print(h);
Serial.print("% ");

Serial.print("Temperature is = ");
Serial.print(t);
Serial.println("°"); 
  Blynk.virtualWrite(V0, h);
  Blynk.virtualWrite(V1, t);

  mdata=analogRead(moistana);
 Serial.println(mdata);
  Blynk.virtualWrite(V2,mdata);
}

BLYNK_WRITE(V3) // function for switching of motor
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  if(pinValue == 0){
    digitalWrite(motor,LOW);
  }
  else if(pinValue == 1){
    digitalWrite(motor,HIGH);
  }
}

void setup()
{
  Serial.begin(9600);
  dht.begin();
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, sendSensor); 
  pinMode(motor,OUTPUT);
  pinMode(buz,OUTPUT);
  digitalWrite(motor,HIGH);
}

void loop() 
{
  Blynk.run();
  timer.run(); // Initiates SimpleTimer
  
  ldrdata = analogRead(ldrana);
  Serial.println(ldrdata);
  if(ldrdata < 900){
     digitalWrite(buz,HIGH);
  }
  else if(ldrdata > 1500){
    digitalWrite(buz,LOW);
    delay(3000);
  }
}
