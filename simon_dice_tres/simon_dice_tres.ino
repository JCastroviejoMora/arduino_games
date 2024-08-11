int whiteState = 0;
int redState = 0;
int blueState = 0;
int whiteLed = 11;
int redLed = 12;
int blueLed = 13;
int nivelActual = 1;
int velocidad = 500;
const int NIVEL_MAX = 10;
int secuencia[NIVEL_MAX];
int secuenciaUsuario[NIVEL_MAX];

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
  if(nivelActual == 1){
    Serial.println("Primer nivel: genera secuencia");
    generaSecuencia();
    Serial.println("Primer nivel: muestra secuencia");
    muestraSecuencia();
    Serial.println("Primer nivel: lee secuencia");
    leeSecuencia();
  }
  if(nivelActual != 1){
    muestraSecuencia();
    leeSecuencia();
  }


/*
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
  }*/
}

void leeSecuencia(){
   int flag = 0;
   for(int i = 0; i < nivelActual; i++){
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
            secuenciaUsuario[i] = blueLed;
            flag = 1;
            delay(200);
            if(secuenciaUsuario[i] != secuencia[i]){
               secuenciaError();
               return;
            }
            digitalWrite(blueLed, LOW);
         }
         if(digitalRead(redLed) == HIGH){
            digitalWrite(redLed, HIGH);
            secuenciaUsuario[i] = redLed;
            flag = 1;
            delay(200);
            if(secuenciaUsuario[i] != secuencia[i]){
               secuenciaError();
               return;
            }
            digitalWrite(redLed, LOW);
         }
         if(digitalRead(whiteLed) == HIGH){
            digitalWrite(whiteLed, HIGH);
            secuenciaUsuario[i] = whiteLed;
            flag = 1;
            delay(200);
            if(secuenciaUsuario[i] != secuencia[i]){
               secuenciaError();
               return;
            }
            digitalWrite(whiteLed, LOW);
         }
      }
   }
   secuenciaCorrecta();
}

void muestraSecuencia(){
   digitalWrite(whiteLed, LOW);
   digitalWrite(redLed, LOW);
   digitalWrite(blueLed, LOW);
   for(int i = 0; i < nivelActual; i++){
      digitalWrite(secuencia[i], HIGH);
      delay(velocidad);
      digitalWrite(secuencia[i], LOW);
      delay(200);
   }
}

void generaSecuencia(){
   randomSeed(millis());
   for(int i = 0; i < NIVEL_MAX; i++){
      secuencia[i] = random(11,14);
   }
}

void secuenciaError(){
   digitalWrite(whiteLed, HIGH);
   digitalWrite(redLed, HIGH);
   digitalWrite(blueLed, HIGH);
   delay(250);
   digitalWrite(whiteLed, LOW);
   digitalWrite(redLed, LOW);
   digitalWrite(blueLed, LOW);
   delay(250);
   nivelActual = 1;
   velocidad = 500;
}

void secuenciaCorrecta(){
   if(nivelActual < NIVEL_MAX)
      nivelActual++;
   velocidad -= 50;
   delay(200);
}
