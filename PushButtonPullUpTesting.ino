    delay(200);
  if(digitalRead(4) == LOW){
      lcd.setCursor(7,1); lcd.print("ON ");   
  }

else{
     digitalRead(4) == HIGH;
      lcd.setCursor(7,1); lcd.print("OFF"); 
  }
       

 if(digitalRead(5) == LOW){
      lcd.setCursor(5,2); lcd.print("ON ");   
  }

else {
    digitalRead(5) == HIGH;
      lcd.setCursor(5,2); lcd.print("OFF");   
  }
      

if(digitalRead(6) == LOW){
      lcd.setCursor(6,3); lcd.print("ON ");   
  }

  else {
    digitalRead(6) == HIGH;
    lcd.setCursor(6,3); lcd.print("OFF");     
}
