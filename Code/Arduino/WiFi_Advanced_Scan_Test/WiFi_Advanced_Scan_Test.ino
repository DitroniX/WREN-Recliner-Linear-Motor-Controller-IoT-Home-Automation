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
#include "WiFi.h"

// ****************  VARIABLES / DEFINES / STATIC ****************

// Return Some Meaningful Information From RSSI
String RSSI_Info(int RSSI_Value) {
  switch (-RSSI_Value)  // Inverted dBm Level ;)
  {
    {
      case 0 ... 30:
        return "Signal Very Strong";
        break;
      case 31 ... 50:
        return "Signal Excellent";
        break;
      case 51 ... 60:
        return "Signal Healthy";
        break;
      case 61 ... 70:
        return "Signal Very Good";
        break;
      case 71 ... 80:
        return "Signal Good";
        break;
      case 81 ... 90:
        return "Signal Poor - Try Moving Position";
        break;
      case 91 ... 100:
        return "Signal Very Low! - Move Position";
        break;
      default:
        return "No Signal :(";
        break;
    }
  }

}  // RSSI_Info

void setup() {

  // Stabalise
  delay(250);

  // Initialize UART:
  Serial.begin(115200, SERIAL_8N1);  //115200
  while (!Serial)
    ;

  // Enable Station mode
  WiFi.STA.begin();
  // Or classic way: WiFi.mode(WIFI_STA); WiFi.disconnect();

  Serial.println("WREN Bring Up and Test Example Code");
}

void scanWiFi(const char* title) {
  Serial.printf("\n--- %s ---\n", title);
  Serial.println("Scan start...");

  int n = WiFi.scanNetworks();  // Returns number of networks found

  Serial.printf("Scan done: %d networks found\n", n);

  if (n == 0) {
    Serial.println("No networks found.");
  } else {
    Serial.println("Nr | SSID                             | RSSI  | CH | Encryption");
    Serial.println("---------------------------------------------------------------");

    for (int i = 0; i < n; ++i) {
      Serial.printf("%2d | %-32.32s | %4d | %2d | ",
                    i + 1,
                    WiFi.SSID(i).c_str(),
                    WiFi.RSSI(i),
                    WiFi.channel(i));

      switch (WiFi.encryptionType(i)) {
        case WIFI_AUTH_OPEN:          Serial.print("Open"); break;
        case WIFI_AUTH_WEP:           Serial.print("WEP"); break;
        case WIFI_AUTH_WPA_PSK:       Serial.print("WPA"); break;
        case WIFI_AUTH_WPA2_PSK:      Serial.print("WPA2"); break;
        case WIFI_AUTH_WPA_WPA2_PSK:  Serial.print("WPA+WPA2"); break;
        case WIFI_AUTH_WPA2_ENTERPRISE: Serial.print("WPA2-Enterprise"); break;
        case WIFI_AUTH_WPA3_PSK:      Serial.print("WPA3"); break;
        case WIFI_AUTH_WPA2_WPA3_PSK: Serial.print("WPA2+WPA3"); break;
        case WIFI_AUTH_WAPI_PSK:      Serial.print("WAPI"); break;
        default:                      Serial.print("Unknown"); break;
      }
      Serial.println();
      delay(10);
    }
  }

  WiFi.scanDelete();  // Free memory
}

void loop() {
  // Default / Auto band scan
  scanWiFi("Default / Auto Band Scan");

#if CONFIG_SOC_WIFI_SUPPORT_5G
  delay(2000);
  WiFi.setBandMode(WIFI_BAND_MODE_2G_ONLY);
  scanWiFi("2.4 GHz Only");

  delay(2000);
  WiFi.setBandMode(WIFI_BAND_MODE_5G_ONLY);
  scanWiFi("5 GHz Only");
#endif

  delay(10000);  // Scan every 10 seconds
}