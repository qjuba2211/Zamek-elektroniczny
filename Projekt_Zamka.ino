#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <MFRC522.h>
#include <Servo.h>
#include <SPI.h>
#include <OneWire.h>
#include <DS18B20.h>

#define ONEWIRE_PIN 5
byte adres[8] = {0x28, 0x82, 0x30, 0x3B, 0xA, 0x0, 0x0, 0xA8};

LiquidCrystal_I2C lcd(0x27, 16, 2);
MFRC522 mfrc522(10, 9);
Servo sg90;
OneWire onewire(ONEWIRE_PIN);
DS18B20 sensors(&onewire);

constexpr uint8_t diodaZielona = 7;
constexpr uint8_t diodaCzerwona = 6;
constexpr uint8_t servoPin = 8;

char kod_domyslny[4] = {'1', '2', '3', '3'};
String tagUID = "74 91 51 A3";
char kod_wprowadzony[4];
boolean RFIDMode;
boolean TempMode = true;
char key_pressed = 0;
uint8_t i = 0;

const byte wiersze = 4;
const byte kolumny = 4;

char mapa_klawiszy[wiersze][kolumny] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
  };

byte piny_w[wiersze] = {A0, A1, A2, A3};
byte piny_k[kolumny] = {4, 3, 2};

Keypad keypad_key = Keypad( makeKeymap(mapa_klawiszy), piny_w, piny_k, wiersze, kolumny);

void setup() {
  pinMode(diodaCzerwona, OUTPUT);
  pinMode(diodaZielona, OUTPUT);
  
  sg90.attach(servoPin);
  sg90.write(0);
  
  lcd.begin();
  lcd.backlight();
  SPI.begin();
  mfrc522.PCD_Init();
  lcd.clear();
  
  while(!Serial);
  Serial.begin(9600);
  
  sensors.begin();
  sensors.request(adres);
}

float temperature = 0;

void loop() {
  if (TempMode == true)
  {   
   if (sensors.available())
    {
      lcd.setCursor(0, 0);
      lcd.print("Zmierz");
      lcd.setCursor(0, 1);
      lcd.print("temperature");
      delay(4000);
      lcd.clear();
      
      for (float t=0 ; t<15 ; t++)
      {
        lcd.setCursor(0, 0);
        lcd.print("Mierzenie..");
        temperature = sensors.readTemperature(adres);
        Serial.print(temperature);
        Serial.println(F(" 'C"));
        sensors.request(adres); 
        delay(1000);
      }

      if (temperature >= 25 && temperature <= 31)
       {
         lcd.clear();
         lcd.setCursor(0, 0);
         lcd.print("Blokada 1/3");
         lcd.setCursor(0, 1);
         lcd.print("Temperatura OK");
         digitalWrite(diodaZielona, HIGH);
         delay(5000);
         digitalWrite(diodaZielona, LOW);
         lcd.clear();
         temperature = 0;
         RFIDMode = true;
         TempMode = false;
       }
      else if (temperature < 25 || temperature > 31)
       {
         lcd.clear();
         lcd.setCursor(0, 0);
         lcd.print("Blokada 1/3");
         lcd.setCursor(0, 1);
         lcd.print("Brak dostepu");
         digitalWrite(diodaCzerwona, HIGH);
         delay(3000);
         digitalWrite(diodaCzerwona, LOW);
         lcd.clear();
         TempMode = true;  
       }
    }    
  }
    
  if (RFIDMode == true)
  { 
    lcd.setCursor(0, 0);
    lcd.print("Zeskanuj brelok");
    
    if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
    }
    
    if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
    }
    
    String tag = "";
    for (byte j = 0; j < mfrc522.uid.size; j++)
    {
      tag.concat(String(mfrc522.uid.uidByte[j] < 0x10 ? " 0" : " "));
      tag.concat(String(mfrc522.uid.uidByte[j], HEX));
    }
    tag.toUpperCase();
    
    if (tag.substring(1) == tagUID)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Blokada 2/3");
      lcd.setCursor(0, 1);
      lcd.print("Brelok zgodny");
      digitalWrite(diodaZielona, HIGH);
      delay(3000);
      digitalWrite(diodaZielona, LOW);
      
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Podaj kod:");
      lcd.setCursor(6, 1);
      RFIDMode = false;
    }
    
    else
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Blokada 2/3");
      lcd.setCursor(0, 1);
      lcd.print("Brelok niezgodny");
      //digitalWrite(buzzerPin, HIGH);
      digitalWrite(diodaCzerwona, HIGH);
      delay(3000);
      digitalWrite(diodaCzerwona, LOW);
      lcd.clear();
      TempMode = true;
      RFIDMode = false;
    }
  }
  
  
  if (RFIDMode == false) {
    key_pressed = keypad_key.getKey();
    if (key_pressed){
      kod_wprowadzony[i++] = key_pressed;
      lcd.print("*");
    }
    if (i == 4){
      delay(200);
      if (!(strncmp(kod_wprowadzony, kod_domyslny, 4)))
        {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Blokada 3/3");
          lcd.setCursor(0, 1);
          lcd.print("Kod zgodny");
          delay(3000);
          sg90.write(90);
          digitalWrite(diodaZielona, HIGH);
          lcd.clear();
          lcd.setCursor(1, 0);
          lcd.print("Drzwi otwarte");
          lcd.setCursor(7, 1);
          lcd.print("5");
          delay(1000);
          lcd.setCursor(7, 1);
          lcd.print("4");
          delay(1000);
          lcd.setCursor(7, 1);
          lcd.print("3");
          delay(1000);
          lcd.setCursor(7, 1);
          lcd.print("2");
          delay(1000);
          lcd.setCursor(7, 1);
          lcd.print("1");
          delay(1000);
          lcd.setCursor(7, 1);
          lcd.print("0");
          delay(1000);

          digitalWrite(diodaZielona, LOW);
          sg90.write(0);
          lcd.clear();
          i = 0;
          TempMode = true;
        }
        
      else
        {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Blokada 3/3");
          lcd.setCursor(0, 1);
          lcd.print("Kod niezgodny");
          digitalWrite(diodaCzerwona, HIGH);
          delay(3000);
          digitalWrite(diodaCzerwona, LOW);
          lcd.clear();
          i = 0;
          TempMode = true;
        }
      }
   }
}
