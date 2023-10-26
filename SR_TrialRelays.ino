const int relayOne = 2; //wash
const int relayTwo = 3; //dry

void setup() {
  // put your setup code here, to run once:
    pinMode(relayOne, OUTPUT);
  pinMode(relayTwo, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.write("Relays = HIGH ");
  digitalWrite(relayOne, HIGH); 
  digitalWrite(relayTwo, HIGH);
  delay(5000);

  Serial.write("Relays = LOW ");
  digitalWrite(relayOne, LOW); 
  digitalWrite(relayTwo, LOW);
  delay(5000);
  
}
