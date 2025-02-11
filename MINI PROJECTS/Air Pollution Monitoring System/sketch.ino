#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define Pin Assignments
#define AIR_SENSOR_PIN A0  // Analog pin for Air Quality Sensor (use potentiometer for simulation)
#define BUZZER_PIN 8  // Pin for the Buzzer
#define LIGHT_PIN 9  // Pin for Light (LED)

// LCD I2C Setup (use address 0x27, but try 0x3F if not working)
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Initialize LCD with I2C address 0x27 and 16 columns, 2 rows

// Thresholds for air quality levels
#define GOOD_AIR_QUALITY 700
#define POOR_AIR_QUALITY 300

void setup() {
  // Start Serial Communication
  Serial.begin(9600);

  // Initialize Buzzer and Light pins
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  // Initialize the LCD
  lcd.begin(16, 2); // Initialize LCD with 16 columns, 2 rows
  delay(1000);  // Wait for 1 second for the LCD to initialize properly
  lcd.backlight();  // Turn on the LCD backlight
  lcd.setCursor(0, 0);  // Set cursor to the first column of the first row
  lcd.print("Air Quality Monitor");  // Display the title
  delay(2000);  // Wait for 2 seconds

  // Test if LCD is working by printing a test message
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hello World");
  delay(2000);  // Wait for 2 seconds
}

void loop() {
  // Read the air quality sensor value (simulated by potentiometer)
  int airSensorValue = analogRead(A0);

  // Map the sensor value to a percentage (0-100% for display)
  float airQualityPercentage = map(airSensorValue, 0, 1023, 0, 100);

  // Display the air quality on the LCD
  lcd.clear();  // Clear the screen
  lcd.setCursor(0, 0);  // Set cursor to the first column of the first row
  lcd.print("Air Quality: ");
  lcd.print(airQualityPercentage);
  lcd.print("%");

  // Buzzer and Light activation based on air quality
  if (airSensorValue > 700) {
    digitalWrite(8, LOW);  // Turn off Buzzer
    digitalWrite(9, HIGH);  // Turn on Light (Good air quality)
  } else if (airSensorValue < 300) {
    digitalWrite(8, HIGH);  // Turn on Buzzer
    digitalWrite(9, LOW);   // Turn off Light (Poor air quality)
  } else {
    digitalWrite(8, LOW);  // Turn off Buzzer
    digitalWrite(9, LOW);   // Turn off Light (Moderate air quality)
  }

  // Delay for a short time
  delay(500);
}
