#define btnPin D5

int lastVal;
unsigned long lastPressTime;
unsigned long pressStartTime = 0;
unsigned long pressDuration = 0;

void setup() {
  Serial.begin(9600);
  pinMode(btnPin, INPUT_PULLUP);

  lastPressTime = millis();
  lastVal = digitalRead(btnPin);
  wifiClient_Setup();
}

void loop() {
  int val = digitalRead(btnPin);

  if((val == LOW) && (lastVal == HIGH) && (millis() - lastPressTime > 50)){
    lastPressTime = millis();
    Serial.println(lastPressTime);
  }
  measurePressDuration(val);
  lastVal = val;
}

void measurePressDuration(int btnCurrVal) {
  if (btnCurrVal == LOW) {
    if (pressStartTime == 0) {
      pressStartTime = millis();
    }
  } else {
    if (pressStartTime != 0) {
      pressDuration = millis() - pressStartTime;
      Serial.print("Press duration: ");
      Serial.print(pressDuration);
      Serial.println(" milliseconds");
      pressStartTime = 0;
    }
  }
}
