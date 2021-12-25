#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <SoftwareSerial.h>
SoftwareSerial BT(2, 3);//TX, RX respetively For BT
LiquidCrystal_I2C lcd(0x27, 16, 2);

String readdata;
long randomNumber;
String input_password;
const String mastercode = "2468";
char keypressed;
int RelayPin = 13;
int BUZZER = 12;
int LED = A0;
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {11, 10, 9, 8}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {7, 6, 5, 4}; //connect to the column pinouts of the keypad

Keypad myKeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );//Create an object of keypad

void setup()
{
  lcd.init();
  lcd.backlight();
  BT.begin(9600);
  Serial.begin(9600);
  randomSeed(analogRead(0));
  input_password.reserve(32);
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(RelayPin, OUTPUT);
  digitalWrite(RelayPin, LOW);

  lcd.setCursor(2, 0);
  lcd.print("WELCOME!!!!");
}

void loop() {
  while (BT.available())
  {
    delay(10);
    char c = BT.read();
    readdata += c;
  }
  if (readdata.length() > 0)
  {
    Serial.println(readdata);

    if (readdata == "OTP")
    {
      randomNumber = random(10000, 99999);
      Serial.print("The Random Number is = ");
      Serial.println(randomNumber);
      //display the random number on the serial monitor


    }
    BT.print(randomNumber);
    BT.println("");
    readdata = "";
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("OTP SENT, PRESS");
    lcd.setCursor(0, 1);
    lcd.print("* TO ENTER OTP");
  }
  char key = myKeypad.getKey();
  if (key != NO_KEY) {
    Serial.print(key);
    lcd.print(key);
    if (key == 'A') {
      Serial.print("MASTERCODE:");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("# TO CONFIRM");

      lcd.setCursor(0, 1);
      lcd.print("MASTERCODE: ");


      input_password = "";

    }
    
    else if (key == '*') {
      Serial.print("Enter OTP : ");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("# TO CONFIRM");

      lcd.setCursor(0, 1);
      lcd.print("Enter OTP: ");


      input_password = "";

    } else if (key == '#') {
      if (input_password == String(randomNumber)||input_password == String(mastercode)) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("OTP CORRECT");
        lcd.setCursor(0, 1);
        lcd.print("ACCESS GRANTED");
        Serial.println("  OTP IS CORRECT");
        digitalWrite(RelayPin, HIGH);
        digitalWrite(LED, HIGH);
        delay(5000);
        randomNumber = "";
        digitalWrite(RelayPin, LOW);
        digitalWrite(LED, LOW);
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("WELCOME!!!");

      }
      else {
        digitalWrite(BUZZER, HIGH);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("INCORRECT OTP");
        lcd.setCursor(0, 1);
        lcd.print("ACCESS DENIED");
        Serial.println("INCORRECT OTP, TRY AGAIN");
        delay(5000);
        digitalWrite(BUZZER, LOW);
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("WELCOME!!!");

      }
      input_password = ""; // reset the input password
    } else {
      input_password += key; // append new character to input password string
    }
  }

}
