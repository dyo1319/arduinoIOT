#define btnPin D5
#define redPin D1
#define greenPin D2
#define bluePin D3

int lastVal;
unsigned long lastPressTime;
unsigned long pressStartTime = 0;
unsigned long pressDuration = 0;


const int MAX_PRESS_DURATIONS = 10;
unsigned long pressDurations[MAX_PRESS_DURATIONS] = {0};
int pressIndex = 0;
int numPresses = 0; 

void btn_setup(){
  Serial.begin(9600);
  pinMode(btnPin, INPUT_PULLUP);

  lastPressTime = millis();
  lastVal = digitalRead(btnPin);
  wifiClient_Setup();
}

void btn_loop() {
  int val = digitalRead(btnPin);

  if((val == LOW) && (lastVal == HIGH) && (millis() - lastPressTime > 50)) {
    lastPressTime = millis();
    pressStartTime = lastPressTime; 
  }

  measurePressDuration(val);
  lastVal = val;
}

void measurePressDuration(int btnCurrVal) {
  if (btnCurrVal == LOW) {
    if (pressStartTime != 0) {
      pressDuration = millis() - pressStartTime;
    }
  } else {
    if (pressStartTime != 0) {
      pressDuration = millis() - pressStartTime;
      Serial.print("Press duration: ");
      Serial.print(pressDuration);
      Serial.println(" milliseconds");
      pressStartTime = 0;

      if (numPresses < MAX_PRESS_DURATIONS) {
        pressDurations[numPresses] = pressDuration;
        numPresses++;
      } else {
        pressDurations[pressIndex] = pressDuration;
        pressIndex = (pressIndex + 1) % MAX_PRESS_DURATIONS;
      } 

      long currentDuration = readCurrentDurationFromServer();
      if (pressDuration < currentDuration || currentDuration == 0) {
        SendBtnPressed();
        lightTurquoise();
      } else {
        lightOrange();
      }
    }
  }
}

void setRGBColor(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

void lightTurquoise() {
  setRGBColor(0, 255, 255); 
}

void lightOrange() {
  setRGBColor(255, 165, 0); 
}

int getNumPresses() {
  return numPresses;
}

unsigned long* getPressDurations() {
  return pressDurations;
}
