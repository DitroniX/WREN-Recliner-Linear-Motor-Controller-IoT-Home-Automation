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
  Defaults
    GPIO 00 | HIGH
    GPIO 01 | LOW 
    GPIO 02 | HIGH
    GPIO 03 | HIGH
    GPIO 04 | LOW 
    GPIO 05 | LOW 
    GPIO 06 | LOW 
    GPIO 07 | HIGH
    GPIO 08 | LOW 
    GPIO 09 | LOW 
    GPIO 12 | HIGH
*/

// List of usable GPIO pins for ESP32-C5 (0-28)
// Exclude or be careful with strapping/boot pins and flash pins
// Need to Skip 10, 11, 13, 14, 23, 24, 25, 26, 27, 28
const uint8_t gpioPins[] = {
  // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 23, 24, 25, 26, 27, 28
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 12
};

const int numPins = sizeof(gpioPins) / sizeof(gpioPins[0]);

void setup() {
  // Stabalise
  delay(250);

  // Initialise UART
  Serial.begin(115200);
  while (!Serial)
    ;  // Wait for serial port to connect
  Serial.println("");

  // Set pin as input - No Pullup
  for (int i = 0; i < numPins; i++) {
    pinMode(i, INPUT);
  }

  delay(1000);

  Serial.println("WREN Bring Up and Test Example Code");
  Serial.println("\n=== ESP32-C5 GPIO Input State Scanner ===");
  Serial.println("Pin | State");
  Serial.println("----|------");
}

void loop() {

  for (int i = 0; i < numPins; i++) {
    uint8_t pin = gpioPins[i];
    int state = digitalRead(pin);

    Serial.printf("GPIO %02d | %s\n", pin, state == HIGH ? "HIGH" : "LOW ");
  }

  Serial.println("-----------------------------------");
  delay(2000);
}