#include <Servo.h>

#define LIGHT1_PIN 7  // Pin for Light 1 (LED 1)
#define LIGHT2_PIN 8  // Pin for Light 2 (LED 2)
#define BUTTON_PIN 2  // Pin for the push button
#define FAN_SERVO_PIN 9  // Pin for the servo motor (Fan)

Servo fanServo;          // Servo object for fan simulation
bool fanRunning = false; // State of the fan (false = OFF, true = ON)
int currentAngle = 90;   // Current angle of the servo
int step = 1;            // Step size for continuous movement

void setup() {
  // Pin modes for LEDs
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);

  // Pin mode for button with internal pull-up
  pinMode(2, INPUT_PULLUP);

  // Attach the servo and set initial position
  fanServo.attach(9);
  fanServo.write(currentAngle); // Start fan at 90° (OFF position)

  // Turn off LEDs initially
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
}

void loop() {
  static bool buttonPressed = false;

  // Check if the button is pressed and toggle the fan state
  if (digitalRead(2) == LOW && !buttonPressed) {
    fanRunning = !fanRunning; // Toggle fan and lights state
    buttonPressed = true;

    // Toggle lights
    if (fanRunning) {
      digitalWrite(7, HIGH); // Turn Light 1 ON
      digitalWrite(8, HIGH); // Turn Light 2 ON
    } else {
      digitalWrite(LIGHT1_PIN, LOW);  // Turn Light 1 OFF
      digitalWrite(LIGHT2_PIN, LOW);  // Turn Light 2 OFF
      fanServo.write(90);            // Reset fan to 90° (OFF position)
    }
    delay(200); // Debounce delay
  } else if (digitalRead(BUTTON_PIN) == HIGH) {
    buttonPressed = false;
  }

  // Move the servo continuously if the fan is ON
  if (fanRunning) {
    currentAngle += step;

    // Reverse direction when reaching bounds
    if (currentAngle >= 180 || currentAngle <= 90) {
      step = -step;
    }

    fanServo.write(currentAngle);
    delay(10); // Delay for smooth movement
  }
}
