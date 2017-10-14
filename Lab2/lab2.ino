const int button = 2;
const int green = 9;
const int red = 10;
const int debounceDelay = 50;
int turn = 0;
unsigned long counter = 0;

bool debounce(int pin) {
  bool prevState , state;
  prevState = digitalRead(pin);
  for(int i = 0 ; i < debounceDelay;i++){
    delay(1);
    state = digitalRead(pin);
    if(state != prevState){
      i=0;
      prevState=state;
    }
    counter++;
  }
  return state;
}

void setup(){
  pinMode(button,INPUT);
  pinMode(green,OUTPUT);
  pinMode(red,OUTPUT);
  flip();
}

int old_state;
void loop() {
    int curr = debounce(button);
    if(curr && !old_state){
      flip();
    }else{
       delay(1);
    if(counter <= 2000) {
      counter++;
    } else {
    flip();
    }
  }
  old_state = curr;
}
void flip() {
  counter = 0;
  turn = !turn;
  digitalWrite(green,turn);
  digitalWrite(red,!turn);
}

