/* LAST REFERENCED FILE: 11_04_2023_test_file */

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // 0X27 = SCREEN ADDRESS 

//assigns relay to nano pins
const int relayOne = 2; //pump relay
const int relayTwo = 3; //fan relay

//assign push buttons NO pins to arduino nano
const int resetPin = 4;  
const int dryPin = 5; 
const int washPin = 6;

//counter variables
int washCount = 0;
int dryCount = 0;

/* max acceptable cycles */
int maxWash = 10;
int maxDry = 10;

/* time constants for wash and dry duration */
int washTime = 30000;
int dryTime = 30000;

void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();

  pinMode(relayOne, OUTPUT);
  pinMode(relayTwo, OUTPUT);

  pinMode(dryPin, INPUT_PULLUP);    //init dryBtn as input
  pinMode(washPin, INPUT_PULLUP);   //init washBtn as input
  pinMode(resetPin, INPUT_PULLUP);  //init reset as input

  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  lcd.clear();
  welcome();
  delay(2000); 
  resetScreen(washCount, dryCount);

}

void loop() {

  if(digitalRead(resetPin) == LOW){
    lcd.setCursor(7,1); lcd.print("ON ");
    delay(2000);
    resetFunct();
    delay(2000);  
  }
  else{
     digitalRead(resetPin) == HIGH;
  }
       

  if(digitalRead(dryPin) == LOW){
    lcd.setCursor(7,2); lcd.print("ON ");
    delay(2000);
    dry(dryTime);
  }
  else {
    digitalRead(dryPin) == HIGH;
  }
      

  if(digitalRead(washPin) == LOW){
    lcd.setCursor(7,3); lcd.print("ON ");
    delay(2000);
    wash(washTime);
  }
  else{
    digitalRead(washPin) == HIGH;
  }

  if(washCount >= maxWash){
    lcd.clear();
    lcd.print("Wash Count Exceeded!");
    delay(5000);
    maintenance();
  }
  else if(dryCount >= maxDry){
    lcd.clear();
    lcd.print("Dry Count Exceeded!");
    maintenance();
  }
  
}


//sub functions created for unit testing
  void wash(int time){
    digitalWrite(relayOne,HIGH);
    delay(time); 
    digitalWrite(relayOne, LOW);
    washCount =washCount + 1;
    resetScreen(washCount, dryCount);
  }

  void dry(int time){
    digitalWrite(relayTwo, HIGH);
    delay(time); 
    digitalWrite(relayTwo, LOW);
    dryCount = dryCount + 1;
    resetScreen(washCount, dryCount);
  }

  void maintenance(){
    lcd.clear();
    lcd.setCursor(7,1); lcd.print("WARNING!"); 
    lcd.setCursor(0,2); lcd.print("MAINTENANCE REQUIRED"); 
    
    //for reset, we ask the maintenance guy to wait 60 seconds before pressing the reset
    delay(30000);
    delay(30000);
    lcd.clear();
    lcd.setCursor(0,0);lcd.print("Please Hold Reset");
    delay(3000);
    if(digitalRead(resetPin)== LOW){
      resetFunct();
    }
  }

  void resetFunct(){
    digitalWrite(relayOne, LOW); 
    digitalWrite(relayTwo, LOW); 
    washCount =0;
    dryCount = 0;
    resetScreen(washCount, dryCount);
  }

void welcome(){
  lcd.setCursor(0,0);  lcd.print("--------------------"); 
  lcd.setCursor(0,1);  lcd.print("     WELCOME TO");
  lcd.setCursor(0,2);  lcd.print("   SHOE - RIFFIC! ");
  lcd.setCursor(0,3);  lcd.print("--------------------");
}

void resetScreen(int wCNT, int dCNT)
{
  lcd.clear();
  lcd.setCursor(0,0); lcd.print("Selection Options");
  lcd.setCursor(0,1); lcd.print("Reset: "); lcd.setCursor(7,1); lcd.print("OFF ");
  lcd.setCursor(0,2); lcd.print("Dry: ");   lcd.setCursor(7,2); lcd.print("OFF"); lcd.setCursor(10,2); lcd.print(" COUNT: "); lcd.setCursor(17, 2); lcd.print(dCNT);
  lcd.setCursor(0,3); lcd.print("Wash: ");  lcd.setCursor(7,3); lcd.print("OFF"); lcd.setCursor(11,3); lcd.print("COUNT: "); lcd.setCursor(17, 3); lcd.print(wCNT);

}
