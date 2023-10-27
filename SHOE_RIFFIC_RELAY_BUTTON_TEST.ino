#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // 0X27 = SCREEN ADDRESS 

const int relayOne = 2; //pump relay
const int relayTwo = 3; //fan relay
  
const int resetPin = 4; //change to reset pin 
const int dryPin = 5; 
const int washPin = 6;

//use these pins for error handling
const int resetErrorPin = 7; 
const int dryErrorPin = 8;
const int washErrorPin = 9;

void setup() {
  // put your setup code here, to run once:
 lcd.init();
  lcd.backlight();

  pinMode(relayOne, OUTPUT);
  pinMode(relayTwo, OUTPUT);

  pinMode(dryPin, INPUT);    //init dryBtn as input
  pinMode(washPin, INPUT);   //init washBtn as input
  pinMode(resetPin, INPUT);  //init reset as input

  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);

  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  lcd.clear();
  lcd.setCursor(0,0);  lcd.print("Relay State Check"); //checking state of pump and fan relay
  lcd.setCursor(0,1);  lcd.print("Pump Relay: ");
  lcd.setCursor(0,2);  lcd.print("Fan Relay: "); 

  delay(2000);
  lcd.setCursor(12,1);  lcd.print("ON ");
  digitalWrite(2, HIGH);
  delay(2000);

  lcd.setCursor(12,1);  lcd.print("OFF");
  digitalWrite(2, LOW);
  delay(2000);

   lcd.setCursor(11,2);  lcd.print("ON ");
  digitalWrite(3, HIGH);
  delay(2000);

  lcd.setCursor(11,2);  lcd.print("OFF");
  digitalWrite(3, LOW);
  delay(2000);

   lcd.clear();
    lcd.setCursor(0,0);  lcd.print("Button State Check");
    lcd.setCursor(0,1);  lcd.print("Reset: ");
    lcd.setCursor(0,2);  lcd.print("Dry: ");  
    lcd.setCursor(0,3); lcd.print("Wash: "); 

}

void loop() {
    delay(200);
  if(digitalRead(resetPin) == LOW){
      lcd.setCursor(7,1); lcd.print("ON ");   
  }

else{
     digitalRead(resetPin) == HIGH;
      lcd.setCursor(7,1); lcd.print("OFF"); 
  }
       

 if(digitalRead(dryPin) == LOW){
      lcd.setCursor(5,2); lcd.print("ON ");   
  }

else {
    digitalRead(dryPin) == HIGH;
      lcd.setCursor(5,2); lcd.print("OFF");   
  }
      

if(digitalRead(washPin) == LOW){
      lcd.setCursor(6,3); lcd.print("ON ");   
  }

  else {
    digitalRead(washPin) == HIGH;
    lcd.setCursor(6,3); lcd.print("OFF");     
}
      
}


    
