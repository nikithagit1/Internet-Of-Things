#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// Define DHT sensor pin and type
#define DHTPIN 2      // Pin where the DATA pin is connected
#define DHTTYPE DHT22 // DHT22 sensor type

// Initialize DHT sensor
DHT dht(2, DHT22);

void setup() {
  Serial.begin(9600);
  Serial.println("Weather Report System");

  // Initialize the DHT sensor
  dht.begin();
  Serial.println("DHT22 sensor initialized");
}

void loop() {
  // Read temperature and humidity from DHT22
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Check if readings are valid
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT22 sensor!");
  } else {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println("°C");

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println("%");
  }

  // Simulate pressure and altitude data (as BMP180 is unavailable)
  float pressure = 1013.25; // Sea level standard atmospheric pressure in hPa
  float altitude = 50.0;    // Simulated altitude in meters

  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" hPa");

  Serial.print("Altitude: ");
  Serial.print(altitude);
  Serial.println(" m");

  Serial.println("-------------------------");

  // Delay before the next reading
  delay(2000);
}
