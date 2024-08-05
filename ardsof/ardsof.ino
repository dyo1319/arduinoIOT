#define SETTING_PIN D6
//Connect pin D6 to ground to Led Work  Leave pin D6 floating or connect it to 5V to Btn work;
bool IhaveLed;
void setup() {
  Serial.begin(9600);
  pinMode(SETTING_PIN,INPUT_PULLUP);
  IhaveLed = (digitalRead(SETTING_PIN) == LOW) ? true:false;

  if(IhaveLed){
   // LED_setup();
  } else {
    btn_setup();
  }
}
void loop() {
  if(IhaveLed){
    //LED_loop();
  } else {
    btn_loop();
  }
}
