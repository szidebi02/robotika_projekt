#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ledg 2
#define leds 4
#define ledb 7
#define ninored 11
#define ninoblue 12
#define tmp 5
#define lightsen 1
#define soilsen 2
#define sound 9

LiquidCrystal_I2C lcd(0x27, 16, 2);
OneWire oneWire(tmp);
DallasTemperature sensors(&oneWire);
int celsius = 0;
int light = 0;
int soil = 0;
int baselinetemp = 27;
int baselightlevel = 50;
int basesoillevel = 300;

int State = 0;

void LedStates()
{
  if (celsius < baselinetemp)
  {
    digitalWrite(ledg, LOW);
  }
  if (celsius >= baselinetemp)
  {
    digitalWrite(ledg, HIGH);
  }

  if (light < baselightlevel)
  {
    digitalWrite(light, LOW);
  }
  if (light >= baselightlevel)
  {
    digitalWrite(light, HIGH);
  }

  if (soil < basesoillevel)
  {
    digitalWrite(soil, LOW);
  }
  if (soil >= basesoillevel)
  {
    digitalWrite(soil, HIGH);
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
  case HIGH:
    lcd.print("Suitable");
    break;
  case LOW:
    lcd.print("Dark");
  }

  lcd.setCursor(0, 1);
  switch (digitalRead(soil))
  {
  case HIGH:
    lcd.print("Wet");
    break;
  case LOW:
    lcd.print("Dry");
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
  ;
}

void loop()
{
  sensors.requestTemperatures();
  digitalWrite(ledg, LOW);
  digitalWrite(leds, LOW);
  digitalWrite(ledb, LOW);
  digitalWrite(ninored, HIGH);
  digitalWrite(ninoblue, LOW);
  celsius = sensors.getTempCByIndex(0);
  light = analogRead(lightsen);
  soil = analogRead(soilsen);
  lcd.clear();
  lcd.setCursor(6, 1);
  lcd.print(light);
  delay(10000);
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
