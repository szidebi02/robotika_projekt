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

void setup()
{
  Serial.begin(115200);
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
  lcd.print("Hello!");
}
