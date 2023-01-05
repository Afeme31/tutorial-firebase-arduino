
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <addons\RTDBHelper.h>
#include "credential.h"

#define WIFI_SSID SSID
#define WIFI_PASSWORD PASS


#define DATABASE_URL "url"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        digitalWrite(LED_BUILTIN, HIGH);
        delay(300);
        digitalWrite(LED_BUILTIN, LOW);
        delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();

    Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

    config.database_url = DATABASE_URL;

    config.signer.test_mode = true;

    Firebase.reconnectWiFi(true);

    /* Initialize the library with the Firebase authen and config */
    Firebase.begin(&config, &auth);

}

void loop() {
  int state;
  // put your main code here, to run repeatedly:
  if( Serial.available()> 1){
    String i = Serial.readString();
    int s = i.toInt();
    Firebase.set(fbdo,"/test/state", s);
  }

  if (Firebase.getInt(fbdo, "/test/state")) {
       state = fbdo.to<int>();
       Serial.print("state : ");
       Serial.println(state);
       if (state == 1 ){
         digitalWrite(LED_BUILTIN,LOW);
       }
       else {
         digitalWrite(LED_BUILTIN,HIGH);         
       }
       
    }
  delay(1000);
}
