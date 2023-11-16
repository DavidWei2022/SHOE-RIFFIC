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
int maxWash = 100;
int maxDry = 75;

/* time constants for wash and dry duration */
int washTime = 45000;
int dryTime = 45000;

void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);  lcd.print("--------------------"); 
  lcd.setCursor(0,1);  lcd.print("     WELCOME TO");
  lcd.setCursor(0,2);  lcd.print("   SHOE - RIFFIC! ");
  lcd.setCursor(0,3);  lcd.print("--------------------");

  pinMode(relayOne, OUTPUT);
  pinMode(relayTwo, OUTPUT);

  pinMode(dryPin, INPUT_PULLUP);    //init dryBtn as input
  pinMode(washPin, INPUT_PULLUP);   //init washBtn as input
  pinMode(resetPin, INPUT_PULLUP);  //init reset as input

  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  lcd.clear();
  delay(2000); 
  // resetScreen();

}

void loop() {
  //  while (washCount < maxWash &&dryCount < maxDry){    

  if(digitalRead(resetPin) == LOW){
    lcd.setCursor(7,1); lcd.print("ON ");
    lcd.clear();//clear screen to print new words
    lcd.print("Reset Selected."); //2 Words, 15 characters 
    delay(2000);
    resetFunct();
    delay(2000);  
  }
  else{
     digitalRead(resetPin) == HIGH;
    lcd.setCursor(0,2); lcd.print("Reset: OFF"); 
  }
       

  if(digitalRead(dryPin) == LOW){
    lcd.setCursor(5,2); lcd.print("ON");
    lcd.clear();//clear screen to print new words
    lcd.print("Dry Selected."); //2 Words, 13 characters
    delay(2000);
    lcd.clear();
    dry(dryTime);
    lcd.clear();  
  }
  else {
    digitalRead(dryPin) == HIGH;
    lcd.setCursor(0,1); lcd.print("Dry Count: ");   //11 characters   
    lcd.setCursor(12,1);lcd.print(dryCount);
  }
      

  if(digitalRead(washPin) == LOW){
    lcd.setCursor(6,3); lcd.print("ON");
    lcd.clear();//clear screen to print new words
    lcd.print("Wash Selected."); //2 Words, 14 characters
    delay(2000);
    lcd.clear();
    wash(washTime);
    lcd.clear(); 
  }
  else{
    digitalRead(washPin) == HIGH;
    lcd.setCursor(0,0); lcd.print("Wash Count: ");  //12 characters   
    lcd.setCursor(12,0);lcd.print(washCount);
  }

  if(washCount >= maxWash){
    lcd.clear();
    lcd.print("wash count exceeded!");
    delay(5000);
    maintenance();
  }
  else if(dryCount >= maxDry){
    lcd.clear();
    lcd.print("dry count exceeded!");
    maintenance();
  }

}


//sub functions created for unit testing
  void wash(int time){
    digitalWrite(relayOne,HIGH);
    delay(time); 
    digitalWrite(relayOne, LOW);
    washCount =washCount +1;
  }

  void dry(int time){
    digitalWrite(relayTwo, HIGH);
    delay(time); 
    digitalWrite(relayTwo, LOW);
    dryCount = dryCount+1;
  }

  void maintenance(){
    lcd.clear();
    lcd.print("WARNING! maintenance required"); 
    
    //for reset, we ask the maintenance guy to wait 60 seconds before pressing the reset
    delay(60000);
    if(digitalRead(resetPin)== LOW){
      resetFunct();
    }
  }

  void resetFunct(){
    digitalWrite(relayOne, LOW); 
    digitalWrite(relayTwo, LOW); 
    washCount =0;
    dryCount = 0;
    // resetScreen();
  }

void resetScreen()
{
  for(int i = 0; i < 4; i++)
  {
    lcd.setCursor(0,i);  lcd.print("                    ");
  }
  Serial.println("Screen Cleared.");
  delay(2000);
  
  lcd.setCursor(0,0); lcd.print("Selection Options");
  lcd.setCursor(0,1); lcd.print("Reset: "); lcd.setCursor(7,1); lcd.print("OFF ");
  lcd.setCursor(0,2); lcd.print("Dry: ");   lcd.setCursor(5,2); lcd.print("OFF");
  lcd.setCursor(0,3); lcd.print("Wash: ");  lcd.setCursor(6,3); lcd.print("OFF"); 
  delay (3000);
  lcd.clear();
  

}