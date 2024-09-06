# DJ Boot Sensor Project

## Project Background

This project is designed to monitor temperature using the **DS18B20** sensor and display the readings in both Celsius and Fahrenheit on a **16x2 LCD** display. It aims to create a simple but effective way to visualize real-time temperature in a DJ booth or any other environment where monitoring temperature is essential for comfort and equipment safety.

The code leverages the I2C protocol to communicate with the LCD and the **DallasTemperature** library to read from the temperature sensor. The display welcomes the user with a custom message and then continuously updates the temperature values in both Celsius and Fahrenheit.

## Components (Physical)

- **AR-NANOCH-TYPE-C**: Arduino Nano clone development board.
- **DS18B20**: One-wire digital temperature sensor.
- **KC-1602-BB-I2C**: 16x2 I2C LCD display for displaying messages and temperature readings.
- **4.7kΩ resistor**: Used to pull up the data line of the DS18B20 sensor.
- **Breadboard**: Optional, for wiring connections.
- **Jumper wires**: For connecting components to the Arduino.
- **1599 EBK (170x86x35) Project Box**: Optional, for housing the components.

## Prerequisites and Installation

Project directory: ./djbooth_sensor

### 1. Install Required Libraries:

You need to install the following libraries using the Arduino IDE's Library Manager:

- **OneWire**: Used for communicating with the DS18B20 temperature sensor.
- **DallasTemperature**: Simplifies reading from the DS18B20 sensor.
- **LiquidCrystal_I2C**: For controlling the 16x2 LCD display via I2C.

To install these libraries:

1. Open Arduino IDE.
2. Go to **Sketch** -> **Include Library** -> **Manage Libraries**.
3. Search for each of the required libraries and click **Install**.

### 2. Hardware Connections:

- **DS18B20** connections:

  - **VCC (Red)**: Connect to Arduino's **5V**.
  - **GND (Black)**: Connect to Arduino's **GND**.
  - **Data (Yellow)**: Connect to Arduino **D2**. Add a **4.7kΩ resistor** between the **VCC** and **Data** lines.

- **16x2 LCD display** (I2C):
  - **VCC**: Connect to Arduino's **5V**.
  - **GND**: Connect to Arduino's **GND**.
  - **SDA**: Connect to Arduino's **A4**.
  - **SCL**: Connect to Arduino's **A5**.

### 3. Code Upload:

Once the hardware is connected and the libraries are installed:

1. Open the **Arduino IDE**.
2. Copy the provided code into the IDE.
3. Select the correct board (`Arduino Nano`) and port under **Tools**.
4. Upload the code to the Arduino.

## What This Code Does

This project uses the **DS18B20 temperature sensor** and an **I2C LCD** to display the current temperature in both Celsius and Fahrenheit. Here’s how the code works:

1. **Setup Phase**:

   - The temperature sensor is initialized.
   - The LCD is initialized and the backlight is turned on.
   - A welcome message, **"Welcome SIPP!"**, is displayed on the first line of the LCD.
   - A message, **"Let's get party!"**, is displayed on the second line.
   - The setup waits for 5 seconds before moving into the loop.

2. **Main Loop**:
   - The temperature is read from the **DS18B20** sensor in **Celsius**.
   - The Celsius temperature is converted to **Fahrenheit**.
   - The first row of the LCD displays the temperature in Celsius with a **degree symbol (ºC)**.
   - The second row displays the temperature in Fahrenheit with a **degree symbol (ºF)**.
   - The display updates every second.

### Code Breakdown:

- **sensors.requestTemperatures()**: Requests the current temperature from the sensor.
- **getTempCByIndex(0)**: Reads the temperature in Celsius from the sensor.
- **lcd.clear()**: Clears the LCD before writing new content.
- **lcd.setCursor(x, y)**: Positions the cursor on the LCD at row `y` and column `x`.
- **delay(1000)**: Delays the loop for 1 second, causing the display to update every second.

The code is designed to be flexible and could be easily extended to handle additional sensors or display features.

---
