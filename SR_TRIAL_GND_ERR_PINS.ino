#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // 0X27 = SCREEN ADDRESS 

const int relayOne = 2; //pump relay
const int relayTwo = 3; //fan relay
  
const int resetPin = 4; //change to reset pin 
const int dryPin = 5; 
const int washPin = 6;
/*
//use these pins for error handling
const int resetErrorPin = 7; 
const int dryErrorPin = 8;
const int washErrorPin = 9;
//assigns relay to nano pins 
*/
//counter variables
int washCount = 0;
int dryCount = 0;

//real values TBD
int maxWash = 100;
int maxDry = 75;

//time constants
//int quickWashTime = 30000;
int washTime = 2000;
int dryTime = 2000;

void setup() {
  // put your setup code here, to run once:
 lcd.init();
  lcd.backlight();

  pinMode(relayOne, OUTPUT);
  pinMode(relayTwo, OUTPUT);

  pinMode(dryPin, INPUT);    //init dryBtn as input
  pinMode(washPin, INPUT);   //init washBtn as input
  pinMode(resetPin, INPUT);  //init reset as input

  //digitalWrite(7, LOW);
  //digitalWrite(8, LOW);
  //digitalWrite(9, LOW);

  digitalWrite(relayOne, LOW);
  digitalWrite(relayTwo, LOW);
  lcd.clear();
  lcd.setCursor(0,0);  lcd.print("Relay State Check"); //checking state of pump and fan relay
  lcd.setCursor(0,1);  lcd.print("Pump Relay: ");
  lcd.setCursor(0,2);  lcd.print("Fan Relay: "); 

  // delay(2000);
  lcd.setCursor(12,1);  lcd.print("ON ");
  digitalWrite(relayOne, HIGH);
  // delay(2000);

  lcd.setCursor(12,1);  lcd.print("OFF");
  digitalWrite(relayOne, LOW);
  // delay(2000);

   lcd.setCursor(11,2);  lcd.print("ON ");
  digitalWrite(relayTwo, HIGH);
  // delay(2000);

  lcd.setCursor(11,2);  lcd.print("OFF");
  digitalWrite(relayTwo, LOW);
  // delay(2000);
     lcd.clear();
    lcd.setCursor(0,0);  lcd.print("Button State Check");
    lcd.setCursor(0,1);  lcd.print("Reset: ");
    lcd.setCursor(0,2);  lcd.print("Dry: ");  
    lcd.setCursor(0,3); lcd.print("Wash: "); 
    delay(2000);
    lcd.clear();
    // digitalWrite(4, HIGH);
    // digitalWrite(5, HIGH);
    // digitalWrite(6, HIGH);
    // delay(200);

}

void loop() {
  //  while (washCount < maxWash &&dryCount < maxDry){    

  if(digitalRead(resetPin) == HIGH){
    lcd.clear(); //clear screen to print new words
    lcd.print("Reset Selected."); //9 Words, 45 characters
    delay(3000);
    resetFunct();
    delay(3000);  
  }
  else{
    digitalRead(resetPin) == LOW; //WE DON'T WHY THIS WORKS, BUT IT DOES
    lcd.setCursor(0,2); lcd.print("Reset: OFF"); 
  }
       

 if(digitalRead(dryPin) == HIGH){
    lcd.clear();//clear screen to print new words
    lcd.print("Dry Selected."); //9 Words, 45 characters
    delay(2000);
    lcd.clear();
    dry(dryTime);
    lcd.clear();  
  }
  else {
    digitalRead(dryPin) == LOW; //WE DON'T WHY THIS WORKS, BUT IT DOES
    lcd.setCursor(0,1); lcd.print("Dry Count: ");   
    lcd.setCursor(12,1);lcd.print(dryCount);
  }
      

  if(digitalRead(washPin) == HIGH){
    lcd.clear();//clear screen to print new words
    lcd.print("Wash Selected."); //9 Words, 46 characters
    delay(2000);
    wash(washTime);
    lcd.clear(); 
  }
  else {
    digitalRead(washPin) == LOW; //WE DON'T WHY THIS WORKS, BUT IT DOES
    lcd.setCursor(0,0); lcd.print("Wash Count: ");  //13   
    lcd.setCursor(12,0);lcd.print(washCount);
  }

   if(washCount >= maxWash){
     lcd.clear();
     lcd.print("wash count exceeded!");
     delay(5000);
    maintenance();
    // break;
  }
  if(dryCount >= maxDry){
    lcd.clear();
    lcd.print("dry count exceeded!");
    maintenance();
    // break;
  }

}



//sub functions created for unit test
  void wash(int time){
    //b4 it was LOW then HIGH
    digitalWrite(relayOne,HIGH);
    delay(time); // real values TBD
    digitalWrite(relayOne, LOW);
    
    washCount = washCount + 1;
  }

  void dry(int time){
    //b4 it was LOW then HIGH
    digitalWrite(relayTwo, HIGH);
    delay(time); //real values TBD
    digitalWrite(relayTwo, LOW);
    
    dryCount = dryCount+1;
  }

  void maintenance(){
    lcd.clear();
    lcd.print("WARNING! maintenance required"); 
    
    //for reset, we ask the maintenance guy to wait 60 seconds before pressing the reset
    delay(3000);
    if(digitalRead(resetPin)== LOW){
      resetFunct();
    }
  }

  void resetFunct(){
      // digitalWrite(relayOne, HIGH); 
      // digitalWrite(relayTwo, HIGH); 
      digitalWrite(relayOne, LOW); 
      digitalWrite(relayTwo, LOW); 
      washCount = 0;
      dryCount = 0;
    resetScreen();
  }

void resetScreen()
{
  // delay(5000); //5 seconds
  for(int i = 0; i < 4; i++)
  {
    lcd.setCursor(0,i);  lcd.print("                    ");
  }
  Serial.println("Screen Cleared.");
  delay(2000);
  lcd.setCursor(0, 1); lcd.print("WashCount = "); lcd.print(washCount);
  
  Serial.println("WashCount = "); Serial.print(washCount);
  Serial.write("W - WashCount = "); Serial.write(washCount);


  lcd.setCursor(0, 2); lcd.print("DryCount = "); lcd.print(dryCount);
  Serial.println("DryCount = "); Serial.print(dryCount);

}

    