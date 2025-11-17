// Narrow sweep: 880 Hz -> 1000 Hz, 1 Hz step, 2s each
const int PULSE_PIN   = 9;
const int PULSE_PIN_2 = 3;
const int LED_PIN     = 13;

void setup() {
  pinMode(PULSE_PIN, OUTPUT);
  pinMode(PULSE_PIN_2, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(PULSE_PIN, HIGH);
  digitalWrite(PULSE_PIN_2, HIGH);
  digitalWrite(LED_PIN, HIGH);
  Serial.begin(115200);
  delay(10000); // give time for gauge power sweep to finish
}

void loop() {
  for (int hz = 880; hz <= 1000; hz += 1) {
    unsigned long periodMicros = 1000000UL / (unsigned long)hz;
    unsigned long lowTime = periodMicros / 10;          // 10% low pulse
    unsigned long highTime = periodMicros - lowTime;
    unsigned long testDuration = 2000UL * 1000UL;      // 2 seconds in microseconds
    unsigned long start = micros();

    Serial.print("Test ");
    Serial.print(hz);
    Serial.println(" Hz");

    while (micros() - start < testDuration) {
      digitalWrite(PULSE_PIN, HIGH);  // MOSFET ON -> pulse LOW
      digitalWrite(PULSE_PIN_2, HIGH);
      digitalWrite(LED_PIN, HIGH);
      delayMicroseconds(lowTime);

      digitalWrite(PULSE_PIN, LOW);   // MOSFET OFF -> pulse HIGH (via pull-up)
      digitalWrite(PULSE_PIN_2, LOW);
      digitalWrite(LED_PIN, LOW);
      delayMicroseconds(highTime);
    }
    delay(200); // tiny pause between steps
  }

  Serial.println("Narrow sweep done.");
  while(true) { digitalWrite(LED_PIN, HIGH); delay(500); digitalWrite(LED_PIN, LOW); delay(500); }
}
