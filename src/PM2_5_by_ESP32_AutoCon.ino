#include <WebServer.h> 
#include <AutoConnect.h> 
#include <Sent_MQTT.h>

//--------------Temp Internal----------------
 #ifdef __cplusplus 
  extern "C" {
 #endif

  uint8_t temprature_sens_read();

#ifdef __cplusplus
}
#endif

uint8_t temprature_sens_read();

//----------------------------------------------------

WebServer Server;          
AutoConnect Portal(Server);

void rootPage() 
{
  char content[] = "ESP32_AutoCon";
  Server.send(200, "text/plain", content);
}

void temp_int()
{
   Serial.print("Temperature_CPU: ");
  
  // Convert raw temperature in F to Celsius degrees
  Serial.print((temprature_sens_read() - 32) / 1.8);
  Serial.println(" C");
}

void callback(char* topic, byte* payload, unsigned int length) 
{
  payload[length] = '\0';
  String topic_str = topic, payload_str = (char*)payload;
  Serial.println("[" + topic_str + "]: " + payload_str);
}

void setup() 
{
  delay(1000);  
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, 17, 16);  //  Tx | Rx
  Serial.println();

  Server.on("/", rootPage);
    if (Portal.begin()) 
    {
      Serial.println("WiFi connected: " + WiFi.localIP().toString());
    }
  
    Portal.handleClient();
    
    mqtt.setServer(MQTT_SERVER, MQTT_PORT);
    mqtt.setCallback(callback); 

  Serial.println(F("DHT22 Connect!"));
  dht.begin();  
}

void loop() 
{   
    Sent_mqtt_eps32();

}

///////////////////////////End//////////////////////////////////
