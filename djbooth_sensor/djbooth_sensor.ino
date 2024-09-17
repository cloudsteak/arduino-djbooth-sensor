#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc; // Real-time module

#define ONE_WIRE_BUS 2  // Data cable on D2

// I2C address, values 0x27 or 0x3F
LiquidCrystal_I2C lcd(0x27, 16, 2);  // 16x2 LCD display, I2C address: 0x27 or 0x3F


// Temperature sensor
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  // Init time module
  Serial.begin(9600);
  
  String statusMessage = "";

  if (!rtc.begin()) {
    statusMessage = "Couldn't find RTC";
    Serial.println(statusMessage);
    while (1);
  }

  if (rtc.lostPower()) {
    // If the RTC lost power and you need to set the time, uncomment the following line and adjust the date and time.
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  sensors.begin(); // Temperature sensor init

  lcd.begin(16, 2);  // Display size: 16 column és 2 row
  lcd.backlight();   // Backlight on
  
  // ***********************
  // Version information
  // ***********************  
  lcd.setCursor(0, 0);   // First row, first position
  lcd.print(" Version: 1.1.0 ");

  lcd.setCursor(0, 1);   // Second row, first position
  lcd.print("- Cloud Mentor -");
  delay(2000); // Wait
  lcd.clear(); // Clear screen

  // ***********************
  // Welcome message
  // ***********************
  lcd.setCursor(0, 0);   // First row, first position
  lcd.print(" Welcome SIPP!");

  lcd.setCursor(0, 1);   // Second row, first position
  lcd.print("Let's get party!");
  delay(5000); // Wait
  lcd.clear(); // Clear screen
}

void loop() {
  // Temp sensor
  sensors.requestTemperatures(); // Get temperature from sensor
  float temperatureC = sensors.getTempCByIndex(0); // convert it to celsius

  // Time module
  char currentTime[20];
  DateTime now = rtc.now();
  sprintf(currentTime, "%02d:%02d:%02d (%02d-%02d)", now.hour(), now.minute(), now.second() ,now.month(), now.day()); 

  // ***********************
  // First Row
  // ***********************
  lcd.setCursor(0, 0);   // First row, first position
  lcd.print(currentTime);

  // ***********************
  // Second Row
  // ***********************
  String tempRow = " Temp: " + String(temperatureC, 1);  // Limit to 1 decimal point
  lcd.setCursor(0, 1);   // Second row, first position
  lcd.print(tempRow);
  lcd.print(" "); // Print a space
  lcd.print((char) 223); // º character
  lcd.print("C"); // Celsius

  // Wait before restart the sequence (250 ms)
  delay(250);
}
