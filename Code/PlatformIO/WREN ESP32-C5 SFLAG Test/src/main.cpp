/*
  Dave Williams, DitroniX 2019-2026 (ditronix.net)
  WREN | ESP32-C5 Recliner Linear Motor Controller | IoT Home Automation

  Example Code, to demonstrate and test the WREN C5 - 260617

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
#include "Arduino.h"
#include "Wire.h"

#include "TCA6408A.h"

// Define I2C (Expansion Port)
#define I2C_SDA 2
#define I2C_SCL 3

// Hardware Serial 0 pins
#define RXD0 17
#define TXD0 16

// Hardware Serial 1 pins - RS485
#define RXLP 1
#define TXLP 0
#define ENLP 23 // RS485 UART Enable

// Configure WREN GPIO

// **************** GPIO  INPUTS ****************

// Driver 1 (from External 24V Inputs)
#define IN_1A 8 // Button 1 - DIN Pin 2 - Black - 1A
#define IN_1B 9 // Button 2 - DIN Pin 3 - Yellow - 1B

// Driver 2 (from External 24V Inputs)
#define IN_2A 14 // Button 3 - DIN Pin 4 - Brown - 2A
#define IN_2B 13 // Button 4 - DIN Pin 5 - Red - 2B

// ENABLE Input Driver 1
#define EN1 5

// ENABLE Input Driver 2
#define EN2 6

// Define SFLAG (Safety Flag)
#define SFLAG 10

// Define Temperature Alarm
#define TMP_Alarm 7

#define ADC_IN 4 // DCV Input

// **************** GPIO  OUTPUTS ****************

// LED
#define LED_Blue 27 // User

// **************** TCA6408 GPIO Expander OUTPUTS ****************

//    7     6     5     4     3     2     1     0
//    0x80  0x40  0x20  0x10  0x8   0x4   0x2   0x1
//

// Driver 1 Output Ports (L6205 Inputs)
#define EN_1 0   // Driver 1
#define OUT_1A 1 // (DIN Pin 4 - Black)
#define OUT_1B 2 // (DIN Pin 2 - Yellow)

// Driver 2 Output Ports (L6205 Inputs)
#define EN_2 3   // Driver 2
#define OUT_2A 4 // (DIN Pin 5 - Brown)
#define OUT_2B 5 // (DIN Pin 3 - Red)

#define LED_Test 7 // Test LED

// **************** TCA6408 GPIO Expander CONFIG ****************

// Register addresses
#define REG_INPUT_PORT 0x00   // Read only
#define REG_OUTPUT_PORT 0x01  // Read/Write
#define REG_POLARITY_INV 0x02 // Read/Write (default 0x00 = normal)
#define REG_CONFIG 0x03       // Read/Write (0 = output, 1 = input)

// ALL_OFF: Write 0x00 to output register to turn all ports LOW (off)
#define ALL_OFF 0x00

// **************** VARIABLES ****************

float ADC_Voltage;

// **************** Device ****************
TCA6408A tca(0x21);

// **************** Functions ****************

// Turn OFF all Ports
void Reset_Outputs()
{
  tca.digitalWrite8(ALL_OFF);
}

// Send pulses (blinks) to the LED on port 7
void FlashLED(int flashes = 0)
{
  const uint16_t onTime = 100;  // ms LED ON
  const uint16_t offTime = 500; // ms LED OFF

  delay(250);

  for (int i = 0; i < flashes; i++)
  {
    // tca.digitalWrite1(LED_Red, HIGH);
    digitalWrite(LED_Blue, HIGH); // Temp
    delay(onTime);
    // tca.digitalWrite1(LED_Red, LOW);
    digitalWrite(LED_Blue, LOW); // Temp
    delay(offTime);
  }

  delay(250);
}

// Read ADC DC Voltage Sensor of DCV Input
void ReadADC()
{
  ADC_Voltage = ((analogReadMilliVolts(ADC_IN) * 44.4444) / 1000); // Value may need tweaking.  Default 44.4444
}

// Flash LED as an Alert
void FlashAlert()
{
  // Red LED Flash Alert
  for (int x = 0; x <= 10; x++)
  {
    delay(250);

    tca.digitalWrite1(LED_Test, HIGH);
    delay(250);
    tca.digitalWrite1(LED_Test, LOW);
  }
}

// Reset/Restart ESP
void RestartESP()
{
  Serial.println("> RESTARTING ESP");
  void (*resetFunc)(void) = 0; // declare reset function at address 0
  resetFunc();                 // call reset
}

// Check for Fault Condition. Two examples of what you can do in event of a detected fault.
void FaultConditionCheck()
{
  // Detection of Main DC Power Fail, USB 5V only or Safety Fuse Blown.  Shutdown ESP.
  if (ADC_Voltage < 10 || ADC_Voltage > 48)
  {
    Serial.println("**************************************************");
    Serial.println("Main DC Power Fail or Safety Fuse Blown");
    Serial.println("Possibly running the board from USB 5V Only.");
    Serial.println("Shutting Down ESP. *Power Cycle device to Wake Up*");
    Serial.println("Safety Disabled both Motor Driver Ports");
    Serial.println("**************************************************");

    Serial.println("\nWREN Motor Driver Safety Fault Condition:");
    Serial.print("DC Input (Low or High) or Back EMF Surge Voltage: ");
    Serial.print(ADC_Voltage);
    Serial.println(" V");

    // Disable both Motor Driver Ports
    Reset_Outputs();

    FlashAlert();

    // Shutdown ESP.  Power Reset WILL be required to bring back to life.
    // Configure timer as a wake-up source
    // esp_sleep_enable_timer_wakeup(5 * 1000000ULL);
    esp_light_sleep_start();
    // ESP.deepSleep(0);
  }

  // Simple SFLAG alert and Voltage range check
  if (digitalRead(SFLAG) == HIGH)
  {

    Serial.println("*******************************************************");
    Serial.println("Over-load of Motor Driver, or Over-Temperature  ");
    Serial.println("ESP is Reatarting to try an Re-enable");
    Serial.println("Safety Reset both Motor Driver Ports.");
    Serial.println("*******************************************************");

    // Disable both Motor Driver Ports
    Reset_Outputs();

    FlashAlert();

    // Reset/Restart ESP
    RestartESP();
  }
}

// Hello LED World
void LEDTest()
{
  digitalWrite(LED_Blue, HIGH); // Temp
  delay(500);
  digitalWrite(LED_Blue, LOW); // Temp
  delay(250);
  tca.digitalWrite1(LED_Test, HIGH);
  delay(500);
  tca.digitalWrite1(LED_Test, LOW);
  delay(250);
  digitalWrite(ENLP, LOW);
  delay(500);
  digitalWrite(ENLP, HIGH);
  delay(250);
}

// Setup
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
  Serial1.begin(9600, SERIAL_8N1, RXLP, TXLP); // LP
  while (!Serial)
    ;
  Serial.println("UART 1 Opened (RS485 Port)");

  // Initialise RS485 UART Enable on GP23
  pinMode(ENLP, OUTPUT);

  // Force RS485 UART Driver Enable and Receiver is Disabled
  digitalWrite(ENLP, HIGH);

  // Initialize I2C
  Wire.begin(I2C_SDA, I2C_SCL);
  // Wire.setClock(400000);
  delay(250);

  // Initialize TCA6408
  if (tca.begin() == false)
  {
    Serial.println("No TCA found.");
    while (1)
      ;
  }

  Serial.println("TCA Connected");

  Serial.println("Set TCA Configuration");
  tca.setPinMode8(0x00);  // All outputs
  tca.setPolarity8(0x00); // Low

  Reset_Outputs();

  // Configure GPIO Inputs
  pinMode(IN_1A, INPUT_PULLDOWN); // DIN 2
  pinMode(IN_1B, INPUT_PULLDOWN); // DIN 3
  pinMode(IN_2A, INPUT_PULLDOWN); // DIN 4
  pinMode(IN_1B, INPUT_PULLDOWN); // DIN 5

  pinMode(EN1, INPUT);
  pinMode(EN2, INPUT);

  pinMode(SFLAG, INPUT_PULLDOWN);

  // Configure GPIO Outputs
  pinMode(LED_Blue, OUTPUT);

  // RS485 TX Test
  Serial1.write("Hello World - Test\n");

  // LED Test
  LEDTest();

  Serial.println("WREN Test - Waiting for Controller Input");
  Serial.println("");
}

// ######### LOOP #########
void loop()
{

  // Read ADC Input Voltage
  ReadADC();

  // Check for Fault Condition
  FaultConditionCheck();

  // // Define DIN Input Ports (from External 24V/29V Inputs)
  bool IN_1A_State = LOW; // Button 1 - DIN Pin 2 - Black
  bool IN_1B_State = LOW; // Button 2 - DIN Pin 3 - Yellow
  bool IN_2A_State = LOW; // Button 3 - DIN Pin 4 - Brown
  bool IN_2B_State = LOW; // Button 4 - DIN Pin 5 - Red

  // Read Input / Buttons
  IN_1A_State = digitalRead(IN_1A); // Read the input pin 1A GP8
  IN_1B_State = digitalRead(IN_1B); // Read the input pin 1B GP9
  IN_2A_State = digitalRead(IN_2A); // Read the input pin 2A GP14
  IN_2B_State = digitalRead(IN_2B); // Read the input pin 2B GP13

  // Read Enable Ports
  bool EN1_State = LOW;         // EN1
  bool EN2_State = LOW;         // EN1
  EN1_State = digitalRead(EN1); // Read the input EN1
  EN2_State = digitalRead(EN2); // Read the input EN1

  // Two Buttons Example - Flash LED or other function
  if (IN_1A_State == HIGH && IN_1B_State == HIGH)
  {
    Serial.println("\nTwo Button Pressed - Flashing LEDs");
    FlashLED(5);
    // RestartESP();
  }

  // Basic Detection.  If any Input High then set appropriate Motor Output High
  if (IN_1A_State == HIGH || IN_1B_State == HIGH || IN_2A_State == HIGH || IN_2B_State == HIGH)
  {

    // Enable L6205 Drivers
    tca.digitalWrite1(EN_1, HIGH);
    tca.digitalWrite1(EN_2, HIGH);

    if (IN_1A_State == HIGH)
    {
      Serial.println("\n2 - WREN Motor Driver 1A High\n");
      tca.digitalWrite1(OUT_1A, HIGH);
      // FlashLED(2); // Hello World Pin Number
    }

    if (IN_1B_State == HIGH)
    {
      Serial.println("\n3 - WREN Motor Driver 1B High\n");
      tca.digitalWrite1(OUT_1B, HIGH);
      // FlashLED(3); // Hello World Pin Number
    }

    if (IN_2A_State == HIGH)
    {
      Serial.println("\n4 -WREN Motor Driver 2A High\n");
      tca.digitalWrite1(OUT_2A, HIGH);
      // FlashLED(4); // Hello World Pin Number
    }

    if (IN_2B_State == HIGH)
    {
      Serial.println("\n5 - WREN Motor Driver 2B High\n");
      tca.digitalWrite1(OUT_2B, HIGH);
      // FlashLED(5); // Hello World Pin Number
    }

    // Display Input State
    Serial.println("\nInputs \t1A(2)\t1B(3)\t2A(4)\t2B(5\tEN1\tEN2\tADC\n");
    Serial.print("\t");
    Serial.print(IN_1A_State ? 'H' : 'L');
    Serial.print("\t");
    Serial.print(IN_1B_State ? 'H' : 'L');
    Serial.print("\t");
    Serial.print(IN_2A_State ? 'H' : 'L');
    Serial.print("\t");
    Serial.print(IN_2B_State ? 'H' : 'L');
    Serial.print("\t");

    Serial.print(EN1_State ? 'H' : 'L');
    Serial.print("\t");
    Serial.print(EN2_State ? 'H' : 'L');
    Serial.print("\t");

    Serial.print(ADC_Voltage);
    Serial.println("");
  }
  else
  {
    tca.digitalWrite1(OUT_1A, LOW);
    tca.digitalWrite1(OUT_1B, LOW);
    tca.digitalWrite1(OUT_2A, LOW);
    tca.digitalWrite1(OUT_2B, LOW);
  }

  // Heat Beat Blue LED
  digitalWrite(LED_Blue, HIGH);
  delay(10);
  digitalWrite(LED_Blue, LOW);
  delay(50);
}
