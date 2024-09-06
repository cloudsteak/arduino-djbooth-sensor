#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define ONE_WIRE_BUS 2  // Data cable on D2

// I2C address, values 0x27 or 0x3F
LiquidCrystal_I2C lcd(0x27, 16, 2);  // 16x2 LCD display, I2C address: 0x27 or 0x3F


// Temperature sensor
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// int runCounter = 0;

void setup() {
  //randomSeed(analogRead(0));  // Seed the random number generator with noise from an unused analog pin
  sensors.begin(); // Temperature sensor init

  lcd.begin(16, 2);  //  Display size: 16 column és 2 row
  lcd.backlight();   // Backlight on
  lcd.setCursor(0, 0);   // First row, first position
  lcd.print("Welcome SIPP!");

  lcd.setCursor(0, 1);   // Second row, first position
  lcd.print("Let's get party!");
  delay(5000); // Wait
}

void loop() {
  //int randomNumber = random(10, 41);  // Generate a random number between 10 and 40
  //runCounter++;

  sensors.requestTemperatures(); // Get temperature from sensor
  float temperatureC = sensors.getTempCByIndex(0); // convert it to celsius

  // Convert Celsius to Fahrenheit
  float temperatureF = temperatureC * 9.0 / 5.0 + 32.0;

  String textOne = "Temp: ";
  String rowOne = textOne + temperatureC;
  String textTwo = "Temp: ";
  String rowTwo = textTwo + temperatureF;
  lcd.clear();
  // ***********************
  // First Row
  // ***********************
  lcd.setCursor(0, 0);   // First row, first position
  lcd.print("                "); // Clear row
  lcd.setCursor(0, 0);   // First row, first position
  lcd.print(rowOne);
  lcd.print(" "); // Print a space
  lcd.print((char) 223); // º character
  lcd.print("C"); // Celsius
  // ***********************
  // Second Row
  // ***********************
  lcd.setCursor(0, 1);   // Second row, first position
  lcd.setCursor(0, 1);   // Second row, first position
  lcd.print(rowTwo);
  lcd.print(" "); // Print a space
  lcd.print((char) 223); // º character
  lcd.print("F"); // Farenheit
  delay(1000);
  
}
