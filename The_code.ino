#include <LiquidCrystal_I2C.h>
#define ledg 2
#define leds 4
#define ledb 7
#define ninored 11
#define ninoblue 12
#define tmp 0
#define lightsen 1
#define soilsen 2
#define sound 9

LiquidCrystal_I2C lcd(0x27, 16, 2);
int celsius = 0;
int baselinetemp = 0;

int State = 0;
void State0()
 {
  	digitalWrite(ninored,LOW);
   digitalWrite(ninoblue,LOW);
   tone(sound, 1000);
  	delay(1000);
 }
void State1()
 {
  	digitalWrite(ninored,HIGH);
   digitalWrite(ninoblue,HIGH);
   noTone(sound);
  	delay(1000);
 }

void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(ledg, OUTPUT);
  pinMode(leds, OUTPUT);
  pinMode(ledb, OUTPUT);
  pinMode(ninored, OUTPUT);
  pinMode(ninoblue, OUTPUT);
  pinMode(tmp, INPUT);
  pinMode(lightsen, INPUT);
  pinMode(soilsen, INPUT);
  pinMode(sound, OUTPUT);;
}

void loop()
{
  digitalWrite(ledg,LOW);
  digitalWrite(leds,LOW);
  digitalWrite(ledb,LOW);
  digitalWrite(ninored,HIGH);
  digitalWrite(ninoblue,LOW);
  baselinetemp = 27;
  celsius = map(((analogRead(tmp) - 20) * 3.04), 0, 1023, -40, 125);
  if (celsius < baselinetemp){
   digitalWrite(ledg, LOW); 
  }
  if (celsius >= baselinetemp){
   digitalWrite(ledg, HIGH); 
  }
  
  while (ledg != LOW && leds != LOW && ledb != LOW){
  	switch (State)
    {
    	case 0:
      		State = 1;
      		State1();
      		break;
      
      	case 1:
      		State = 0;
      		State0();
      		break;
    }
  }
  digitalWrite(ninored,HIGH);
  digitalWrite(ninoblue,LOW);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(celsius);
}
