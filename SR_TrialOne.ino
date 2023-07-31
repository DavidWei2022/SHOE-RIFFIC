/*
  PURPOSE - FIRST DESIGN OF SHOE-RIFFIC FIRMWARE
  DEV - AARUSHI DHANGER
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

//counter variables
int washCount = 0;
int dryCount = 0;
//time constants
int quickWashTime = 60000;
int WashTime = 120000;
int dryTime = 30000;

void setup() {
  // put your setup code here, to run once:

  pinMode(relayOne, OUTPUT);
  pinMode(relayTwo, OUTPUT);
  pinMode(relayThree, OUTPUT);
  
  //init dryBtn as input
  pinMode(dryPin, INPUT_PULLUP);
  //init washBtn as input
  pinMode(washPin, INPUT_PULLUP);
  //init quickWashBtn as input
  pinMode(quickWashPin, INPUT_PULLUP);
  
  //turns relays off then on
  digitalWrite(relayOne, HIGH); 
  digitalWrite(relayTwo, HIGH); 
  digitalWrite(relayThree, HIGH); 

  //sets up LCD's # of col & row
  lcd.begin(16, 2);
  //lcd.print("Welcome");
  lcd.print("WashCount = "); lcd.print(washCount);
  //sets cursor to col0, line1 (aka row2)
  lcd.setCursor(0, 1); 
  lcd.print("DryCount = "); lcd.print(dryCount);
}

void loop() {
  // put your main code here, to run repeatedly:

  //check if each button is pressed (LOW), then allow the relay to power the designated unit
  if(digitalRead(washPin)== LOW){
    //deepWash();
    digitalWrite(relayOne, LOW);
    delay(120000); //120 second delay
    digitalWrite(relayOne, HIGH);
    washCount = washCount+2;
  }

  if(digitalRead(quickWashPin)== LOW){
    //lightWash();
    digitalWrite(relayTwo, LOW);
    delay(60000); //60 second delay
    digitalWrite(relayTwo, HIGH);
    washCount = washCount+1;

  }

  if(digitalRead(dryPin)== LOW){
    //dry();
    digitalWrite(relayThree, LOW);
    delay(30000); //30 second delay
    digitalWrite(relayThree, HIGH);
    dryCount = dryCount+1; //EDITED - fixed wrong increment

  }

}
//sub functions created for unit test
  void deepWash(int time){
    digitalWrite(relayOne,LOW);
    delay(time); // real values TBD
    digitalWrite(relayOne, HIGH);
    washCount = washCount+2;
  }
  
  void lightWash(int time){
    digitalWrite(relayTwo, LOW);
    delay(time); //real values TBD
    digitalWrite(relayTwo, HIGH);
    washCount = washCount+1;
  }
  
  void dry(int time){
    digitalWrite(relayThree, LOW);
    delay(time); //real values TBD
    digitalWrite(relayThree, HIGH);
    dryCount = dryCount+1;
  }

//unit test functions
  //for deepWashing   time ranges from 60 seconds to 180 seconds
    void TestDW60(){deepWash(60000);}
    void TestDW90(){deepWash(90000);}
    void TestDW120(){deepWash(120000);}
  //for lightWashing  time ranges from 30 seconds to 50 seconds
    void TestLW20(){lightWash(30000);}
    void TestLW30(){lightWash(40000);}
    void TestLW40(){lightWash(50000);}
  // for drying time ranges from 30 seconds to 45 seconds
    void TestDR30(){dry(30000);}
    void TestDR40(){dry(40000);}
    void TestDR45(){dry(45000);}
