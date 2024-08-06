#define SETTING_PIN D6
bool IhaveLed;

void setup() {
  Serial.begin(9600);
  pinMode(SETTING_PIN,INPUT_PULLUP);
  IhaveLed = (digitalRead(SETTING_PIN) == LOW) ? true:false;

  if(IhaveLed){
   WifiSetup();
  } else {
    btn_setup();
  }
}
void loop() {
  if (digitalRead(SETTING_PIN) == LOW) {
    if (!IhaveLed) {
      WifiSetup();
      IhaveLed = true;
    }
    wifi_loop(); 
  } else {
    btn_loop();
  }
}
