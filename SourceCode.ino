#include <Servo.h>

Servo servo; // Create a servo object

const int trigPin = 9; // Ultrasonic Trig pin

const int echoPin = 10; // Ultrasonic Echo pin

bool lidOpen = false; // Track whether the lid is open

unsigned long openTime = 0; // Store the time when the lid opened bool objectStillDetected = false; // Track if the object is still present

void setup() {

servo.attach(11); // Servo motor pin

} pinMode(trigPin, OUTPUT); pinMode(echoPin, INPUT); servo.write(90); // Initial position of the lid (closed - 90°) Serial.begin(9600);

void loop() {

long duration, distance;

// Measure distance

digitalWrite(trigPin, LOW);

delayMicroseconds(2);

digitalWrite(trigPin, HIGH);

delayMicroseconds(10);

digitalWrite(trigPin, LOW);

23

duration = pulseln (echoPin, HIGH);

distance = duration 0.034/2; // Convert to centimeters

Serial.print("Distance: "); Serial.println(distance);

// Open the lid if an object is detected within 20 cm, and the lid is not already open

if (distance > 0 && distance < 20 && !lidOpen) { } openLid(); // Open the lid lidOpen = true; openTime = millis(); // Record the time the lid opened

// Check if the lid has been open for 10 seconds

if (lidOpen && millis() - openTime >= 5000) { } closeLid(); // Close the lid lidOpen = false; objectStill Detected = true; // Wait for the object to move away

// Wait for the object to move away before resetting if (objectStillDetected && (distance >= 20 || distance == 0)) { } objectStillDetected = false; // Reset the system Serial.println("Object moved away. System reset.");

24

} delay(200); // Delay to avoid rapid triggering

void openLid() {

for (int angle = 90; angle >= 0; angle -= 2) { // Move from 90° to 0° in

steps of 2°

servo.write(angle);

delay(15); // Small delay to make the movement smooth

}

Serial.println("Lid opened");

}

void closeLid() {

for (int angle = 0; angle <= 90; angle += 2) { // Move from 0° to 90° in

steps of 2°

servo.write(angle);

delay(15); // Small delay to make the movement smooth

}

Serial.println("Lid closed");

}
