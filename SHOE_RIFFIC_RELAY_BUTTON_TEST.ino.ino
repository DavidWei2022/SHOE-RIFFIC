#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // 0X27 = SCREEN ADDRESS 

const int relayOne = 2; //pump relay
const int relayTwo = 3; //fan relay
  
const int resetPin = 4; //change to reset pin 
const int dryPin = 5; 
const int washPin = 6;

//counter variables
int washCount = 0;
int dryCount = 0;
int firstTime= 0;
//real values TBD
int maxWash = 100;
int maxDry = 75;

//time constants
unsigned long seconds = 1000L;
unsigned long forty_five = 45*seconds;
int washTime = 30000;
int dryTime = 30000;

void setup() {

  lcd.init();
  lcd.backlight();

  pinMode(relayOne, OUTPUT);
  pinMode(relayTwo, OUTPUT);

  pinMode(dryPin, INPUT_PULLUP);    //init dryBtn as input
  pinMode(washPin, INPUT_PULLUP);   //init washBtn as input
  pinMode(resetPin, INPUT_PULLUP);  //init reset as input

  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
}

void loop() {
  //it's gonna add some delays but it should work
  if(firstTime ==0){
    welcome();
  }
  else{
    if(digitalRead(resetPin) == LOW){
        lcd.clear();//clear screen to print new words
        lcd.setCursor(0,2);lcd.print("Reset Selected."); //9 Words, 45 characters
        delay(2000);
      resetFunct();
      delay(1000);  
    }
    else{
      digitalRead(resetPin) == HIGH;
        lcd.setCursor(0,2); lcd.print("Reset: OFF"); 
    }
  

    if(digitalRead(dryPin) == LOW){
        lcd.clear();
        lcd.setCursor(0,1);lcd.print("Dry Selected."); //2 Words, 13 characters
        delay(2000);
        dry(forty_five);
        lcd.clear();  
    }

    else {
        digitalRead(dryPin) == HIGH;
        lcd.setCursor(0,1); lcd.print("Dry Count: ");   
        lcd.setCursor(12,1);lcd.print(dryCount);
    }
        

    if(digitalRead(washPin) == LOW){
        lcd.clear();
        lcd.print("Wash Selected."); 
        delay(2000);
        wash(washTime);
        lcd.clear(); 
    }

    else {
      digitalRead(washPin) == HIGH;
      lcd.setCursor(0,0); lcd.print("Wash Count: ");  
      lcd.setCursor(12,0);lcd.print(washCount);
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
}


//sub functions created for unit test
  void wash(int time){
    //b4 it was LOW then HIGH
    digitalWrite(relayOne,HIGH);
    delay(time); // real values TBD
    digitalWrite(relayOne, LOW);

    washCount =washCount +1;
    firstTime=0;
  }

  void dry(int time){
    //b4 it was LOW then HIGH
    digitalWrite(relayTwo, HIGH);
    delay(time); //real values TBD
    digitalWrite(relayTwo, LOW);
    
    dryCount = dryCount+1;
    firstTime=0;
  }

  void maintenance(){
    lcd.clear();
    lcd.print("WARNING! maintenance required"); 
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
      lcd.clear();
    firstTime=0;
  }

void welcome(){
    lcd.clear();
    lcd.setCursor(0,0); lcd.print("--------------------");
    lcd.setCursor(0,1); lcd.print("     WELCOME TO");
    lcd.setCursor(0,2); lcd.print("   SHOE - RIFFIC! ");
    lcd.setCursor(0,3); lcd.print("--------------------");
    delay(3000);
    lcd.clear();
    firstTime = 1;
}
