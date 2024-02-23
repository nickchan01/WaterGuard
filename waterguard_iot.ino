//#include <ESP8266WiFi.h>
#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include<WiFi.h>                
#include<Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"    
#include "addons/RTDBHelper.h"    
//#include <DHT.h>              
 
#define FIREBASE_API_KEY ""    
#define FIREBASE_URL ""           
#define WIFI_SSID ""                            
#define WIFI_PASSWORD "" 

#define trigPin 12
#define echoPin 13

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
LiquidCrystal_I2C lcd(0x27, 16, 2);

long duration, inches, distance;
int set_val,percentage;
bool state,pump;
unsigned long sendDataPrevMillis = 0;
bool signupOK = false;
int count = 0;
long prevLevel = 0;

float maxLevel = 70;

float level1= ((maxLevel / 25) * 100);
//float level2= ((maxLevel / 50) * 100);
float level2= 79;
//float level3= ((maxLevel / 75) * 100);
float level3= 75;

//19 bugged value no water level

void setup() 
{
  Serial.begin(115200);
  lcd.init();     
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("WATER : ");
  lcd.setCursor(0, 1); 
  lcd.print("LEVEL :");

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  set_val=EEPROM.read(0);
  if(set_val>150)set_val=150;
                                                         
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
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WATER : ");
    lcd.setCursor(0, 1); 
    lcd.print("LEVEL :");
    sendDataPrevMillis = millis();
    count = count + 1;

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration*.0343)/2;  
    //inches = microsecondsToInches(duration);
    
    //percentage=(set_val-inches)*100/set_val;

    //pinMode(echoPin, INPUT);

    lcd.setCursor(10, 0); 
    lcd.print(distance);
    //Serial.println(distance);

    /*if (distance < 20){ 
      Serial.println("Flood Alert!");
      Serial.println("Sending text Notification...");
      delay(5000);
      Serial.println("Patrol Mode Initiated...");
    }*/

    if(Firebase.RTDB.setFloat(&fbdo, "WaterLvl/us_data", distance)){
      Serial.println();
      Serial.print(count);
      Serial.print(") ");
      Serial.print(distance);
      Serial.print(" - successfully saved to: " + fbdo.dataPath());
      Serial.println(" (" + fbdo.dataType() + ") ");
    }
    else{
      Serial.println("FAILED: " + fbdo.errorReason());
    }

    if(prevLevel != 0 && (prevLevel - distance)> 5){
      Serial.println();
      Serial.println("Dangerous water rise detected!");
      Serial.println("Sending alert");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Dangerous rise");
      lcd.setCursor(0, 1); 
      lcd.print("Sending alert");
      delay(4000);
      exit(0);
    }

    prevLevel = distance;

    if (distance >= level1){
      lcd.setCursor(10, 1); 
      lcd.print("LOW");
    } else if (distance >= level2 && distance < level1){
      lcd.setCursor(10, 1); 
      lcd.print("MEDIUM");
    } else if (distance >= level3 && distance < level2){
      lcd.setCursor(10, 1); 
      lcd.print("HIGH");
    } else if (distance <= maxLevel && distance < level3){
      lcd.setCursor(10, 1); 
      lcd.print("FLOOD");
    }
  }
}

/* //Video elements
  void firestoreDataUpdate(//param)
*/