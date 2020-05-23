/****************************************************************
 * THIS PROJECT BELONG TO ENSAR LEVENT.
 * YOU CAN GET OTHER PROJECTS FROM INSTRUCTABLES
 * https://www.instructables.com/member/ensarlevent/instructables/

Tested with SparkFun Arduino Nano
****************************************************************/
#include <SPI.h>
#include <MFRC522.h>
#include <EEPROM.h>

const int buttonPin = 7;
int buttonState = 0;


#define RST_PIN 9
#define SS_PIN 10

MFRC522 mfrc522(SS_PIN, RST_PIN);

String lastRfid = "";
String card1 = "";
String card2 = "";

MFRC522::MIFARE_Key key;

void setup()
{  
  pinMode(buttonPin, OUTPUT); 
  

  
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("RFID Card Reader");
  Serial.println("--------------------------");
  Serial.println();
  readEEPROM();
  digitalWrite(buttonPin,1);
}

void loop()
{
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  String rfid = "";
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    rfid += mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ";
    rfid += String(mfrc522.uid.uidByte[i], HEX);
  }
  rfid.trim();
  rfid.toUpperCase();
  
  if (rfid == lastRfid)
    return;
  lastRfid = rfid;

  Serial.print("Card 1: ");
  Serial.println(card1);
  Serial.print("Card 2: ");
  Serial.println(card2);
  Serial.print("Now: ");
  Serial.println(rfid);
  Serial.println();
    if (rfid == card1)
  {
    Serial.println("Turned On.");
    digitalWrite(buttonPin,0);
    delay (2000);
    
  }
  if (rfid == card2)
  {
    Serial.println("Turned Off");
    digitalWrite(buttonPin,1);
    delay (2000);
    

  }
  Serial.println();
  delay(200);
}

void readEEPROM()
{
  for (int i = 0 ; i < 4 ; i++)
  {
    card1 += EEPROM.read(i) < 0x10 ? " 0" : " ";
    card1 += String(EEPROM.read(i), HEX);
  }
  for (int i = 4 ; i < 8 ; i++)
  {
    card2 += EEPROM.read(i) < 0x10 ? " 0" : " ";
    card2 += String(EEPROM.read(i), HEX);
  }
  card1.trim();
  card1.toUpperCase();
  card2.trim();
  card2.toUpperCase();
}

