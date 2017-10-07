/*
  Morse sketch

  Direct port I/O used to send AM radio carrier at 1MHz
*/
const int sendPin = 13;
const byte dot = 1;
const byte gap = 1;
const byte dash = 3;
const byte letterGap = 3;
const byte wordGap = 7;
const int unit_time = 100;
byte letter = 0; // the letter to send
char prev;
bool first;
char* getCode(char key)
{
  switch (key) {
    case 'A':
    case 'a':
      return ".-";
    case 'B':
    case 'b':
      return "-...";
    case 'C':
    case 'c':
      return "-.-.";
    case 'D':
    case 'd':
      return "-..";
    case 'E':
    case 'e':
      return ".";
    case 'F':
    case 'f':
      return "..-.";
    case 'G':
    case 'g':
      return "--.";
    case 'H':
    case 'h':
      return "....";
    case 'I':
    case 'i':
      return "..";
    case 'J':
    case 'j':
      return ".---";
    case 'K':
    case 'k':
      return "-.-";
    case 'L':
    case 'l':
      return ".-..";
    case 'M':
    case 'm':
      return "--";
    case 'N':
    case 'n':
      return "-.";
    case 'O':
    case 'o':
      return "---";
    case 'P':
    case 'p':
      return ".--.";
    case 'Q':
    case 'q':
      return "--.-";
    case 'R':
    case 'r':
      return ".-.";
    case 'S':
    case 's':
      return "...";
    case 'T':
    case 't':
      return "-";
    case 'U':
    case 'u':
      return "..-";
    case 'V':
    case 'v':
      return "...-";
    case 'W':
    case 'w':
      return ".--";
    case 'X':
    case 'x':
      return "-..-";
    case 'Y':
    case 'y':
      return "-.--";
    case 'Z':
    case 'z':
      return "--..";
    case '0':
      return "-----";
    case '1':
      return ".----";
    case '2':
      return "..---";
    case '3':
      return "...--";
    case '4':
      return "....-";
    case '5':
      return ".....";
    case '6':
      return "-....";
    case '7':
      return "--...";
    case '8':
      return "---..";
    case '9':
      return "----.";
    default:
      return " ";
  }
  return 0;

}
void setup()
{
  prev = '-';
  first = true;
  pinMode(sendPin, OUTPUT);
  Serial.begin(9600);
}
void loop()
{

  if ( Serial.available())
  {
    char ch = Serial.read();
    if (prev == ' ' && ch != '\n' && ch != ' ') {
      sendWordGap();
      first = true;
    }
    //Serial.println(getCode(ch));
    sendMorse(getCode(ch));
    prev = ch;
  }else{
    digitalWrite(sendPin,LOW);
  }
}
void sendMorse(char* str)
{
  if (!first && strcmp(str," ")){
    spendLetterGap();
  }
  first=false;
  letter = 0 ;
  while (str[letter] != 0)
  {
    if (letter){
      spendInterElementGap();
    }
    if (str[letter] == '.')
    {
      sendDot();
    }
    else if (str[letter] == '-')
    {
      sendDash();
    }
    letter = letter + 1;
  }
}

void spendInterElementGap(){
    sendGap(unit_time);
}
void sendDot()
{
  morseTime( dot * unit_time);
}


void sendDash()
{
  morseTime( dash * unit_time);
}

void sendGap(int ms)
{
//  Serial.print("off-->");
//  Serial.println(ms);
  digitalWrite(sendPin, LOW);
  delay(ms);
}
void spendLetterGap() {
  sendGap(letterGap * unit_time);
}
void sendWordGap()
{
  sendGap(wordGap * unit_time);
}
void morseTime(int ms) {
//  Serial.print("on-->");
//  Serial.println(ms);
  digitalWrite(sendPin, HIGH);
  delay(ms);                       
}
