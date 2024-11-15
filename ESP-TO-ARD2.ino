#include <ArduinoJson.h> 
#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "realme"
#define WIFI_PASSWORD "12345678"

// Insert Firebase project API Key
#define API_KEY "AIzaSyApv9di90PF2DX_z1I8G5_KAF7iNYdMHdk"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://carparking-aa456-default-rtdb.firebaseio.com/"
//Define Firebase Data object
FirebaseData fbdo;

#define led1 19
#define led2 18
#define led3 5
#define led4 4
#define led5 2

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int intValue;
float floatValue;
bool signupOK = false;
int l1,l2,l3,l4,l5;
int s1,s2,s3,s4,s5;
int r1=1,r2=1,r3=1,r4=1,r5=1;

void setup() {
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
//  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) 
  {
    //Serial.print(".");
//    delay(300);
  }
  //Serial.println();
  //Serial.print("Connected with IP: ");
//  Serial.println(WiFi.localIP());
//  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")) {
    //Serial.println("ok");
    signupOK = true;
  }
  else {
    //Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}



void loop() 
{
  if (Serial.available() > 0) 
  { // Check if data is available to read
   String receivedData = Serial.readStringUntil('\n'); 
   //Serial.println(receivedData);
   int parsedB1, parsedB2, parsedB3, parsedB4, parsedB5, parsedB6, parsedB7, parsedB8, parsedB9, parsedB10;
   sscanf(receivedData.c_str(), "l1: %d, l2: %d, l3: %d, l4: %d, l5: %d, r1: %d, r2: %d, r3: %d, r4: %d, r5: %d", &parsedB1, &parsedB2, &parsedB3, &parsedB4, &parsedB5, &parsedB6, &parsedB7, &parsedB8, &parsedB9, &parsedB10); 

        l1=parsedB1;
        l2=parsedB2;
        l3=parsedB3;
        l4=parsedB4;
        l5=parsedB5;
        r1=parsedB6;
        r2=parsedB7;
        r3=parsedB8;
        r4=parsedB9;
        r5=parsedB10;
        
//        Serial.print("l1: ");
//        Serial.print(l1);
//        Serial.print(", l2: ");
//        Serial.print(l2);
//        Serial.print(", l3: ");
//        Serial.print(l3);
//        Serial.print(", l4: ");
//        Serial.print(l4);
//        Serial.print(", l5: ");
//        Serial.println(l5);

//        Serial.print("r1: ");
//        Serial.print(r1);
//        Serial.print(", r2: ");
//        Serial.print(r2);
//        Serial.print(", r3: ");
//        Serial.print(r3);
//        Serial.print(", r4: ");
//        Serial.print(r4);
//        Serial.print(", r5: ");
//        Serial.println(r5);
        
        ledoff();
  }
  // Check if Firebase is ready, signed up, and it's time to retrieve data
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0))
  {
    sendDataPrevMillis = millis();

    // Attempt to retrieve JSON data for the specified path ("/Time" in this case)
    if (Firebase.RTDB.getJSON(&fbdo, "/"))
    {
      // Check if the data was successfully retrieved
      if (fbdo.jsonObjectPtr())
      {
        // Convert JSON object to string
        String jsonData = fbdo.jsonString();

        // Parse JSON data
        StaticJsonDocument<200> doc;
        DeserializationError error = deserializeJson(doc, jsonData);

        // Check for parsing errors
        if (error)
        {
//          Serial.print("Failed to parse JSON: ");
//          Serial.println(error.c_str());
          return;
        }

        // Extract values for B1, B2, B3, B4, and B5
        int b1 = doc["B1"].as<int>();
        int b2 = doc["B2"].as<int>();
        int b3 = doc["B3"].as<int>();
        int b4 = doc["B4"].as<int>();
        int b5 = doc["B5"].as<int>();

        s1=b1;
        s2=b2;
        s3=b3;
        s4=b4;
        s5=b5;
        ledon();

        // Print the retrieved data
        Serial.print("B1: ");
        Serial.print(b1);
        Serial.print(", B2: ");
        Serial.print(b2);
        Serial.print(", B3: ");
        Serial.print(b3);
        Serial.print(", B4: ");
        Serial.print(b4);
        Serial.print(", B5: ");
        Serial.println(b5);
      } else {
//        Serial.println("Failed to get JSON data");
      }
    } else {
//      Serial.println("Failed to retrieve JSON data from Firebase");
    }
  }
}

void ledoff()
{
  if(l1==0)
  {
    digitalWrite(led1,LOW);
  }
  if(l2==0)
  {
    digitalWrite(led2,LOW);
  }
  if(l3==0)
  {
    digitalWrite(led3,LOW);
  }
  if(l4==0)
  {
    digitalWrite(led4,LOW);
  }
  if(l5==0)
  {
    digitalWrite(led5,LOW);
  }
  if(r1==0)
  {
    Firebase.RTDB.setInt(&fbdo, "B1", 0);
    r1=1;
  }
  if(r2==0)
  {
    Firebase.RTDB.setInt(&fbdo, "B2", 0);
    r2=1;
  }
  if(r3==0)
  {
    Firebase.RTDB.setInt(&fbdo, "B3", 0);
    r3=1;
  }
  if(r4==0)
  {
    Firebase.RTDB.setInt(&fbdo, "B4", 0);
    r4=1;
  }
  if(r5==0)
  {
    Firebase.RTDB.setInt(&fbdo, "B5", 0);
    r5=1;
  }   
}

void ledon()
{
  if(s1!=0)
  {
    digitalWrite(led1,HIGH);
    l1=1;
  }
  if(s2!=0)
  {
    digitalWrite(led2,HIGH);
    l2=1;
  }
  if(s3!=0)
  {
    digitalWrite(led3,HIGH);
    l3=1;
  }
  if(s4!=0)
  {
    digitalWrite(led4,HIGH);
    l4=1;
  }
  if(s5!=0)
  {
    digitalWrite(led5,HIGH);
    l5=1;
  }  
}
