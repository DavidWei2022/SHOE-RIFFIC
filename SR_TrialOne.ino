/*
  PURPOSE - FIRST DESIGN OF SHOE-RIFFIC FIRMWARE
  DEV - AARUSHI DHANGER & DAVID WEI
  DATE - 07/24/2023 
*/

//NOTE - LCD display is 20x4, so we have 80 character max
#include <LiquidCrystal.h> 

//init library w/ numbers of interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // register selection, enable, 5 = d4, 4 = d5, 3 = d6, 2 = d7

//NOTE - nano has 14 digi I/O pins
//assigns push buttons to nano pins
const int dryPin = 7;
const int washPin = 8;
const int quickWashPin = 9;

//assign LCD Display to nano pins
const int display = 10;

//assigns relay to nano pins (not sure if i can use these pins?)
const int relayOne = 11;
const int relayTwo = 12;
const int relayThree = 13; 
//resetPin  to be reset pin
const int resetPin  = 14;

//counter variables
int washCount = 0;
int dryCount = 0;
//real values TBD
int maxWash = 100;
int maxDry = 75;
//time constants
int quickWashTime = 60000;
int WashTime = 120000;
int dryTime = 30000;


void setup() {
  // put your setup code here, to run once:

  pinMode(relayOne, OUTPUT);
  pinMode(relayTwo, OUTPUT);
  pinMode(relayThree, OUTPUT);
  pinMode(resetPin , OUTPUT);
  //init dryBtn as input
  pinMode(dryPin, INPUT_PULLUP);
  //init washBtn as input
  pinMode(washPin, INPUT_PULLUP);
  //init quickWashBtn as input
  pinMode(quickWashPin, INPUT_PULLUP);
  //init reset as input
  pinMode(resetPin, INPUT_PULLUP);
  
  //turns relays off then on
  digitalWrite(relayOne, HIGH); 
  digitalWrite(relayTwo, HIGH); 
  digitalWrite(relayThree, HIGH); 
  digitalWrite(resetPin , HIGH); 
  
  //sets up LCD's # of col & row
  lcd.begin(16, 2);
  //lcd.print("Welcome");
  lcd.print("WashCount = "); lcd.print(washCount);
  Serial.print("WashCount = "); Serial.print(washCount);
  //sets cursor to col0, line1 (aka row2)
  lcd.setCursor(0, 1); 
  lcd.print("DryCount = "); lcd.print(dryCount);
  Serial.print("DryCount = "); Serial.print(dryCount);
}

void loop() {
  while (washCount < maxWash &&dryCount < maxDry){
    //check if each button is pressed (LOW), then allow the relay to power the designated unit
    //added delay function to make user to hold a button for 3 seconds before performing any functions
    if(digitalRead(quickWashPin)== LOW){
      lcd.clear();//clear screen to print new words
      lcd.print("You selected wash, please hold it for 2 second"); //9 Words, 46 characters
      delay(2000);
      lcd.clear();
        //user has confirmed he/she wants to wash
        if(digitalRead(washPin) ==LOW){
          lcd.print("Initializing Washing....");
          wash(quickWashTime);
         }
      lcd.clear();
    }



//  disabled deep wash for now since we only have 3 buttons 

    // if(digitalRead(washPin)== LOW){
    //   delay(3000);
    //   wash(WashTime);
    // }




    if(digitalRead(dryPin)== LOW){
      lcd.clear();//clear screen to print new words
      lcd.print("You selected dry, please hold it for 2 second"); //9 Words, 45 characters
      delay(2000);
      lcd.clear();
      if(digitalRead(dryPin)== LOW){
        lcd.print("Initializing Drying....");
        dry(dryTime);
      }
      lcd.clear();
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
    if(time <=quickWashTime)
      washCount =washCount +1;
    else
      washCount = washCount+2;
  }

  void dry(int time){
    digitalWrite(relayThree, LOW);
    delay(time); //real values TBD
    digitalWrite(relayThree, HIGH);
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
