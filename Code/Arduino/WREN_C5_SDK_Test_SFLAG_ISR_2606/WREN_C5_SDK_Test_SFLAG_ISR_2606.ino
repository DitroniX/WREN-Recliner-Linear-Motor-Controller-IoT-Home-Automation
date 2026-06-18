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
  Dave Williams, DitroniX 2019-2026 (ditronix.net)
  WREN | ESP32-C5 Recliner Linear Motor Controller | IoT Home Automation

  STABLE & RELIABLE VERSION - Clean Heartbeat + Full Functionality
*/

// Libraries
#include "Arduino.h"
#include "Wire.h"
#include "TCA6408A.h"

// ==================== PIN DEFINITIONS ====================

#define I2C_SDA 2
#define I2C_SCL 3
#define RXLP 1
#define TXLP 0
#define ENLP 23

#define IN_1A 8
#define IN_1B 9
#define IN_2A 14
#define IN_2B 13
#define EN1   5
#define EN2   6
#define SFLAG 10
#define ADC_IN 4

#define LED_Blue 27

#define EN_1   0
#define OUT_1A 1
#define OUT_1B 2
#define EN_2   3
#define OUT_2A 4
#define OUT_2B 5
#define LED_Test 7

#define ALL_OFF 0x00

// ==================== VOLATILE VARIABLES ====================

volatile bool IN_1A_State = false;
volatile bool IN_1B_State = false;
volatile bool IN_2A_State = false;
volatile bool IN_2B_State = false;
volatile bool EN1_State   = false;
volatile bool EN2_State   = false;
volatile bool SFLAG_State = false;

float ADC_Voltage = 0.0;
unsigned long lastHeartbeat = 0;
bool ledState = false;

// ==================== DEVICE ====================

TCA6408A tca(0x21);

// ==================== ISR ====================

void IRAM_ATTR inputISR()
{
    IN_1A_State = digitalRead(IN_1A);
    IN_1B_State = digitalRead(IN_1B);
    IN_2A_State = digitalRead(IN_2A);
    IN_2B_State = digitalRead(IN_2B);
    EN1_State   = digitalRead(EN1);
    EN2_State   = digitalRead(EN2);
    SFLAG_State = digitalRead(SFLAG);
}

// ==================== HELPERS ====================

void Reset_Outputs() { tca.digitalWrite8(ALL_OFF); }

void ReadADC()
{
    ADC_Voltage = (analogReadMilliVolts(ADC_IN) * 44.4444f) / 1000.0f;
}

void FlashAlert()
{
    for (int x = 0; x <= 10; x++)
    {
        delay(250);
        tca.digitalWrite1(LED_Test, HIGH);
        delay(250);
        tca.digitalWrite1(LED_Test, LOW);
    }
}

void RestartESP()
{
    Serial.println("> RESTARTING ESP");
    void (*resetFunc)(void) = 0;
    resetFunc();
}

void FaultConditionCheck()
{
    ReadADC();

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

        Reset_Outputs();
        FlashAlert();
        esp_light_sleep_start();
    }

    if (SFLAG_State == HIGH)
    {
        Serial.println("*******************************************************");
        Serial.println("Over-load of Motor Driver, or Over-Temperature  ");
        Serial.println("ESP is Reatarting to try an Re-enable");
        Serial.println("Safety Reset both Motor Driver Ports.");
        Serial.println("*******************************************************");
        Reset_Outputs();
        FlashAlert();
        RestartESP();
    }
}

// ==================== SETUP ====================

void setup()
{
    delay(250);
    Serial.begin(115200);
    while (!Serial);
    Serial.println("\n=== WREN C5 - Stable Reliable ISR Version ===");

    Serial1.begin(9600, SERIAL_8N1, RXLP, TXLP);
    pinMode(ENLP, OUTPUT);
    digitalWrite(ENLP, HIGH);

    Wire.begin(I2C_SDA, I2C_SCL);
    if (!tca.begin()) { Serial.println("TCA not found!"); while(1); }
    Serial.println("TCA6408A Connected");

    tca.setPinMode8(0x00);
    tca.setPolarity8(0x00);
    Reset_Outputs();

    pinMode(IN_1A, INPUT_PULLDOWN);
    pinMode(IN_1B, INPUT_PULLDOWN);
    pinMode(IN_2A, INPUT_PULLDOWN);
    pinMode(IN_2B, INPUT_PULLDOWN);
    pinMode(EN1, INPUT);
    pinMode(EN2, INPUT);
    pinMode(SFLAG, INPUT_PULLDOWN);

    pinMode(LED_Blue, OUTPUT);
    digitalWrite(LED_Blue, LOW);

    attachInterrupt(digitalPinToInterrupt(IN_1A), inputISR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(IN_1B), inputISR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(IN_2A), inputISR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(IN_2B), inputISR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(EN1),   inputISR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(EN2),   inputISR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(SFLAG), inputISR, CHANGE);

    inputISR();

    Serial.println("Blue LED Heartbeat + Full Input/Fault Monitoring Active");
}

// ==================== LOOP ====================

void loop()
{
    FaultConditionCheck();

    // Reliable Heartbeat
    if (millis() - lastHeartbeat >= 500)
    {
        ledState = !ledState;
        digitalWrite(LED_Blue, ledState);
        lastHeartbeat = millis();
    }

    bool anyInputActive = IN_1A_State || IN_1B_State || IN_2A_State || IN_2B_State;

    if (anyInputActive)
    {
        tca.digitalWrite1(EN_1, HIGH);
        tca.digitalWrite1(EN_2, HIGH);

        if (IN_1A_State) tca.digitalWrite1(OUT_1A, HIGH);
        if (IN_1B_State) tca.digitalWrite1(OUT_1B, HIGH);
        if (IN_2A_State) tca.digitalWrite1(OUT_2A, HIGH);
        if (IN_2B_State) tca.digitalWrite1(OUT_2B, HIGH);

        Serial.printf("ACTIVE → 1A=%c 1B=%c 2A=%c 2B=%c | ADC=%.1fV\n",
                      IN_1A_State?'H':'L', IN_1B_State?'H':'L',
                      IN_2A_State?'H':'L', IN_2B_State?'H':'L', ADC_Voltage);
    }
    else
    {
        tca.digitalWrite1(OUT_1A, LOW);
        tca.digitalWrite1(OUT_1B, LOW);
        tca.digitalWrite1(OUT_2A, LOW);
        tca.digitalWrite1(OUT_2B, LOW);
    }

    delay(50);
}