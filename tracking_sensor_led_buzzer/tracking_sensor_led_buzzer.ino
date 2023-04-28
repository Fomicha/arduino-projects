int ledPin = 13;
int sensor = A0;
int buzzerPin = 8;
int val = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode (buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  val = analogRead(sensor);

  Serial.println(val);

  if (val > 500) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
    digitalWrite (buzzerPin, HIGH);
  }

  delay(3000);
}