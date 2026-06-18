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
  GPIO00 | LOW       | Floating / IE        | 
  GPIO01 | LOW       | Floating / IE        | 
  GPIO02 | LOW       | Floating / IE        | STRAPPING
  GPIO03 | LOW       | Floating / IE        | 
  GPIO04 | HIGH      | Floating / IE        | 
  GPIO05 | LOW       | Floating / IE        | 
  GPIO06 | LOW       | Floating / IE        | 
  GPIO07 | LOW       | HIGH (strapping)     | STRAPPING
  GPIO08 | LOW       | Floating / IE        | 
  GPIO09 | LOW       | Floating / IE        | 
  GPIO10 | LOW       | Floating / IE        | 
  GPIO11 | HIGH      | Floating / IE        | 
  GPIO12 | HIGH      | HIGH (WPU)           | 
  GPIO13 | LOW       | Floating / IE        | 
  GPIO14 | HIGH      | HIGH (USB_PU)        | 
  GPIO15 | HIGH      | HIGH (flash WPU)     | 
  GPIO16 | HIGH      | HIGH (flash WPU)     | 
  GPIO17 | LOW       | HIGH (flash WPU)     | 
  GPIO18 | LOW       | HIGH (flash WPU)     | 
  GPIO19 | LOW       | HIGH (flash WPU)     | 
  GPIO20 | HIGH      | HIGH (flash WPU)     | 
  GPIO21 | LOW       | HIGH (flash WPU)     | 
  GPIO22 | LOW       | HIGH (flash WPU)     | 
  GPIO23 | LOW       | Floating / IE        | 
  GPIO24 | LOW       | Floating / IE        | 
  GPIO25 | LOW       | Floating / IE        | 
  GPIO26 | LOW       | Floating / IE        | 
  GPIO27 | HIGH      | HIGH (WPU)           | 
  GPIO28 | HIGH      | HIGH (WPU)       
*/

// List of usable GPIO pins for ESP32-C5 (0-28)
// Exclude or be careful with strapping/boot pins and flash pins
// Need to Skip 10, 11, 13, 14, 23, 24, 25, 26, 27, 28
const uint8_t gpioPins[] = {
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
  13, 14, 15, 16, 17, 18, 19, 20, 21, 22,
  23, 24, 25, 26, 27, 28
};

const int numPins = sizeof(gpioPins) / sizeof(gpioPins[0]);

// Expected default behavior at reset (from ESP32-C5 datasheet)
String getDefaultState(uint8_t pin) {
  if (pin == 12 || pin == 27 || pin == 28) return "HIGH (WPU)";
  if (pin == 7) return "HIGH (strapping)";
  if (pin >= 15 && pin <= 22) return "HIGH (flash WPU)";
  if (pin == 14) return "HIGH (USB_PU)";
  return "Floating / IE";
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("\n=== ESP32-C5 GPIO Input Scanner (HIGH/LOW) ===");
  Serial.println("Pin   | Current   | Expected Default     | Note");
  Serial.println("------|-----------|----------------------|-----");

  Serial.println("Scanning... (HIGH = 3.3V, LOW = 0V)\n");
}

void loop() {
  unsigned long now = millis();
  Serial.printf("=== Scan @ %lu ms ===\n", now);

  for (int i = 0; i < numPins; i++) {
    uint8_t pin = gpioPins[i];
    int state = digitalRead(pin);
    String current = (state == HIGH) ? "HIGH" : "LOW ";
    String def = getDefaultState(pin);

    Serial.printf("GPIO%02d | %s      | %-20s | %s\n",
                  pin, current.c_str(), def.c_str(),
                  (pin == 2 || pin == 7) ? "STRAPPING" : "");
  }

  Serial.println("--------------------------------------------------");
  delay(2000);
}