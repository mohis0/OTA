#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>

String SSID = "mohsen" , PASS = "m1111111";

void wifiConnect()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID.c_str(), PASS.c_str()); //start connecting to wifi
  Serial.println();
  Serial.print("connecting to wifi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("connected successfuly");
  return;
}

void OTASetup()
{
  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);
  // Hostname defaults to esp8266-[ChipID]
  // ArduinoOTA.setHostname("myesp8266");
  // No authentication by default
  // ArduinoOTA.setPassword("admin");
  ArduinoOTA.onStart([]() {
      // Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
      // Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
      // Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR)
          Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR)
          Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR)
          Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR)
          Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR)
          Serial.println("End Failed");
  });
  ArduinoOTA.begin();
}
void setup() {
  // put your setup code here, to run once:
  wifiConnect();
  OTASetup();
}

void loop() {
  // put your main code here, to run repeatedly:
  ArduinoOTA.handle();
}