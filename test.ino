#define LEDAG 2 // Groupe of A.g
#define LEDBG 3 // Groupe of B.g
#define LEDAR 4 // Groupe of A.r
#define LEDBR 5 // Groupe of B.r
#define BUTTON1 11
#define BUTTON2 12
#define TIMEOFF 1000
#define TIMEON 5000

int buttonState = 0;

void waitAllRed() {
  delay(TIMEOFF);
}

void switchOn(int greens, int reds, int button) {
  digitalWrite(reds, LOW);
  digitalWrite(greens, HIGH);
  for(int i = 0; i<TIMEON; i++){
      delay(1);
      buttonState = digitalRead(button);
      if (buttonState == HIGH) {
        int rest= TIMEON-i-2000;
        if (rest < 0){rest = 0;}
        delay(rest);
        break;
      }
  }
  digitalWrite(greens, LOW);
  digitalWrite(reds, HIGH);
}

void setup() {
  pinMode(LEDAG, OUTPUT);
  pinMode(LEDAR, OUTPUT);
  pinMode(LEDBG, OUTPUT);
  pinMode(LEDBR, OUTPUT);
  
  digitalWrite(LEDAR, HIGH);
  digitalWrite(LEDBR, HIGH);
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  
}

void loop() {
  waitAllRed();
  switchOn(LEDAG, LEDAR, BUTTON1);
  waitAllRed();
  switchOn(LEDBG, LEDBR, BUTTON2);
}
