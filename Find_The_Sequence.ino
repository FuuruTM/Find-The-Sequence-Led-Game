int arr[] = {0, 1, 2, 3, 4, 0, 0, 0, 0, 0};
int led[] = {1, 4, 7, 9, 12};
int btn[] = {0, 3, 6, 8, 11};
int buzz = 2;
int reset = 5;
int counter = 0;

int sequence[100];
int seq[5];

void setup( ) {
  for(int i = 0; i < 5; i++) {
    pinMode(led[i], OUTPUT);
    pinMode(btn[i], INPUT_PULLUP);
    pinMode(buzz, OUTPUT);
    pinMode(reset, INPUT_PULLUP);
  }
  randomSeed(analogRead(A0));
  startSequence( );
  showSequence( );
}

void loop( ) {
  playerTurn( );
  if(digitalRead(reset) == LOW) {
    digitalWrite(4, HIGH);
  }
}

void startSequence( ) {
  for(int i = 0; i < 1; i++) {
    sequence[i] = random(0,5);
    int a = sequence[i];
    seq[0] = arr[a];
    int save = a;
    arr[a] = arr[a+1];
    arr[a+1] = arr[a+2];
    arr[a+2] = arr[a+3];
    arr[a+3] = arr[a+4];
  }
  for(int i = 1; i < 2; i++) {
    sequence[i] = random(0,4);
    int a = sequence[i];
    seq[1] = arr[a];
    int save = a;
    arr[a] = arr[a+1];
    arr[a+1] = arr[a+2];
    arr[a+2] = arr[a+3];
  }
  for(int i = 2; i < 3; i++) {
    sequence[i] = random(0,3);
    int a = sequence[i];
    seq[2] = arr[a];
    int save = a;
    arr[a] = arr[a+1];
    arr[a+1] = arr[a+2];
    arr[a+2] = arr[a+3];
  }
  for(int i = 3; i < 4; i++) {
    sequence[i] = random(0,2);
    int a = sequence[i];
    seq[3] = arr[a];
    int save = a;
    arr[a] = arr[a+1];
    arr[a+1] = arr[a+2];
  }
  for(int i = 4; i < 5; i++) {
    sequence[i] = random(0,1);
    int a = sequence[i];
    seq[4] = arr[a];
    int save = a;
    arr[a] = arr[a+1];
  }
  arr[0] = 0;
  arr[1] = 1;
  arr[2] = 2;
  arr[3] = 3;
  arr[4] = 4;
  arr[5] = 0;
  arr[6] = 0;
  arr[7] = 0;
  arr[8] = 0;
  arr[9] = 0;
}

void showSequence( ) { 
  for(int a = 0; a < 5; a++) {
    int x = seq[a];
    digitalWrite(led[x], HIGH);
    delay(300);
    digitalWrite(led[x], LOW);
    delay(250);
  }
}

void playerTurn( ) {
  for(int i = 0; i < 5; i++) {
    int pressed = waitButton( );
    int check = seq[i];
    digitalWrite(led[pressed], HIGH);
    delay(300);
    digitalWrite(led[pressed], LOW);
    delay(250);
    if(pressed == check) {
      counter++;
    }
  }
  winCheck( );
}

int waitButton( ) {
  while(true) {
    for(int i = 0; i < 5; i++) {
      if(digitalRead(btn[i]) == LOW) {
        delay(200);
        return i;
      }
    }
  }
}

void buzzPlay( ) { 
  for(int i = 0; i < counter; i++) {
    tone(buzz, 700);
    delay(200);
    noTone(buzz);
    delay(200);
  }
  counter = 0;
}

void winCheck( ) {
  if(counter == 5) {
    tone(buzz, 900);
    delay(1000);
    noTone(buzz);
    for(int i = 0; i < 3; i++) {
      for(int i = 0; i < 5; i++) {
        digitalWrite(led[i], HIGH);
      }
      delay(300);
      for(int i = 0; i < 5; i++) {
        digitalWrite(led[i], LOW);
      }
      delay(250);
    }
    counter = 0;
    startSequence( );
    showSequence( );
  } else {
    buzzPlay( );
  }
}