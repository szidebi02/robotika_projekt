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
#define moisturesen 2
#define sound 6

LiquidCrystal_I2C lcd(0x27, 16, 2);
OneWire oneWire(tmp);
DallasTemperature sensors(&oneWire);
int celsius = 0;
int light = 0;
int moisture = 0;
int baseLineTemp = 27;
int baseLightLevel = 25;
int baseMoistureLevel = 150;

int state = 0;

bool Temperature(int cel){
  if (cel > baseLineTemp){
    return true;
  }
  return false;
}

bool LightLevel(int light){
  if (light > baseLightLevel){
    return true;
  }
  return false;
}

bool MoistureLevel(int moisture){
  if (moisture > baseMoistureLevel){
    return true;
  }
  return false;
}

void lcdWrite()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(celsius);

  lcd.setCursor(0, 1);
  if (LightLevel(analogRead(lightsen))) {
    lcd.print("Day");
  }
  else {
    lcd.print("Night");
  }

  lcd.setCursor(6, 1);
  if (MoistureLevel(analogRead(moisturesen))) {
    lcd.print("Wet");
  }
  else {
    lcd.print("Dry");
  }
}

void State0(){
  digitalWrite(ninored, HIGH);
  digitalWrite(ninoblue, HIGH);
  tone(sound, 1000, 500);
  noTone(sound);
}

void State1(){
  digitalWrite(ninored, LOW);
  digitalWrite(ninoblue, LOW);
  tone(sound, 1500, 500);
  noTone(sound);
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
  pinMode(moisturesen, INPUT);
  pinMode(sound, OUTPUT);
}

void loop()
{
  sensors.requestTemperatures();
  celsius = sensors.getTempCByIndex(0);
  light = analogRead(lightsen);
  moisture = analogRead(moisturesen);
  bool tempInvestigation = Temperature(celsius);
  bool lightInvestigation = LightLevel(light);
  bool moistureInvestigation = MoistureLevel(moisture);
  digitalWrite(ledg, LOW);
  digitalWrite(leds, LOW);
  digitalWrite(ledb, LOW);
  digitalWrite(ninored, LOW);
  digitalWrite(ninoblue, LOW);
  noTone(sound);

  lcdWrite();
  delay(1000);
  
  if (tempInvestigation) {
    digitalWrite(ledg, HIGH);
  }
  else {
    digitalWrite(ledg, LOW);
  }

  if (lightInvestigation) {
    digitalWrite(leds, HIGH);
  }
  else {
    digitalWrite(leds, LOW);
  }

  if (moistureInvestigation) {
    digitalWrite(ledb, HIGH);
  }
  else {
    digitalWrite(ledb, LOW);
  }

  lcdWrite();
  delay(1000);

  while (!tempInvestigation && !lightInvestigation && !moistureInvestigation) {
    lcdWrite();
    delay(200);

    if (!tempInvestigation && !lightInvestigation && !moistureInvestigation) {
      switch (state){
        case 0:
          state = 1;
          State1();
          break;
        case 1:
          state = 0;
          State0();
          break;
      }
    }

    tempInvestigation = Temperature(celsius);
    lightInvestigation = LightLevel(light);
    moistureInvestigation = MoistureLevel(moisture);

    lcdWrite();
    delay(200);
  }

  delay(1000);
  lcdWrite();
  delay(1000);
}
