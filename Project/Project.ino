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