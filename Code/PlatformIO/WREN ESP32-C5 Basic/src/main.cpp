/*
  Dave Williams, DitroniX 2019-2026 (ditronix.net)
  WREN | ESP32-C5 Recliner Linear Motor Controller | IoT Home Automation

  Example Code, to demonstrate and test the WREN C5

  Remember!
  - Set the BOARD to Use ESP32C5 Dev Module (or similar).
  - You can also set the BAUD rate up to 921600 to speed up flashing.
  - The SDK does NOT need external power to flash.  It will take Power from the USB 5V.
  - The Serial Monitor is configured for BAUD 115200

  The purpose of this test code is to cycle through the various main functions of the board as part of bring up testing.

  This test code is OPEN SOURCE and formatted for easier viewing.  Although is is not intended for real world use, it may be freely used, or modified as needed.
  It is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

  For board configuration, see:

  * github.com/DitroniX/WREN-Recliner-Linear-Motor-Controller-IoT-Home-Automation/wiki/Arduino-IDE
  * github.com/DitroniX/WREN-Recliner-Linear-Motor-Controller-IoT-Home-Automation/wiki/PlatformIO-ESP32%E2%80%90C5
  * github.com/DitroniX/WREN-Recliner-Linear-Motor-Controller-IoT-Home-Automation/wiki/Home-Assistant-and-ESPHome
  * github.com/DitroniX/Home-Assistant-Dev

  Further information, details and examples can be found on our website or github.com/DitroniX

  * ditronix.net
  * github.com/DitroniX
  * github.com/DitroniX/WREN-Recliner-Linear-Motor-Controller-IoT-Home-Automation
  * github.com/DitroniX/WREN-Recliner-Linear-Motor-Controller-IoT-Home-Automation/wiki
  * github.com/DitroniX/WREN-Recliner-Linear-Motor-Controller-IoT-Home-Automation/wiki/FAQ
  * hackster.io/DitroniX/
  * hackster.io/DitroniX/wren-esp32-c5-recliner-linear-motor-controller-iot-rs485-e2b397
*/

// Libraries
#include <Arduino.h>
#include <Wire.h>

#include "TCA6408A.h"
#include <SparkFunTMP102.h>

// **************** USER VARIABLES / DEFINES / STATIC / STRUCTURES / CONSTANTS ****************

// **************** OUTPUTS ****************
#define LED_Blue 27 // Blue LED

// **************** Ports ****************
// Define I2C (Expansion Port)
#define I2C_SDA 2
#define I2C_SCL 3

// Hardware Serial 1 pins - RS485
#define RXLP 1
#define TXLP 0
#define ENLP 23 // RS485 UART Enable

// **************** Devices ****************
TCA6408A expander(0x21); // or 0x21 depending on your ADDR pin

TMP102 TempSensor;

// Variables TMP102
float TemperatureC; // TMP102 Temperature C
float TemperatureF; // TMP102 Temperature F

// **************** FUNCTIONS AND ROUTINES ****************

// I2C Bus Scanner
void ScanI2CBus()
{

  // Useful Reference https://i2cdevices.org/addresses

  byte error, address;
  int nDevices;

  Serial.println("Scanning I2C Bus for Devices for Auto Configuration ...\n");

  nDevices = 0;
  for (address = 1; address < 127; address++)
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    nDevices++;
    if (nDevices == 1)
      Serial.println(" I2C Possible Device(s) found at Address:");
    if (error == 0)
    {
      Serial.print(" * Hex 0x");
      Serial.print(address, HEX);

      Serial.print(" (");
      if (address < 16)
      {
        Serial.print("0");
      }
      Serial.print(address);
      Serial.print(")\t");

      switch (address)
      {
      case 0x21:
        Serial.print(" TCA6408A GPIO Expander");
        break;
      case 0x48:
        Serial.print(" TLA2024 12-bit ADC");
        break;
      case 0x4A:
        Serial.print(" TMP102 Temperature Sensor");
        break;
      case 0x49:
        Serial.print(" ADS1115 16-bit ADC");
        break;
      case 0x3C ... 0x3D:
        Serial.print(" OLED Display");
        break;
      case 0x50:
        Serial.print(" EEPROM");
        break;
      case 0x55:
        Serial.print(" EEPROM");
        break;
      case 0x58:
        Serial.print(" EEPROM (Reserved Unused Address)");
        break;
      case 0x60 ... 0x62:
        Serial.print(" MCP4728 12-bit DAC");
        break;
      case 0x68:
        Serial.print(" DS3231SN RTC");
        break;
      case 0x71 ... 0x77:
        Serial.print(" PCA9671 GPIO Expander");
        break;
      case 0x7C:
        Serial.print(" PCA9671 GPIO Expander (Reserved Address)");
        break;
      default:
        Serial.print(" ?");
        break;
      }
      Serial.println();
    }
    else if (error == 4)
    {
      Serial.print(" * Unknown error at address Decimal ");
      if (address < 16)
      {
        Serial.print("0");
      }
      Serial.print(address);
      Serial.print(" = Hex 0x");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
  {
    Serial.println(" * No I2C devices found. Possible Hardware Issue?");
  }
  else
  {
    Serial.println(" I2C Bus Scan Complete\n");
  }
} // ScanI2CBus

// **************** SETUP ****************
void setup()
{
  // Stabalise
  delay(250);

  // Initialise UART
  Serial.begin(115200);
  while (!Serial)
    ; // Wait for serial port to connect
  Serial.println("");

    // Initialise UART 1 - RS485 Port
  Serial1.begin(9600, SERIAL_8N1, RXLP, TXLP);  //LP
  while (!Serial)
    ;
  Serial.println("UART 1 Opened (RS485 Port)");

  // Initialise RS485 UART Enable on GP23
    
  digitalWrite(ENLP, LOW);

  // Initialize I2C
  Wire.begin(I2C_SDA, I2C_SCL);

  // Initialise LED Output
  pinMode(LED_Blue, OUTPUT);

  if (!expander.begin())
  {
    Serial.println("TCA6408A not found! Houston, we may have a problem!");
    while (1)
      ;
  }

  // Set ALL pins P0 to P7 as OUTPUTS
  expander.setPinMode8(0x00); // 0x00 = all outputs
  Serial.println("TCA6408A initialized.  Houston, all good to go.");

  if (!TempSensor.begin(0x4A))
  {
    Serial.println("Failed to initialize TMP102");
    while (1)
      ;
  }

  Serial.println("Temperature Sensor (TMP102) Initialised\n");
  delay(100);
  TempSensor.sleep(); // Put sensor to sleep

  Serial.println("WREN Bring Up and Test Example Code");

  ScanI2CBus();

  Serial.println("Flashing Blue LED");
}

// **************** LOOP ****************
void loop()
{
  // ++++++++++++++++++  RS485 Test ++++++++++++++++++
    Serial1.write("Hello World - Test\n");



  // ++++++++++++++++++  Cycle Outputs ++++++++++++++++++
  Serial.println("TCA6408A Cycle Outputs...");
  for (int pin = 0; pin < 8; pin++)
  {
    Serial.printf("P%d ON\n", pin);
    expander.digitalWrite1(pin, HIGH);
    delay(250);

    Serial.printf("P%d OFF\n", pin);
    expander.digitalWrite1(pin, LOW);
    delay(200); // short pause between pins
  }

  // ++++++++++++++++++  Temperature ++++++++++++++++++
  TemperatureC = TempSensor.readTempC(); // Centigrade
  TemperatureF = TempSensor.readTempF(); // Fahrenheit

  Serial.println("TMP102 PCB Temperature: " + String(TemperatureC) + " °C");
  Serial.println("TMP102 PCB Temperature: " + String(TemperatureF) + " °F\n");

  // Return sensor to sleep
  TempSensor.sleep();

  // ++++++++++++++++++  LEDS ++++++++++++++++++

  // Cycle RED LED
  digitalWrite(LED_Blue, HIGH);
  delay(500);
  digitalWrite(LED_Blue, LOW);
  delay(500);
}
//