#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int soilMoisturePin = 34;
const int ldrPin = 35;
const int motorPin = 12;
const int lightPin = 13;
const int fanPin = 4;
const int dhtPin = 14;
const int buzzerPin = 5;
const int LCDAddress = 0x27; // I2C address of your LCD display

DHT dht(dhtPin, DHT11);
LiquidCrystal_I2C lcd(LCDAddress, 16, 2); // Adjust the columns (16) and rows (2) based on your LCD

void setup() {
  Serial.begin(115200);
  lcd.init();                      // Initialize the LCD display
  lcd.backlight();                 // Turn on the backlight
  lcd.setCursor(0, 0);
  lcd.print("Temperature:      C");
  lcd.setCursor(0, 1);
  lcd.print("Humidity:  %");

  pinMode(motorPin, OUTPUT);
  pinMode(lightPin, OUTPUT);
  pinMode(fanPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  dht.begin();
  Wire.begin();
}

void loop() {
  int soilMoisture = analogRead(soilMoisturePin);
  int lightIntensity = analogRead(ldrPin);
  int moisturePercentage = map(soilMoisture, 4095, 0, 0, 100);
  int lightPercentage = map(lightIntensity, 0, 4095, 0, 100);
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  Serial.print("Soil Moisture Percentage: ");
  Serial.println(moisturePercentage);
  Serial.print("Light Intensity Percentage: ");
  Serial.println(lightPercentage);
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Update the LCD display with the sensor data
  lcd.setCursor(6, 0);
  lcd.print(temperature);
  lcd.setCursor(10, 1);
  lcd.print(humidity);
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print("%");
  lcd.setCursor(0, 0);
  lcd.print("Temper: ");
  lcd.print(temperature);
  lcd.print("°C");

  if (moisturePercentage < 20) { 
    digitalWrite(motorPin, LOW);
    Serial.println("Watering the plant!");
  } else {
    digitalWrite(motorPin, HIGH);
    Serial.println("Soil Moisture is nomal!!");
  }

  if (lightPercentage > 70) {
    digitalWrite(lightPin, HIGH);
    //digitalWrite(buzzerPin, HIGH);
    delay(500);
    //digitalWrite(buzzerPin, LOW);
    Serial.println("Light intensity is not enough. Turn on Artificial light!");
  } else {
    digitalWrite(lightPin, LOW);
    Serial.println("Light intensity is enough");
  }

  if (temperature > 30) {
    digitalWrite(fanPin, LOW);
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
    Serial.println("Temperature is high. Turning on the fan!");
  } else {
    digitalWrite(fanPin, HIGH);
    Serial.println("Temperature is normal");
  }

  delay(1000);
}
