#include <DHT.h>

#define DHTPIN 2        // Pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22 type
#define POT_PIN A0      // Potentiometer pin (simulating soil moisture sensor)
#define RELAY_PIN 3     // Relay module pin
#define BUZZER_PIN 4    // Buzzer pin (optional)

// Thresholds
#define SOIL_THRESHOLD 400  // Soil moisture threshold (adjustable)
#define TEMP_THRESHOLD 35   // Temperature threshold in Celsius
#define HUMIDITY_THRESHOLD 30  // Humidity threshold (%)

DHT dht(2, DHT22);

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(A0, INPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);

  digitalWrite(3, LOW);  // Ensure pump/relay is OFF initially
  digitalWrite(4, LOW);
}

void loop() {
  int soilValue = analogRead(A0);  // Read potentiometer value
  float temperature = dht.readTemperature(); // Read temperature
  float humidity = dht.readHumidity();       // Read humidity

  // Check if any reading failed
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Soil Moisture: ");
  Serial.println(soilValue);
  Serial.print("Temperature: ");
  Serial.println(temperature);
  Serial.print("Humidity: ");
  Serial.println(humidity);

  // Check conditions to water plants
  if (soilValue > SOIL_THRESHOLD && temperature < TEMP_THRESHOLD && humidity > HUMIDITY_THRESHOLD) {
    Serial.println("Watering the plants...");
    digitalWrite(3, HIGH);  // Turn on the relay
    digitalWrite(4, HIGH); // Optional alert
    delay(5000);  // Simulate watering duration (5 seconds)
    digitalWrite(3, LOW);  // Turn off the relay
    digitalWrite(4, LOW);
  } else {
    Serial.println("No need to water the plants.");
    digitalWrite(3, LOW);  // Ensure relay is off
    digitalWrite(4, LOW);
  }

  delay(2000);  // Wait before the next reading
}
