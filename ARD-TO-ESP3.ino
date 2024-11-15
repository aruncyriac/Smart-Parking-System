#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define IR1 4
#define IR2 5
#define IR3 6
#define IR4 7
#define IR5 8
#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key;

unsigned long startTime1 = 0;
unsigned long stopTime1 = 0;
bool timer1Running = false;

unsigned long startTime2 = 0;
unsigned long stopTime2 = 0;
bool timer2Running = false;

unsigned long startTime3 = 0;
unsigned long stopTime3 = 0;
bool timer3Running = false;

unsigned long startTime4 = 0;
unsigned long stopTime4 = 0;
bool timer4Running = false;

unsigned long startTime5 = 0;
unsigned long stopTime5 = 0;
bool timer5Running = false;

unsigned long timer1 = 0;
bool t1 = false;
unsigned long timer2 = 0;
bool t2 = false;
unsigned long timer3 = 0;
bool t3 = false;
unsigned long timer4 = 0;
bool t4 = false;
unsigned long timer5 = 0;
bool t5 = false;

// Define target IDs
byte targetID1[] = {0x7C, 0xAB, 0xFA, 0x37};
byte targetID2[] = {0xC3, 0x6F, 0x45, 0xFB};
byte targetID3[] = {0x33, 0x06, 0x45, 0xFB};
byte targetID4[] = {0x33, 0x25, 0xEB, 0x1B};
byte targetID5[] = {0x43, 0xCF, 0x50, 0xFB};
int S1, S2, S3, S4, S5;
int l1=1,l2=1,l3=1,l4=1,l5=1;
int r1=1,r2=1,r3=1,r4=1,r5=1;

Servo servoMotor;

void sendleddata();
void checkid(int i);

LiquidCrystal_I2C lcd(0x27, 16, 2); // Address 0x27, 16 columns, 2 rows

void setup() {
  Serial.begin(9600); // Set baud rate to match sender
  servoMotor.attach(3);
  servoMotor.write(90);
  delay(100);
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
  pinMode(IR5, INPUT);
  lcd.init(); // Initialize LCD
  lcd.backlight(); // Turn on backlight
  lcd.clear(); // Clear LCD
  lcd.print("PARKING ");
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522
}



void loop() 
{
  if (Serial.available() > 0) 
  { // Check if data is available to read
    String receivedData = Serial.readStringUntil('\n'); 

    // Parsing data
    int parsedB1, parsedB2, parsedB3, parsedB4, parsedB5;
    sscanf(receivedData.c_str(), "B1: %d, B2: %d, B3: %d, B4: %d, B5: %d", &parsedB1, &parsedB2, &parsedB3, &parsedB4, &parsedB5);
    
    S1 = parsedB1;
    S2 = parsedB2;
    S3 = parsedB3;
    S4 = parsedB4;
    S5 = parsedB5;
  }
  if(S1!=0)
  {
   if (!t1)
   {
    timer1 = millis();
    t1 = true;
   }
   if (digitalRead(IR1) == LOW && !timer1Running) 
   {
    startTime1 = millis();
    timer1Running = true;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Slot 1 occupied");
    delay(500);
    lcd.clear();
    l1=1;
    t1 = false;
    timer1 = 0;     
   }
   else if(digitalRead(IR1) == HIGH && timer1Running)
   {
    l1=0;
    r1=0;
    sendleddata();
    servoMotor.write(90);
    delay(100);
   }
   if (t1 && !timer1Running && (millis() - timer1 >= 30000))
   {
    r1 = 0;
    l1 = 0;
    t1=false;
    timer1 = 0;
    sendleddata();
   }
  }
  else
  {
    t1 = false;
  }
  
  if(S2!=0)
  {
   if (!t2)
   {
    timer2 = millis();
    t2 = true;
   }
   if (digitalRead(IR2) == LOW && !timer2Running) 
   {
    startTime2 = millis();
    timer2Running = true;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Slot 2 occupied");
    delay(500);
    lcd.clear();
    l2=1;
    t2 = false;
    timer2 = 0;     
   }
   else if(digitalRead(IR2) == HIGH && timer2Running)
   {
    l2=0;
    r2=0;
    sendleddata();
    servoMotor.write(90);
    delay(100);
   }
   if (t2 && !timer2Running && (millis() - timer2 >= 30000))
   {
    r2 = 0;
    l2 = 0;
    t2=false;
    timer2 = 0;
    sendleddata();
   }
  }
  else
  {
    t2 = false;
  }
  
  if(S3!=0)
  {
   if (!t3)
   {
    timer3 = millis();
    t3 = true;
   }
   if (digitalRead(IR3) == LOW && !timer3Running) 
   {
    startTime3 = millis();
    timer3Running = true;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Slot 3 occupied");
    delay(500);
    lcd.clear();
    l3=1;
    t3 = false;
    timer3 = 0;     
   }
   else if(digitalRead(IR3) == HIGH && timer3Running)
   {
    l3=0;
    r3=0;
    sendleddata();
    servoMotor.write(90);
    delay(100);
   }
   if (t3 && !timer3Running && (millis() - timer3 >= 30000))
   {
    r3 = 0;
    l3 = 0;
    t3=false;
    timer3 = 0;
    sendleddata();
   }
  }
  else
  {
    t3 = false;
  }
  
  if(S4!=0)
  {
   if (!t4)
   {
    timer4 = millis();
    t4 = true;
   }
   if (digitalRead(IR4) == LOW && !timer4Running) 
   {
    startTime4 = millis();
    timer4Running = true;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Slot 4 occupied");
    delay(500);
    lcd.clear();
    l4=1;
    t4 = false;
    timer4 = 0;     
   }
   else if(digitalRead(IR4) == HIGH && timer4Running)
   {
    l4=0;
    r4=0;
    sendleddata();
    servoMotor.write(90);
    delay(100);
   }
   if (t4 && !timer4Running && (millis() - timer4 >= 30000))
   {
    r4 = 0;
    l4 = 0;
    t4=false;
    timer4 = 0;
    sendleddata();
   }
  }
  else
  {
    t4 = false;
  }
  
  if(S5!=0)
  {
   if (!t5)
   {
    timer5 = millis();
    t5 = true;
   }
   if (digitalRead(IR5) == LOW && !timer5Running) 
   {
    startTime5 = millis();
    timer5Running = true;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Slot 5 occupied");
    delay(500);
    lcd.clear();
    l5=1;
    t5 = false;
    timer5 = 0;     
   }
   else if(digitalRead(IR5) == HIGH && timer5Running)
   {
    l5=0;
    r5=0;
    sendleddata();
    servoMotor.write(90);
    delay(100);
   }
   if (t5 && !timer5Running && (millis() - timer5 >= 30000))
   {
    r5 = 0;
    l5 = 0;
    t5=false;
    timer5 = 0;
    sendleddata();
   }
  }
  else
  {
    t5 = false;
  }
  rfidcheck();
}


void rfidcheck()
{    
  if (!rfid.PICC_IsNewCardPresent())
        return;

    // Verify if the NUID has been read
    if (!rfid.PICC_ReadCardSerial())
        return;

    if (memcmp(rfid.uid.uidByte, targetID1, sizeof(targetID1)) == 0) 
    {
//      lcd.setCursor(0, 0);
//      lcd.print("Target ID 1 matched.");
      checkid(1);
    } 
    else if (memcmp(rfid.uid.uidByte, targetID2, sizeof(targetID2)) == 0)
    {
//      lcd.setCursor(0, 0);
//      lcd.print("Target ID 2 matched.");
      checkid(2);
    } 
    else if (memcmp(rfid.uid.uidByte, targetID3, sizeof(targetID3)) == 0)
    {
//      lcd.setCursor(0, 0);
//      lcd.print("Target ID 3 matched.");
      checkid(3);
    } 
    else if (memcmp(rfid.uid.uidByte, targetID4, sizeof(targetID4)) == 0)
    {
//      lcd.setCursor(0, 0);
//      lcd.print("Target ID 4 matched.");
      checkid(4);
    } 
    else if (memcmp(rfid.uid.uidByte, targetID5, sizeof(targetID5)) == 0)
    {
//      lcd.setCursor(0, 0);
//      lcd.print("Target ID 5 matched.");
      checkid(5);
    } else
    {
//      lcd.setCursor(0, 0);
//      lcd.print("No matching ID found.");
    }

    // Halt PICC
    rfid.PICC_HaltA();
}



void checkid(int i)
{
    if(i==S1)
    {
//      lcd.clear();
//      lcd.setCursor(0, 1);
//      lcd.print("id is in S1"); 
      if (timer1Running) 
      {
        stopTime1 = millis();
        timer1Running = false;
        unsigned long elapsedTime1 = (stopTime1 - startTime1) / 60000;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("slot1 rate: ");
        lcd.setCursor(0, 1);
        lcd.print(elapsedTime1);
        delay(1000);
        lcd.clear();
        startTime1 = 0;
        stopTime1 = 0;
        r1=0;
        l1=1;
        sendleddata();
        r1=1;
        servoMotor.write(170);
        delay(1000);
        servoMotor.write(90);
      }
    }
    else if(i==S2)
    {
//      lcd.clear();
//      lcd.setCursor(0, 1);
//      lcd.print("id is in S2"); 
      if (timer2Running) 
      {
        stopTime2 = millis();
        timer2Running = false;
        unsigned long elapsedTime2 = (stopTime2 - startTime2) / 60000;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("slot2 rate: ");
        lcd.setCursor(0, 1);
        lcd.print(elapsedTime2);
        delay(1000);
        lcd.clear();
        startTime2 = 0;
        stopTime2 = 0;
        r2=0;
        l2=1;
        sendleddata();
        r2=1;
        servoMotor.write(170);
        delay(1000);
        servoMotor.write(90);
      } 
    }
    else if(i==S3)
    {
//      lcd.clear();
//      lcd.setCursor(0, 1);
//      lcd.print("id is in S3"); 
      if (timer3Running) 
      {
        stopTime3 = millis();
        timer3Running = false;
        unsigned long elapsedTime3 = (stopTime3 - startTime3) / 60000;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("slot3 rate: ");
        lcd.setCursor(0, 1);
        lcd.print(elapsedTime3);
        delay(1000);
        lcd.clear();
        startTime3 = 0;
        stopTime3 = 0;
        r3=0;
        l3=1;
        sendleddata();
        r3=1;
        servoMotor.write(170);
        delay(1000);
        servoMotor.write(90);
      }
    }
    else if(i==S4)
    {
//      lcd.clear();
//      lcd.setCursor(0, 1);
//      lcd.print("id is in S4"); 
      if (timer4Running) 
      {
        stopTime4 = millis();
        timer4Running = false;
        unsigned long elapsedTime4 = (stopTime4 - startTime4) / 60000;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("slot4 rate: ");
        lcd.setCursor(0, 1);
        lcd.print(elapsedTime4);
        delay(1000);
        lcd.clear();
        startTime4 = 0;
        stopTime4 = 0;
        r4=0;
        l4=1;
        sendleddata();
        r4=1;
        servoMotor.write(170);
        delay(1000);
        servoMotor.write(90);
      }
    }
    else if(i==S5)
    {
//      lcd.clear();
//      lcd.setCursor(0, 1);
//      lcd.print("id is in S5");  
      if (timer5Running) 
      {
        stopTime5 = millis();
        timer5Running = false;
        unsigned long elapsedTime5 = (stopTime5 - startTime5) / 60000;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("slot5 rate: ");
        lcd.setCursor(0, 1);
        lcd.print(elapsedTime5);
        delay(1000);
        lcd.clear();
        startTime5 = 0;
        stopTime5 = 0;
        r5=0;
        l5=1;
        sendleddata();
        r5=1;
        servoMotor.write(170);
        delay(1000);
        servoMotor.write(90);
      }
    }
  }

  void sendleddata()
  {
    Serial.print("l1: ");
    Serial.print(l1);
    Serial.print(", l2: ");
    Serial.print(l2);
    Serial.print(", l3: ");
    Serial.print(l3);
    Serial.print(", l4: ");
    Serial.print(l4);
    Serial.print(", l5: ");
    Serial.print(l5);
    Serial.print(", r1: ");
    Serial.print(r1);
    Serial.print(", r2: ");
    Serial.print(r2);
    Serial.print(", r3: ");
    Serial.print(r3);
    Serial.print(", r4: ");
    Serial.print(r4);
    Serial.print(", r5: ");
    Serial.println(r5);
  }
