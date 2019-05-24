#define PPTV 2        // pieton parallele au train vert
#define PTV 3         // pieton perpendiculaires au train vert
#define PPTR 4        // pieton parallele au train rouge
#define PTR 5         // pieton perpendiculaires au train rouge

#define VPTV 6        // voiture parallele au train vert
#define VTV 7         // voiture perpen au train vert
#define VPTR 8        // voiture parallele au train rouge
#define VTR 9         // voiture perpen au train rouge


#define LEDTRAIN 10   // Train
#define BUTTONT 11    // Bouton du train
#define BUTTONP 12    // Bouton des piétons 

#define TIMEOFF 2000
#define TIMEON 10000
#define TIMETRAIN 2000


//#define PROBATRAIN 1000000 // at any time the proba of arrival of a train is 1/PROBATRAIN


bool PRESSEDBUTTON = false;
int buttonState = 0;
long randomVal = 256;


void setup() {
  pinMode(PPTV, OUTPUT);
  pinMode(PTV, OUTPUT);
  pinMode(PPTR, OUTPUT);
  pinMode(PTR, OUTPUT);
  pinMode(VPTV, OUTPUT);
  pinMode(VTV, OUTPUT);
  pinMode(VPTR, OUTPUT);
  pinMode(VTR, OUTPUT);
  
  pinMode(LEDTRAIN, OUTPUT);
  pinMode(BUTTONP, INPUT);
  digitalWrite(PPTR,HIGH);
  digitalWrite(PTR,HIGH);
  
}

void loop(){
  switchOn(VPTR,VTR,VPTV,VTV);
  off1();
  switchOn(VTR,VPTR,VTV,VPTV);
  off2();
}


void off2(){
  
  for(int i = 0; i< TIMEOFF; ++i){
    delay(1);
    digitalWrite(PPTR,HIGH);
    digitalWrite(PTR,HIGH);
    digitalWrite(VPTR,HIGH);
    digitalWrite(VTR,HIGH);
    
    checkButtonP();
    if (checkButtonT()){
        trainTravel();
        i=0;   
    }
  }
  if(PRESSEDBUTTON){
    off3();
  }
}

void off1(){
  for(int i = 0; i< TIMEOFF; ++i){
    delay(1);
    digitalWrite(PPTR,HIGH);
    digitalWrite(PTR,HIGH);
    digitalWrite(VPTR,HIGH);
    digitalWrite(VTR,HIGH);
    
    checkButtonP();
    if (checkButtonT()){
        trainTravel();
        i=0;
    }
  }
  digitalWrite(VPTR,LOW);
  digitalWrite(VTR,LOW);
}

void off3(){
  digitalWrite(PPTR,LOW);
  digitalWrite(PTR,LOW);
  digitalWrite(PPTV,HIGH);
  digitalWrite(PTV,HIGH);
  digitalWrite(VPTR,HIGH);
  digitalWrite(VTR,HIGH);
  
  for(int i = 0; i< 5000; ++i){
    delay(1);
    if (checkButtonT()){
        trainTravel();
        i=0;
        digitalWrite(PPTV,HIGH);
        digitalWrite(PTV,HIGH);
        digitalWrite(PPTR,LOW);
        digitalWrite(PTR,LOW);
    }
  }
  PRESSEDBUTTON = false;
  digitalWrite(PPTV,LOW);
  digitalWrite(PTV,LOW);
  digitalWrite(PPTR,HIGH);
  digitalWrite(PTR,HIGH);
  
}


void switchOn(int vptr, int vtr, int vptv, int vtv){
  digitalWrite(vptr,HIGH);
  digitalWrite(vtr,LOW);
  digitalWrite(vptv,LOW);
  digitalWrite(vtv,HIGH);
  
  for(int i = 0; i< TIMEON; ++i){
    delay(1);
    checkButtonP();
    
    if (checkButtonT()){
        trainTravel();
        i=0;
        digitalWrite(vtv,HIGH);
        digitalWrite(vtr,LOW);
     }
  }
  digitalWrite(vtv,LOW);
  digitalWrite(vptr,LOW);
  
}

/*bool trainRandom(){
  randomVal = random(0,PROBATRAIN);
  return randomVal == 0;
}*/


void checkButtonP(){
  buttonState = digitalRead(BUTTONP);
  if(buttonState == HIGH){
    PRESSEDBUTTON = true;
  }  
}

bool checkButtonT(){
  buttonState = digitalRead(BUTTONT);
  return buttonState == HIGH;
}


void trainTravel(){
  digitalWrite(PPTR,HIGH);
  digitalWrite(PTR,HIGH);
  digitalWrite(VPTR,HIGH);
  digitalWrite(VTR,HIGH);

  digitalWrite(PPTV,LOW);
  digitalWrite(PTV,LOW);
  digitalWrite(VPTV,LOW);
  digitalWrite(VTV,LOW);

  for(int i = 0; i<TIMETRAIN/200; ++i){
      digitalWrite(LEDTRAIN,LOW);
      for(int j=0; j<100; j++){
        delay(1);
        checkButtonP();
      }
      digitalWrite(LEDTRAIN,HIGH);
      for(int k=0; k<100; k++){
        delay(1);
        checkButtonP();
      }
  }
  for(int i = 0; i<TIMETRAIN; ++i){
    delay(1);
    checkButtonP();  
  }
  digitalWrite(LEDTRAIN,LOW);
}
