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
int light = 0;
int soil = 0;
int baselinetemp = 27;
int baselightlevel = 50;
int basesoillevel = 300;

int State = 0;

void LedStates()
{
  switch(celsius < baselinetemp)
  {
  case true:
    digitalWrite(ledg, HIGH);
    break;
  case false:
    digitalWrite(ledg, LOW);
    break;
  }

  switch (light < baselightlevel)
  {
  case true:
    digitalWrite(light, HIGH);
    break;
  case false:
    digitalWrite(light, LOW);
    break;
  }

  switch (soil < basesoillevel)
  {
  case true:
    digitalWrite(soil, HIGH);
    break;
  case false:
    digitalWrite(soil, LOW);
    break;
  }
}

void lcdWrite()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(celsius);

  switch (digitalRead(light))
  {
  case LOW:
    lcd.print("Light");
    break;
  case HIGH:
    lcd.print("Dark");
    break;
  }

  lcd.setCursor(0, 1);
  switch (digitalRead(soil))
  {
  case LOW:
    lcd.print("Wet");
    break;
  case HIGH:
    lcd.print("Dry");
    break;
  }
}


void State0()
{
  LedStates();
  lcdWrite();
}
void State1()
{
  LedStates();
  lcdWrite();
  digitalWrite(ninored, LOW);
  digitalWrite(ninoblue, LOW);
  tone(sound, 1000);
  delay(1000);
}
void State2()
{
  LedStates();
  lcdWrite();
  digitalWrite(ninored, HIGH);
  digitalWrite(ninoblue, HIGH);
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
  pinMode(sound, OUTPUT);
}

void loop()
{
  digitalWrite(ledg, LOW);
  digitalWrite(leds, LOW);
  digitalWrite(ledb, LOW);
  digitalWrite(ninored, HIGH);
  digitalWrite(ninoblue, LOW);

  celsius = map(((analogRead(tmp) - 20) * 3.04), 0, 1023, -40, 125);
  light = analogRead(lightsen);
  soil = analogRead(soilsen);

  switch (State)
  {
  case 0:
    State0();
    if (ledg != LOW && ledb != LOW && leds != LOW)
    {
      State = 1;
    }
    break;
  case 1:
    State1();
    while (ledg != LOW && ledb != LOW && leds != LOW)
    {
      State = 2;
    }
    State = 0;
    break;
  case 2:
    State2();
    while (ledg != LOW && ledb != LOW && leds != LOW)
    {
      State = 1;
    }
    State = 0;
    break;
  }
}
