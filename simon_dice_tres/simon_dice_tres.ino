int whiteState = 0;
int redState = 0;
int blueState = 0;
int whiteLed = 11;
int redLed = 12;
int blueLed = 13;
int currentLevel = 1;
int speed = 500;
const int LEVEL_MAX = 10;
int sequence[LEVEL_MAX];
int sequenceGamer[LEVEL_MAX];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(whiteLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  digitalWrite(whiteLed, LOW);
  digitalWrite(redLed, LOW);
  digitalWrite(blueLed, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(currentLevel == 1){
    createSequence();
    showSequence();
    readSequence();
  }
  if(currentLevel != 1){
    showSequence();
    readSequence();
  }
}

void readSequence(){
   int flag = 0;
   for(int i = 0; i < currentLevel; i++){
      flag = 0;
      while(flag == 0){

    whiteState = digitalRead(2);
      if (whiteState == HIGH) {
        digitalWrite(whiteLed, HIGH);
      } else {
        digitalWrite(whiteLed, LOW);
      }
      redState = digitalRead(3);
      if (redState == HIGH) {
        digitalWrite(redLed, HIGH);
      } else {
        digitalWrite(redLed, LOW);
      }
      blueState = digitalRead(4);
      if (blueState == HIGH) {
        digitalWrite(blueLed, HIGH);
      } else {
        digitalWrite(blueLed, LOW);
      }
      if(digitalRead(blueLed) == HIGH){
        digitalWrite(blueLed, HIGH);
        Serial.println("Azuuuuul");
        sequenceGamer[i] = blueLed;
        flag = 1;
        delay(200);
        if(sequenceGamer[i] != sequence[i]){
          sequenceError();
          return;
        }
        digitalWrite(blueLed, LOW);
      }
      if(digitalRead(redLed) == HIGH){
        digitalWrite(redLed, HIGH);
        sequenceGamer[i] = redLed;
        flag = 1;
        delay(200);
        if(sequenceGamer[i] != sequence[i]){
          sequenceError();
          return;
        }
        digitalWrite(redLed, LOW);
      }
      if(digitalRead(whiteLed) == HIGH){
        digitalWrite(whiteLed, HIGH);
        sequenceGamer[i] = whiteLed;
        flag = 1;
        delay(200);
        if(sequenceGamer[i] != sequence[i]){
          sequenceError();
          return;
        }
        digitalWrite(whiteLed, LOW);
      }
    }
  }
  sequenceCorrect();
}

void showSequence(){
   digitalWrite(whiteLed, LOW);
   digitalWrite(redLed, LOW);
   digitalWrite(blueLed, LOW);
   for(int i = 0; i < currentLevel; i++){
      digitalWrite(sequence[i], HIGH);
      delay(speed);
      digitalWrite(sequence[i], LOW);
      delay(200);
   }
}

void createSequence(){
   randomSeed(millis());
   for(int i = 0; i < LEVEL_MAX; i++){
      sequence[i] = random(11,14);
   }
}

void sequenceError(){
   digitalWrite(whiteLed, HIGH);
   digitalWrite(redLed, HIGH);
   digitalWrite(blueLed, HIGH);
   delay(250);
   digitalWrite(whiteLed, LOW);
   digitalWrite(redLed, LOW);
   digitalWrite(blueLed, LOW);
   delay(250);
   currentLevel = 1;
   speed = 500;
}

void sequenceCorrect(){
   if(currentLevel < LEVEL_MAX)
      currentLevel++;
   speed -= 50;
   delay(200);
}
