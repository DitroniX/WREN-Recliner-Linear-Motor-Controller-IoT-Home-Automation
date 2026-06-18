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

// ****************  VARIABLES / DEFINES / STATIC / STRUCTURES / CONSTANTS ****************

// **************** INPUTS ****************
#define IN1A 8
#define IN1B 9
#define IN2A 14
#define IN2B 13

// **************** OUTPUTS ****************
#define LED_Blue 27  // Red Blue

// **************** SETUP ****************
void setup() {

  // Stabalise
  delay(250);

  // Initialise UART
  Serial.begin(115200, SERIAL_8N1);  // 115200
  while (!Serial)
    ;
  Serial.println("");

  //  Configures the specified LED GPIO as outputs
  pinMode(LED_Blue, OUTPUT);

  // LEDs Default Off State
  digitalWrite(LED_Blue, LOW);

  // Configure GPIO Inputs
  pinMode(IN1A, INPUT_PULLDOWN);
  pinMode(IN1B, INPUT_PULLDOWN);
  pinMode(IN2A, INPUT_PULLDOWN);
  pinMode(IN2B, INPUT_PULLDOWN);

  Serial.println("WREN Bring Up and Test Example Code");
  Serial.println("Ready for Input");
}

// **************** LOOP ****************
void loop() {

  // Check for Inputs
  if (digitalRead(IN1A) == HIGH) {

    Serial.println("2 - IN1A");

    // Blue Heartbeat
    digitalWrite(LED_Blue, HIGH);
    delay(50);
    digitalWrite(LED_Blue, LOW);
    delay(50);
  }

  if (digitalRead(IN1B) == HIGH) {

    Serial.println("3 - IN1B");

    // Blue Heartbeat
    digitalWrite(LED_Blue, HIGH);
    delay(50);
    digitalWrite(LED_Blue, LOW);
    delay(50);
  }

  if (digitalRead(IN2A) == HIGH) {

    Serial.println("4 - IN2A");

    // Blue Heartbeat
    digitalWrite(LED_Blue, HIGH);
    delay(50);
    digitalWrite(LED_Blue, LOW);
    delay(50);
  }

  if (digitalRead(IN2B) == HIGH) {

    Serial.println("5 - IN2B");

    // Blue Heartbeat
    digitalWrite(LED_Blue, HIGH);
    delay(50);
    digitalWrite(LED_Blue, LOW);
    delay(50);
  }
}
