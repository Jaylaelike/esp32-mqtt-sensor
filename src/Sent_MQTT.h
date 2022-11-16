#include <PubSubClient.h>
#include <WiFi.h> 
#include <Set_Location.h>
#include <PM_Read.h> 
#include <Temp_Read.h>


#define MQTT_SERVER   "broker.emqx.io"
#define MQTT_PORT     1883
#define MQTT_USERNAME ""
#define MQTT_PASSWORD ""
#define MQTT_NAME     "ESP32_HUA"

long lastMsg = 0;
char msg[200];
int value = 0;
String payload_ESP;
int rssi_esp32;
String clientID   = "espiot";  //Your client id < 120 characters

WiFiClient espiot;
PubSubClient mqtt(espiot); //---- clientID = "espiot" ----------//

void initWiFi() 
{
  rssi_esp32=WiFi.RSSI();
  Serial.print("RRSI: ");
  Serial.println(rssi_esp32);
}

void MQTT_Recon()
{
if (mqtt.connected() == false) 
  {
    Serial.print("MQTT connection... ");
    if (mqtt.connect(MQTT_NAME, MQTT_USERNAME, MQTT_PASSWORD)) 
    {
      Serial.println("connected");
      mqtt.subscribe("ESP32_HUA");
      mqtt.publish("/PM/HUA","hello world");
   
    } 
    else 
    {
      Serial.println("failed");
      delay(5000);
    }
  }
}

void Sent_mqtt_eps32()
{
  long now = millis();
  if (now - lastMsg > 10000)
  { 
  initWiFi();
  MQTT_Recon();
  //temp_int();
  TM_Read();
  PM_Read (); 
   lastMsg = now;
    value++; 

  payload_ESP = "{\"latitude\":"+String(Lat)+",\"longitude\":"+String(Long)+",\"name\":"+String(Station)+",\"signal\":"+String(rssi_esp32)+",\"temp\":"+String(t)+",\"humid\":"+String(h)+",\"pm2p5\":"+String(pm2_5)+",\"pm10\":"+String(pm10)+"}";      
  payload_ESP.toCharArray(msg, 200);
    Serial.print("Publish message: ");
    Serial.println(msg);
    mqtt.publish("/PM/HUA", msg); //ส่งข้อความ "msg" ใน Topic = "/PM/HUA"
    Serial.println("Success sending");
            
  }
  else 
    {
    mqtt.loop();
    } 
}
