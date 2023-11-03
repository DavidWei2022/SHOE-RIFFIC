#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // 0X27 = SCREEN ADDRESS 

const int relayOne = 2; //pump relay
const int relayTwo = 3; //fan relay
  
const int resetPin = 4; //change to reset pin 
const int dryPin = 5; 
const int washPin = 6;

void setup() {
  // put your setup code here, to run once:
 lcd.init();
  lcd.backlight();

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);

  pinMode(5, INPUT_PULLUP);    //init dryBtn as input
  pinMode(6, INPUT_PULLUP);   //init washBtn as input
  pinMode(4, INPUT_PULLUP);  //init reset as input

  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  lcd.clear();

 
  delay(2000);

   lcd.clear();
    lcd.setCursor(0,0);  lcd.print("Button State Check");
    lcd.setCursor(0,1);  lcd.print("Reset: ");
    lcd.setCursor(0,2);  lcd.print("Dry: ");  
    lcd.setCursor(0,3); lcd.print("Wash: "); 

      delay(200);
 
}

void loop() {

      
}


    
