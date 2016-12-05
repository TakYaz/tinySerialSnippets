
int value = 0; // the number got from serial port messages
int isReading = 0; // flag of reading number

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
}

// the loop function runs over and over again forever
void loop() {
  int finished = isReading;
  getIntFromSerial();
  finished -= isReading;
  if(value != 0 && finished){
    Serial.println(value);
  }
}

void getIntFromSerial(){
  if(Serial.available()){
    char ch = Serial.read(); // read a byte, in another words, read a character.
    if(ch == 'H'){
      isReading = 1;
      value = 0;
      return;
    }
    int num_ch = ch - '0';
    if(num_ch >= 0 && num_ch <= 9 && isReading){
      value = value * 10 + num_ch;
    }else{
      isReading = 0;
    }
  }
  return;
}

// sample functions
void funcOne(){
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
}

void funcTwo(){
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
}

void funcThree(){
  digitalWrite(LED_BUILTIN, HIGH);
  delay(250);
  digitalWrite(LED_BUILTIN, LOW);
  delay(250);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(250);
  digitalWrite(LED_BUILTIN, LOW);
  delay(250);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(250);
  digitalWrite(LED_BUILTIN, LOW);
  delay(250);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(250);
  digitalWrite(LED_BUILTIN, LOW);
}
