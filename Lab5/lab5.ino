#include <LiquidCrystal.h>

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

const int sensorPin = A5;
const int buzzer = 3;
float temperature = 0.0;
int val;
unsigned long tepTimer = 0;
const char* message = "WARNING!! High Temperature!";
const int maxThreshold = 30 ;
const int timeInterval = 1000;
int len;

void setup()
{
  pinMode(buzzer, OUTPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  len = strlen(message);
  Serial.begin(9600);

}

void loop()
{

  lcd.setCursor(0, 0);
  val = analogRead(sensorPin);

  convertToCelius();

  // output a temperature value per 1 time interval

  if (millis() - tepTimer > timeInterval) {

    tepTimer = millis();

    lcd.clear();

    if (temperature > maxThreshold) {
      digitalWrite(buzzer, HIGH);
      Serial.println("Warning!");
      lcd.print(message);
      for (int i = 0 ; i < len ; i++) {
        delay(350);
        lcd.scrollDisplayLeft();
      }

    } else {
      digitalWrite(buzzer, LOW);
      lcd.print("T: ");
      lcd.print(temperature);
      lcd.print(" C");
    }
  }

}
void convertToCelius() {
  temperature = (float) val * (5 / 10.24);
}

