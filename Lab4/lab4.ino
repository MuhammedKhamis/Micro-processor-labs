#include <IRremote.h>

int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;
const int referenceVolts = 5000;
const int sensorPin = A0;
int ledPin = 13;
const float defaultMaxThreshold = 40.0;
float maxThrehold = 40.0;
int remoteValue = 0;
bool firstDigit = true;
const long keys[] = {33491191, 33523831, 33507511, 33540151, 33499351, 33531991, 33515671, 33548311, 33495271, 33527911, 33552391};


int myHouseRemote(long key) {
  for (int i = 0 ; i <= 10 ; i++) {
    if (keys[i] == key) {
      return i;
    }
  }
  return -1;
}

int getValue(long key) {
  return myHouseRemote(key);
}

void setupIR()
{
  irrecv.enableIRIn(); // Start the receiver
}

void loopIR() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value);
    int tmp  = getValue(results.value);
    Serial.print("Value Pressed : ");
    Serial.println(tmp);
    if (tmp == 10) {
      if (firstDigit) {
        maxThrehold = defaultMaxThreshold;
        printmaxThrehold();
      } else {
        if (remoteValue < 0) {
          Serial.println("overflow happened, The maxThreshold will return to be the default one");
          maxThrehold = defaultMaxThreshold;
        } else {
          maxThrehold = (float)remoteValue;
        }
        firstDigit = true;
        remoteValue = 0;
        printmaxThrehold();
      }
    } else if (tmp == -1) {
      firstDigit = true;
      remoteValue = 0;
      Serial.println("Error Happened Value hasn't been set");
    } else {
      firstDigit = false;
      remoteValue = 10 * remoteValue + tmp;
    }
    delay(300);
    irrecv.resume(); // Receive the next value
  }
}
void setupTemperature() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);

}
void loopTemperature() {
  // put your main code here, to run repeatedly:
  int val = analogRead(sensorPin);
  Serial.print(val);
  Serial.print(" > ");
  float millivolts = (val / 1024.0) * referenceVolts;
  float celsius = millivolts / 10;
  Serial.print(celsius);
  Serial.print(" degrees Celsius, ");
  Serial.print((celsius * 9) / 5 + 32);
  Serial.println(" degrees Fahrenheit");
  if (celsius > maxThrehold) {
    digitalWrite(ledPin, HIGH);
  } else if (celsius  < maxThrehold) {
    digitalWrite(ledPin, LOW);
  }
  delay(200);
}

void printmaxThrehold() {
  Serial.print("new Value of maxThrehold : ");
  Serial.println(maxThrehold);
  digitalWrite(ledPin, LOW);
}
void setup() {
  Serial.begin(9600);
  setupIR();
  setupTemperature();
}

void loop() {
  loopIR();
  loopTemperature();
}

