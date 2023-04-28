int laserPin = 13;
void setup() {                
	pinMode(laserPin, OUTPUT);  // Define the digital output interface pin 13 
}
void loop() {
	digitalWrite(laserPin, HIGH); // Turn on the laser head
	delay(1000); // wait for one second
	// digitalWrite(laserPin, LOW); // Turn off the laser head
	// delay(1000); 
}