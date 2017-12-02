#include <IRremote.h>
#include <Servo.h>

int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;
Servo myservo;
int remoteValue = 0;
bool firstDigit = true;
int angle=0;
const int SERVO_PIN = 9;
const int OK = 10;
const int UP = 11;
const int DOWN = 12;
const long keys[] = {33491191, 33523831, 33507511, 33540151, 33499351, 33531991, 33515671, 33548311, 33495271, 33527911, 33552391, 33505471, 33538111};


int myHouseRemote(long key) {
  int sz = 12;
  for (int i = 0 ; i <= sz ; i++) {
    if (keys[i] == key) {
      return i;
    }
  }
  return -1;
}

int getValue(long key) {
  return myHouseRemote(key);
}
void setupServo() {
  myservo.attach(SERVO_PIN);
  myservo.write(0);
  delay(15);
}
void setupIR()
{
  irrecv.enableIRIn(); // Start the receiver
}
void updateServo() {
  if(angle != myservo.read()){
    myservo.write(angle);
    Serial.print("Value of servo : ");
    Serial.println(myservo.read());
    delay(15);
  }
}
void loopIR() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value);
    int tmp  = getValue(results.value);
    Serial.print("Value Pressed : ");
    Serial.println(tmp);
    if (tmp == OK) {
      if (firstDigit) {
        Serial.println("ok has been pushed with no prev digits");
      } else {
        if (remoteValue < 0) {
          Serial.println("overflow happened, No more digits will be accepted.");
        } else {
          angle = remoteValue;
          Serial.print("Angle has been read from the remote and its value = ");
          Serial.println(angle);
          updateServo();
        }
        firstDigit = true;
        remoteValue = 0;
      }
    } else if (tmp == UP) {
      angle += 10;
      Serial.println("UP button has been pushed");
      updateServo();

    } else if (tmp == DOWN) {
      angle -= 10;
      Serial.println("DOWN button has been pushed");
      updateServo();
    }
    else if (tmp == -1) {
      firstDigit = true;
      remoteValue = 0;
      Serial.println("Error Happened Value hasn't been set");
    } else {
      firstDigit = false;
      remoteValue = 10 * remoteValue + tmp;
      Serial.print("Current Remote Value = ");
      Serial.println(remoteValue);
    }
    delay(300);
    irrecv.resume(); // Receive the next value
  }
}

void setup() {
  Serial.begin(9600);
  setupServo();
  setupIR();
}

void loop() {
  loopIR();
  delay(100);
}

