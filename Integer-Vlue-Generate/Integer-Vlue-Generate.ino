

void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 baud
}

void loop() {
  int random_number = random(1, 21); // Generate a random number between 1 and 20 (inclusive)
  Serial.println(random_number); // Print the random number followed by a newline
  delay(1000); // Delay for 1 second
}
