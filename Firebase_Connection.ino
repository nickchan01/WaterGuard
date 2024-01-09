//#include <ESP8266WiFi.h>
#include<WiFi.h>                
#include<Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"    
#include "addons/RTDBHelper.h"    
//#include <DHT.h>              
 
#define FIREBASE_API_KEY "AIzaSyBKqH7oV8JSB_bAqw0Bm61k__2tXfIRZ1Y"      
#define FIREBASE_URL "https://uno-flood-default-rtdb.asia-southeast1.firebasedatabase.app/"            
#define WIFI_SSID ""                                  
#define WIFI_PASSWORD ""            

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
bool signupOK = false;
int test = 0;

void setup() 
{
  Serial.begin(115200);                                             //reads dht sensor data               
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                  
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to IP: ");
  Serial.println(WiFi.localIP());                               //prints local IP address
  Serial.println();

  config.api_key = FIREBASE_API_KEY;
  config.database_url = FIREBASE_URL;
  if(Firebase.signUp(&config, &auth, "", "")){
    Serial.println("Firebase Sign In - Successful");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n",config.signer.signupError.message.c_str());
  }

  config.token_status_callback = tokenStatusCallback;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

 
}
 
void loop() 
{
  if(Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 10000 || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();
    test = test + 1;

    if(Firebase.RTDB.setInt(&fbdo, "WaterLvl/us_data", test)){
      Serial.println();
      Serial.print(test);
      Serial.print(" - successfully saved to: " + fbdo.dataPath());
      Serial.println(" (" + fbdo.dataType() + ") ");
    }
    else{
      Serial.println("FAILED: " + fbdo.errorReason());
    }
  }
}

/* //Video elements
  void firestoreDataUpdate(//param)
*/