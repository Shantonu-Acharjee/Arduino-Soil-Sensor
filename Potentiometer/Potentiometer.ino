const int vcc = A8;  
const int gnd = A12;  
const int POTENTIOMETER_PIN = A10;  

void setup() {
  Serial.begin(9600);
  pinMode(POTENTIOMETER_PIN, INPUT);

  // Create versual VCC AND GND
  pinMode(vcc, OUTPUT);  
  pinMode(gnd, OUTPUT); 
  digitalWrite(vcc, HIGH);  
  digitalWrite(gnd, LOW);
}

void loop() {
  Serial.println(analogRead(POTENTIOMETER_PIN));
  delay(200);
}

