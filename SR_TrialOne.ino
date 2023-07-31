
/*Controls*/
#define PIN_INT 2 
#define PIN_M_IO 51
#define PIN_ALE 49
#define PIN_WRITE 45
#define PIN_READ 43

/* AD pin mapping. */
static int8_t AD_PINS[8]={38,40,42,44,46,48,50,52};
#define AD_PINS_SIZE (sizeof (AD_PINS) / sizeof (AD_PINS[0]))

/* Set ALE and M_IO signals to be active high. */
#define ALE_DISABLE() digitalWrite(PIN_ALE, LOW);
#define ALE_ENABLE() digitalWrite(PIN_ALE, HIGH);
#define M_IO_DISABLE() digitalWrite(PIN_M_IO, LOW);
#define M_IO_ENABLE() digitalWrite(PIN_M_IO, HIGH);

/* Set read and write signals to be active low. */
#define WRITE_DISABLE() digitalWrite(PIN_WRITE, HIGH);
#define WRITE_ENABLE() digitalWrite(PIN_WRITE, LOW);
#define READ_DISABLE() digitalWrite(PIN_READ, HIGH);
#define READ_ENABLE() digitalWrite(PIN_READ, LOW);


void memWrite(int8_t addr, int8_t data);
void memRead(int8_t addr);
void write_byte(int8_t b);
void read_byte(int8_t b);
void address_latch(int8_t addr);


void setup() 
{ 
  pinMode (38,INPUT);
  pinMode (40,INPUT);
  pinMode (42,INPUT);
  pinMode (44,INPUT);
  pinMode (46,INPUT);
  pinMode (48,INPUT);
  pinMode (50,INPUT);
  pinMode (52,INPUT);
  pinMode(PIN_READ, OUTPUT);
  pinMode(PIN_WRITE, OUTPUT);
  pinMode(PIN_ALE, OUTPUT);
  pinMode(PIN_M_IO, OUTPUT);
  Serial.begin(9600);
// SRAM1
delay(1000);
Serial.println("\nSRAM1:Reading address 30");
Serial.print("Data: ");
memWrite(0x30,0x55);
memRead(0x30);
digitalWrite(PIN_READ,LOW);
delay(1000);
digitalWrite(PIN_READ,HIGH);
// SRAM2
Serial.println("SRAM2: Reading address 40");
Serial.print("Data: ");
memWrite(0x80,0xFF);
memRead(0x80);
delay(1000);
digitalWrite(PIN_READ,LOW);
} 

void write_byte(int8_t b)
{
  int i;
  for (i = 0; i < AD_PINS_SIZE; i++) 
  {
   pinMode(AD_PINS[i], OUTPUT);
  }
  for (i = 0; i < AD_PINS_SIZE; i++)
  {
    digitalWrite(AD_PINS[i], ((b >> (AD_PINS_SIZE-1-i)) & 1));
  }
}

void read_byte(int8_t b)
{
  int i;
  int8_t d = 0b00000000;
  for (i = 0; i < AD_PINS_SIZE; i++)
  {
    pinMode(AD_PINS[i], INPUT);
    d = digitalRead(AD_PINS[i]);
    Serial.print(d);
  }
  Serial.print("\n");
}


void memWrite(int8_t addr, int8_t data)
{
  /* Disable read, enable M/IO*/
  READ_DISABLE();
  M_IO_ENABLE();

  /* Latch the address. */
  address_latch(addr);

  /* Enable write to be ready to write on the data bus */
  WRITE_ENABLE();

  /* Place the data onto the data bus. */
  write_byte(data);
  delay(1);
  WRITE_DISABLE();  
}


void memRead(int8_t addr){
  /* disable write, enable read and M/IO */
  WRITE_DISABLE();
 
  M_IO_ENABLE();

  /*Latch the address. */
  address_latch(addr);
  READ_ENABLE();
  read_byte(addr);
  delay(100);
  READ_DISABLE();
}

void address_latch(int8_t addr){
  digitalWrite(PIN_ALE, 1); // Prepare to latch an address
  write_byte(addr); // Place addr on data bus
  digitalWrite(PIN_ALE, 0); // Disable ALE so that subsequent writes to the bus are not latched
}

void loop() { 
 
} 






