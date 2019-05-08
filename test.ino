#define LEDAG 3 // Groupe of A.g
#define LEDBG 6 // Groupe of B.g
#define LEDAR 2 // Groupe of A.r
#define LEDBR 5 // Groupe of B.r
#define LEDEG 8 // Groupe of E.g
#define LEDER 7 // Groupe of E.r
#define LEDTRAIN 9 // Groupe of the train
#define BUTTON1 11
#define BUTTON2 12
#define TIMEOFF 2000
#define TIMEON 10000
#define TIMETRAIN 2000
#define PROBATRAIN 30000 // at any time the proba of arrival of a train is 1/PROBATRAIN

int buttonState = 0;
long randomVal = 256;

void trainTravel(int on1, int on2 , int on3, int on4){
  digitalWrite(LEDAG,LOW);
  digitalWrite(LEDBG,LOW);
  digitalWrite(LEDER,LOW);
  digitalWrite(LEDAR,HIGH);
  digitalWrite(LEDBR,HIGH);
  digitalWrite(LEDEG,HIGH);
  digitalWrite(LEDTRAIN,HIGH);
  delay(TIMETRAIN);
  digitalWrite(LEDAR,LOW);
  digitalWrite(LEDBR,LOW);
  digitalWrite(LEDEG,LOW);
  digitalWrite(LEDTRAIN,LOW);
  
  //reset
  digitalWrite(on1,HIGH);
  digitalWrite(on2,HIGH);
  digitalWrite(on3,HIGH);
  digitalWrite(on4,HIGH);
  
}

bool trainRandom(){
  randomVal = random(0,PROBATRAIN);
  return randomVal == 0;
}

void waitAllRed() {
  digitalWrite(LEDAR,HIGH);
  digitalWrite(LEDBR,HIGH);
  digitalWrite(LEDER,HIGH);

  for(int i = 0; i<TIMEOFF; i++){
      delay(1);
      if (trainRandom()){
        trainTravel(LEDAR,LEDER,LEDBR, LEDBR);
        i = 0;
      }
  }
}

void switchOn(int g1, int g2, int r1, int r2, int button) {
  digitalWrite(g2-1, LOW);
  digitalWrite(g1-1, LOW);
  digitalWrite(g1, HIGH);
  digitalWrite(g2, HIGH);
  
  for(int i = 0; i<TIMEON; ++i){
      delay(1);
      if (trainRandom()){
        trainTravel(g1,g2,r1,r2);
        i = 0;
      }
      buttonState = digitalRead(button);
      
      if (buttonState == HIGH) {
        int rest= TIMEON-i-4000;
        if (rest < 0){rest = 0;}
        for (int j = 0; i < rest; ++i){
          delay(1);
          if (trainRandom()){
            trainTravel(g1,g2,r1, r2);
            j = 0;
            rest=TIMEON-4000;
          }
        }
        break;
      }
  }
  digitalWrite(g1, LOW);
  digitalWrite(g2, LOW);
  
}

void setup() {
  pinMode(LEDAG, OUTPUT);
  pinMode(LEDAR, OUTPUT);
  pinMode(LEDBG, OUTPUT);
  pinMode(LEDBR, OUTPUT);
  pinMode(LEDEG, OUTPUT);
  pinMode(LEDER, OUTPUT);
  pinMode(LEDTRAIN, OUTPUT);
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  
}

void loop() {
  waitAllRed();
  switchOn(LEDAG, LEDAG, LEDBR, LEDER, BUTTON1);
  waitAllRed();
  switchOn(LEDBG, LEDEG, LEDAR, LEDAR, BUTTON2);
}
