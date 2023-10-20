/*
 PIN CONNECTIONS

  * analog connections
  * SDA - A4 
  * SCL - A5

  * digi I/O connections
  * Relay1  - 3 = D2
  * Relay2  - 4 = D3
  * RESET   - 5 = D4
  * DRY PIN - 6 = D5 
  * WASHPIN - 7 = D6

Notes:
 * ADD ERROR CHECKING PINS (D7, D8, D9) (RESET, DRY, WASH)
 * pump delay: 2 second(s)
 * fan delay : 1 second(s) *** CHECK THIS ***
 * 
 * purpose of reset button - 
 *  1. customer presses reset to stop all functionality
 *  2. Maintenance feature - press 3x to activate the maintenance stage - ignore for now
 */
 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // 0X27 = SCREEN ADDRESS 

//NOTE - nano has 14 digi I/O pins
//assigns push buttons to nano pins
const int resetPin = 5; //change to reset pin 

const int dryPin = 6;
const int washPin = 7;
//const int quickWashPin = 10;

//assigns relay to nano pins 
const int relayOne = 3;
const int relayTwo = 4;

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


void setup() {

lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);  lcd.print("--------------------"); 
  lcd.setCursor(0,1);  lcd.print("     WELCOME TO");
  lcd.setCursor(0,2);  lcd.print("   SHOE - RIFFIC! ");
  lcd.setCursor(0,3);  lcd.print("--------------------");

  //initializing 
  pinMode(relayOne, OUTPUT);
  pinMode(relayTwo, OUTPUT);
  
  pinMode(dryPin, INPUT_PULLUP);    //init dryBtn as input
  pinMode(washPin, INPUT_PULLUP);   //init washBtn as input
  pinMode(resetPin, INPUT_PULLUP);  //init reset as input
  
  //turns relays off then on
  digitalWrite(relayOne, HIGH); 
  digitalWrite(relayTwo, HIGH);
  resetScreen();
  delay(5000); //NEW
}

void loop() {
  
  while (washCount < maxWash &&dryCount < maxDry){
    lcd.clear();
    lcd.print("waiting for user input");
    delay(5000);

    //check if each button is pressed (LOW), then allow the relay to power the designated unit
    //added delay function to make user to hold a button for 3 seconds before performing any functions

    if(digitalRead(washPin)== LOW){
      lcd.clear();//clear screen to print new words
      lcd.print("You selected wash, please hold it for 2 second"); //9 Words, 46 characters
      delay(2000);
      lcd.clear();
        //user has confirmed he/she wants to wash
        if(digitalRead(washPin) ==LOW){
          lcd.print("Initializing Washing....");
          wash(WashTime);
        }
      lcd.clear();
   
    }

    if(digitalRead(dryPin)== LOW){
      lcd.clear();//clear screen to print new words
      lcd.print("You selected dry, please hold for 2 seconds"); //9 Words, 45 characters
      delay(2000);
      lcd.clear();
      if(digitalRead(dryPin)== LOW){
        lcd.print("Initializing Drying....");
        dry(dryTime);
      }
      lcd.clear();
    }
    if(digitalRead(resetPin) == LOW){
      resetFunct();
    }
    //real values TBD
  if(washCount >= maxWash){
    maintenance();
    break;
  }
  else if(dryCount >= maxDry){
    maintenance();
    break;
  }
 }
}


//sub functions created for unit test
  void wash(int time){
    
    digitalWrite(relayOne,LOW);
    delay(time); // real values TBD
    digitalWrite(relayOne, HIGH);
    
    //if time is less than a certain threshold, it becomes light wash!
    washCount =washCount +1;
  }

  void dry(int time){
    
    digitalWrite(relayTwo, LOW);
    delay(time); //real values TBD
    digitalWrite(relayTwo, HIGH);
    
    dryCount = dryCount+1;
  }

  void maintenance(){
    lcd.clear();
    lcd.print("WARNING! maintenance required"); 
    
    //for reset, we ask the maintenance guy to wait 60 seconds before pressing the reset
    delay(60000);
    if(digitalRead(resetPin)== LOW){
      digitalWrite(relayOne, HIGH); 
      digitalWrite(relayTwo, HIGH); 
      washCount =0;
      dryCount = 0;
    }
  }

  void resetFunct(){
    digitalWrite(relayOne, HIGH); 
    digitalWrite(relayTwo, HIGH); 
    washCount 
    resetScreen();
  }

void resetScreen()
{
  delay(5000); //5 seconds
  for(int i = 0; i < 4; i++)
  {
    lcd.setCursor(0,i);  lcd.print("                    ");
  }
  Serial.println("Screen Cleared.");

  lcd.setCursor(0, 1); lcd.print("WashCount = "); lcd.print(washCount);
  
  Serial.println("WashCount = "); Serial.print(washCount);
  Serial.write("W - WashCount = "); Serial.write(washCount);


  lcd.setCursor(0, 2); lcd.print("DryCount = "); lcd.print(dryCount);
  Serial.println("DryCount = "); Serial.print(dryCount);

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
