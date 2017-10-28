/*

   ِ simple voltmeter with an alarm to indicate that the voltage has exceeded a
  certain limit
*/
const int referenceVolts = 5;
const int potentiometerPin = A0;
int ledPin = 13;
float maxThrehold = 3.0;
float minThrehold = 2.5;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  int val = analogRead( potentiometerPin);
  float volts = (val / 1023.0) * referenceVolts;
  Serial.println(volts);
  if (volts > maxThrehold) {
    digitalWrite(ledPin,HIGH);
  } else if(volts  < minThrehold){
      digitalWrite(ledPin,LOW);
    }
  

}
