#include <SPI.h>
#include <ESP8266WiFi.h>
#include <ThingerWifi.h>

#define USERNAME "your_user_name"
#define DEVICE_ID "your_device_id"
#define DEVICE_CREDENTIAL "your_device_credential"

#define SSID "your_wifi_ssid"
#define SSID_PASSWORD "your_wifi_ssid_password"

ThingerWifi thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);

  thing.add_wifi(SSID, SSID_PASSWORD);

  // resource input example (i.e. turning on/off a light, a relay, configuring a parameter, etc)
  thing["led"] << [](pson& in){ digitalWrite(BUILTIN_LED, in ? HIGH : LOW); };

  // resource output example (i.e. reading a sensor value)
  thing["millis"] >> [](pson& out){ out = millis(); };

  // resource input/output example (i.e. passing input values and do some calculations)
  thing["in_out"] = [](pson& in, pson& out){
      out["sum"] = (long)in["value1"] + (long)in["value2"];
      out["mult"] = (long)in["value1"] * (long)in["value2"];
  };
}

void loop() {
  thing.handle();
}