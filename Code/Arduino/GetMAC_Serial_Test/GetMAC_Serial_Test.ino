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

/*
  WREN MAC Address:	3C:DC:75:83:99:40
  WREN Serial ID:	83FFFE75DC3C
  WREN Bring Up and Test Example Code
*/

// Libraries
#include <Arduino.h>
#include "WiFi.h"

// **************** USER VARIABLES / DEFINES / STATIC / STRUCTURES / CONSTANTS ****************

// **************** OUTPUTS ****************
#define LED_Blue 27  // Red Blue

uint64_t chipid = ESP.getEfuseMac();  // Get ChipID (essentially the MAC address)

// **************** FUNCTIONS AND ROUTINES ****************

// **************** SETUP ****************
void setup() {
  // Stabalise
  delay(250);

  // Initialise UART
  Serial.begin(115200, SERIAL_8N1);  //115200
  while (!Serial)
    ;
  Serial.println("");

  //  Configures the specified LED GPIO as outputs
  pinMode(LED_Blue, OUTPUT);

  // LEDs Default Off State
  digitalWrite(LED_Blue, LOW);

  WiFi.mode(WIFI_MODE_STA);

  Serial.print("WREN MAC Address:\t");
  Serial.println(WiFi.macAddress());

  Serial.printf("WREN Serial ID:\t%04X", (uint16_t)(chipid >> 32));
  Serial.printf("%08X", (uint32_t)chipid);
  Serial.println("");

  Serial.println("WREN Bring Up and Test Example Code");
}

// **************** LOOP ****************
void loop() {

  Serial.print("WREN MAC Address:\t");
  Serial.println(WiFi.macAddress());

  Serial.printf("WREN Serial ID:\t%04X", (uint16_t)(chipid >> 32));
  Serial.printf("%08X", (uint32_t)chipid);
  Serial.println(" ..\n");  

  // Heart Beat
  digitalWrite(LED_Blue, HIGH);
  delay(500);
  digitalWrite(LED_Blue, LOW);
  delay(2000);
}