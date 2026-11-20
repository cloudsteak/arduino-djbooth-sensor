# DJ booth Sensor Project

## Project Background

This project is designed to monitor temperature using the **DS18B20** sensor and get current datetime using the **DS3231+AT24C32 RTCM** real-time module. Then display the current time in EU timeformat and temperature in Celsius and on a **16x2 LCD** display. It aims to create a simple but effective way to visualize real-time temperature in a DJ booth or any other environment where monitoring temperature is essential for comfort and equipment safety.

The code leverages the I2C protocol to communicate with the LCD and the **DallasTemperature** library to read from the temperature sensor. The display welcomes the user with a custom message and then continuously updates the temperature values in both Celsius and Fahrenheit.

## Components (Physical)

- **AR-NANOCH-TYPE-C**: Arduino Nano clone development board.
- **DS18B20**: One-wire digital temperature sensor.
- **DS3231+AT24C32 RTCM**: Real-time clock module with EEPROM.
- **KC-1602-BB-I2C**: 16x2 I2C LCD display for displaying messages and temperature readings.
- **4.7kΩ resistor**: Used to pull up the data line of the DS18B20 sensor.
- **Breadboard**: Optional, for wiring connections.
- **Jumper wires**: For connecting components to the Arduino.
- **1599 EBK (170x86x35) Project Box**: Optional, for housing the components.

## Prerequisites and Installation

Firmware lives in `src/main.cpp` and is built with [PlatformIO](https://platformio.org/).

Target board: **AR-NANOCH-TYPE-C** (ATmega328P, CH340, USB Type-C). This board uses the new bootloader, so the default environment is `sipp_djbooth_sensor` (Arduino IDE: **Processor → ATmega328P**, 115200 baud).

Libraries (pulled automatically from `platformio.ini`):

- **OneWire** — DS18B20 bus
- **DallasTemperature** — DS18B20 readings
- **LiquidCrystal_I2C** — 16x2 LCD over I2C
- **RTClib** — DS3231 real-time clock
- **Wire** — built into the Arduino framework

On Windows, install the [WCH CH340 driver](https://www.wch-ic.com/downloads/CH341SER_EXE.html) if the board does not show up as a COM port.

### Hardware connections

- **DS18B20** connections:

  - **VCC (Red)**: Connect to Arduino's **5V**.
  - **GND (Black)**: Connect to Arduino's **GND**.
  - **Data (Yellow)**: Connect to Arduino **D2**. Add a **4.7kΩ resistor** between the **VCC** and **Data** lines.

- **DS3231+AT24C32 RTCM** connections:

  - **VCC**: Connect to Arduino's **5V**.
  - **GND**: Connect to Arduino's **GND**.
  - **SDA**: Connect to Arduino's **A4**.
  - **SCL**: Connect to Arduino's **A5**.

- **16x2 LCD display** (I2C):
  - **VCC**: Connect to Arduino's **5V**.
  - **GND**: Connect to Arduino's **GND**.
  - **SDA**: Connect to Arduino's **A4**.
  - **SCL**: Connect to Arduino's **A5**.

### Build and upload

From the project root, with the Nano plugged in over USB-C:

```bash
pio run              # compile
pio run -t upload    # flash (COM port is detected automatically)
pio device monitor   # serial log at 9600 baud
```

In the PlatformIO IDE extension the same actions are **Build**, **Upload**, and **Monitor**. The board shows up as **USB-SERIAL CH340**.

If upload stops at `stk500_recv(): programmer is not responding`, that board has the old bootloader. Upload with:

```bash
pio run -e nano -t upload
```

## What This Code Does

This project uses the **DS18B20 temperature sensor**, **DS3231+AT24C32 RTCM module** and an **I2C LCD** to display the current temperature and current time in Celsius. Here’s how the code works:

1. **Setup Phase**:

   - Time is initialized using the **DS3231+AT24C32 RTCM** module.
   - The temperature sensor is initialized.
   - The LCD is initialized and the backlight is turned on.
   - Version number message is displayed on the LCD, then waits for 2 seconds.
   - Clear the LCD display.
   - A welcome message, **"Welcome SIPP!"**, is displayed on the first line of the LCD.
   - A message, **"Let's get party!"**, is displayed on the second line.
   - The setup waits for 5 seconds before moving into the loop.
   - The LCD is cleared again.

2. **Main Loop**:
   - Time is read from the **DS3231+AT24C32 RTCM** module.
   - The time is converted to **EU time format** (24-hour clock, ). Format: HH:MM:SS (mm-dd)
   - The temperature is read from the **DS18B20** sensor in **Celsius**.
   - The first row of the LCD displays the time in the format above.
   - The second row displays the temperature in Celsius with a **degree symbol (ºC)**.
   - The display updates every 250 milliseconds, because time module is updated sharply every second and we need to catch the time update. If we update the display every second, we may miss the time update and the display shows the same time for 2 seconds.

The code is designed to be flexible and could be easily extended to handle additional sensors or display features.
