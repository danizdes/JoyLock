// Declerations
const int joystickXPin = A0;
const int joystickYPin = A1;
const int joystickButtonPin = 6;

const int led1 = 8;
const int led2 = 9;
const int led3 = 10;
const int led4 = 11 ;

int index = 0;
int pattern[4];
int patternIndex = 0;

int correctPattern[4] = {3, 0, 1, 2};

bool match = false;
bool sound_played = false;

int compareArrays(int array1[], int array2[], int length) {
  for (int i = 0; i < length; i++) {
    if (array1[i] != array2[i]) {
      return 0; // Arrays are different
    }
  }
  return 1; // Arrays are the same
}

void playMoveSound() {
  tone(5, 1200);
  delay(80); 
  noTone(5);
}

void playCorrectSound() {
  int notes[] = {262, 330, 392, 523};
  for (int i = 0; i < 4; i++) {
    tone(5, notes[i]);
    delay(100);
  }
  noTone(5);
}

void setup() {
  Serial.begin(9600);

  pinMode(joystickButtonPin, INPUT_PULLUP);

  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);

  pinMode(5, OUTPUT);

  digitalWrite(led1, HIGH);
  
}

void loop() {

  if (match == true){
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);

    delay (200);

    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);

    playCorrectSound();
  }

  else {
  int xValue = analogRead(joystickXPin);
  int yValue = analogRead(joystickYPin);
  int buttonState = digitalRead(joystickButtonPin);



    if (xValue < 100){
      if (index != 0) {
        digitalWrite((8+index), LOW);
        index--;
        digitalWrite((8+index), HIGH);
        Serial.println(index);
        playMoveSound();
      }
  } else if (xValue > 900) {
      if (index < 4) {
        digitalWrite((8+index), LOW);
        index++;
        digitalWrite((8+index), HIGH);
        Serial.println(index);
        playMoveSound();
      }
  }

    if (buttonState == LOW) {
    if (patternIndex < 4) {
      pattern[patternIndex] = index;
      patternIndex++;
      playMoveSound();
    }
  }
  
  if (index == 2){
    if (compareArrays(pattern, correctPattern, 4) == 1) {
      match = true;

  }
  }

  }
  delay(200);

}
