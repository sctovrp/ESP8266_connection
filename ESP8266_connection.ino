//FirebaseESP8266.h must be included before ESP8266WiFi.h
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "XXXXX"
#define FIREBASE_AUTH "XXXXX"
#define WIFI_SSID "SSID"
#define WIFI_PASSWORD "*******"

//Define FirebaseESP8266 data object
FirebaseData firebaseData;

FirebaseJson json;

String path = "/Blynk_Test/Int";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  if (!Firebase.beginStream(firebaseData, path))
  {
    Serial.println("------------------------------------");
    Serial.println("Can't begin stream connection...");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }

  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");

  Serial.println("------------------------------------");
  Serial.println("Set boolean test...");
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = 1;
  if (Firebase.getInt(firebaseData, path)) {
    Serial.println("firebase data has a int");
    value = firebaseData.intData();
    if (value == 0) {
      Serial.println("--------------------------------");
      Serial.println("int is zero");
      Serial.println("***");
      Serial.println(value);
      digitalWrite(LED_BUILTIN, HIGH);
      
    } else if (value == 1) {
      Serial.println("--------------------------------");
      Serial.println("int is one");
      Serial.println("***");
      Serial.println(value);
      digitalWrite(LED_BUILTIN, LOW);
    }

  }

}
