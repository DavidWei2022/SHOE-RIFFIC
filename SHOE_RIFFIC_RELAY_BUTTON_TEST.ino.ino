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

int maxWash = 100;
int maxDry = 75;

//time constants (in ms)
int washTime = 45000;
int dryTime = 45000;

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
        lcd.print("Reset Selected."); //9 Words, 45 characters
        delay(2000);
      resetFunct();
      delay(1000);  
    }
    else{
      digitalRead(resetPin) == HIGH;
        lcd.setCursor(0,2); lcd.print("Reset: OFF"); 
    }
        

    if(digitalRead(dryPin) == LOW){
      lcd.clear();//clear screen to print new words
        lcd.print("Dry Selected."); //2 Words, 13 characters
        delay(2000);
        lcd.clear();
        dry(dryTime);
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
      lcd.print("wash count exceeded!");
      delay(5000);
      lcd.clear();
      maintenance();
    }
    else if(dryCount >= maxDry){
      lcd.clear();
      lcd.print("dry count exceeded!");
      lcd.clear();
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
  }

  void dry(int time){
    digitalWrite(relayTwo, HIGH);
    delay(time); //real values TBD
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
    resetScreen();
  }

void resetScreen()
{
  lcd.clear();
  for(int i = 0; i < 4; i++)
  {
    lcd.setCursor(0,i);  lcd.print("                    ");
  }
  Serial.println("Screen Cleared.");
  delay(2000);
  lcd.clear();
}

void welcome(){
    lcd.clear();
    lcd.setCursor(0,0); lcd.print("--------------------");
    lcd.setCursor(0,1); lcd.print("     WELCOME TO");
    lcd.setCursor(0,2); lcd.print("   SHOE - RIFFIC! ");
    lcd.setCursor(0,3); lcd.print("--------------------");
    delay(5000);
    lcd.clear();
    firstTime = 1;
}
