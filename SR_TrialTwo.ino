/*
  PROJET - SHOE-RIFFIC FIRMWARE
  PURPOSE - implementing LiquidCrystal_I2C library instead of LiquidCrystal
  DEV - AARUSHI DHANGER & DAVID WEI
  I2C REF - https://github.com/johnrickman/LiquidCrystal_I2C/tree/master 
  DATE - 07/31/2023
*/

#include <LiquidCrystal_I2C.h>
 

LiquidCrystal_I2C lcd(0x27, 20, 4); // 0X27 = SCREEN ADDRESS 

//NOTE - nano has 14 digi I/O pins
//assigns push buttons to nano pins
const int dryPin = 7;
const int washPin = 8;
//const int quickWashPin = 9;
const int resetPin = 10;

//assigns relay to nano pins (not sure if i can use these pins?)
const int relayOne = 11;
const int relayTwo = 12;

//counter variables
int washCount = 0;
int dryCount = 0;

//real values TBD
int maxWash = 100;
int maxDry = 75;

//time constants
//int quickWashTime = 30000;
int WashTime = 60000;
int dryTime = 30000;

void setup()
{
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);  lcd.print("--------------------"); 
  lcd.setCursor(0,1);  lcd.print("     WELCOME TO");
  lcd.setCursor(0,2);  lcd.print("   SHOE - RIFFIC! ");
  lcd.setCursor(0,3);  lcd.print("--------------------");

  pinMode(relayOne, OUTPUT);
  pinMode(relayTwo, OUTPUT);
  
  //init dryBtn as input
  pinMode(dryPin, INPUT_PULLUP);
  //init washBtn as input
  pinMode(washPin, INPUT_PULLUP);
  //init quickWashBtn as input
  pinMode(quickWashPin, INPUT_PULLUP);
  //init reset as input
  pinMode(reset, INPUT_PULLUP);
  
  //turns relays off then on
  digitalWrite(relayOne, HIGH); 
  digitalWrite(relayTwo, HIGH); 

  resetScreen();
  
  
}

void loop()
{
  while (washCount < maxWash &&dryCount < maxDry){
    //check if each button is pressed (LOW), then allow the relay to power the designated unit
    if(digitalRead(washPin)== LOW)
    {
      wash(WashTime);
      resetScreen();
    }
    /*
    if(digitalRead(quickWashPin)== LOW)
    {
      wash(quickWashTime);
      resetScreen();
    }
    */
    if(digitalRead(dryPin)== LOW)
    {
      dry(dryTime);
      resetScreen();
    }

    //real values TBD
    if(washCount >= maxWash)
    {
      maintence();
      resetScreen();
      break;
    }
    else if(dryCount >= maxDry)
    {
      maintence();
      resetScreen();
      break;
    }
 }

}

void resetScreen()
{
  for(int i = 0; i < 4; i++)
  {
    lcd.setCursor(0,i);  lcd.print("                    ");
  }
  Serial.println("Screen Cleared.");

  lcd.setCursor(0, 1); lcd.print("WashCount = "); lcd.print(washCount);
  Serial.println("WashCount = "); Serial.print(washCount);

  lcd.setCursor(0, 2); lcd.print("DryCount = "); lcd.print(dryCount);
  Serial.println("DryCount = "); Serial.print(dryCount);

}

void wash(int time)
{

  digitalWrite(relayOne,LOW);
  delay(time); // real values TBD
  digitalWrite(relayOne, HIGH);
  washCount = washCount +1;
  //if time is less than a certain threshold, it becomes light wash!
  /*
  if(time <=quickWashTime)
  {
    washCount =washCount +1;
  }
  else
  {
    washCount = washCount+2;
  }
  */
}

void dry(int time)
{
  digitalWrite(relayThree, LOW);
  delay(time); //real values TBD
  digitalWrite(relayThree, HIGH);
  dryCount = dryCount+1;
}

void maintence()
{
  lcd.print("WARNING! maintenance required"); 
  //for reset, we ask the maintence guy to wait 60 seconds before pressing the reset
  delay(60000);
  if(digitalRead(reset, LOW))
  {
    washCount =0;
    dryCount = 0;
  }
}

//unit test functions

  //for deepWashing   time ranges from 60 seconds to 180 seconds
    void TestDW60(){wash(60000);}
    void TestDW90(){wash(90000);}
    void TestDW120(){wash(120000);}
    
  //for lightWashing  time ranges from 30 seconds to 50 seconds
    void TestLW20(){wash(30000);}
    void TestLW30(){wash(40000);}
    void TestLW40(){wash(50000);}
  // for drying time ranges from 30 seconds to 45 seconds
    void TestDR30(){dry(30000);}
    void TestDR40(){dry(40000);}
    void TestDR45(){dry(45000);}