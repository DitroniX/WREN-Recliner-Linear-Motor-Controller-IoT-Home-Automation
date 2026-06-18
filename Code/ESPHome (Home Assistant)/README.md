# WREN | ESP32-C5 Recliner Linear Motor Controller | IoT Home Automation

## **WREN C5 - ESPHome Example Code**

This is a working development code for WREN, within Home Assistant.

### **Code Development**

Being primarily a hardware engineer and not understanding YAML, I have enlisted some help.

Have used the help of GROK and ChatGPT in the process of understanding more on AI help and importantly ESPHome YAML.  Then after a number of iterations, learning and testing, I have formed a working 'wren-c5-esphome' code.

The important point of the code is to read the controller inputs, drive the motors and importantly recognise a fault condition.

### **Basic Examples**

During development, I took baby steps in understanding how YAML worked and how to integrate the various elements of the WREN board.   These examples have been included for your information, in the Basic Examples folder.

### **TCA6408A Driver**

Rather than continue development of a TCA6408A component, I have taken a lambda approach and created code within the YAML , which drives the GPIO Expander.  This makes is much easier - as a starting point, due to being self contained.

### **Required Editing**

The code should work as it is but you will ideally need to update the footer ESPHome API details, which I have xxxx out.

## Enable Home Assistant API
	api:
	  encryption:
	    key: "xxxx="

	ota:
	  - platform: esphome
	    password: "xxxx"

	wifi:
	  ssid: !secret wifi_ssid
	  password: !secret wifi_password

	  # Enable fallback hotspot (captive portal) in case wifi connection fails
	  ap:
	    ssid: "Wren-C5-Test Fallback Hotspot"
	    password: "xxxx"

## Documentation - WREN-C5 Motor Controller Firmware Overview

### Purpose

This firmware runs on the ESP32-C5 and provides control and monitoring for a dual-motor actuator system using a TCA6408A I²C GPIO expander and motor driver circuitry.

The firmware performs:

-   Dual motor direction control
    
-   Automatic enable control of motor drivers
    
-   Motor fault detection
    
-   Supply voltage monitoring
    
-   Temperature monitoring
    
-   Fault indication using a TCA6408A LED output
    
-   Automatic recovery via ESP restart
    
-   Wi-Fi telemetry through ESPHome

## Hardware Architecture

### ESP32-C5

The ESP32-C5 is the main controller and performs:

-   Input monitoring
    
-   Motor control logic
    
-   Fault detection
    
-   I²C communications
    
-   Sensor monitoring
    
-   ESPHome integration

### TCA6408A I/O Expander (I²C Address 0x21)

The TCA6408A provides eight output signals.

#### Output Mapping

Bit

Function

P0

EN1

P1

Motor 1 Extend

P2

Motor 1 Retract

P3

EN2

P4

Motor 2 Extend

P5

Motor 2 Retract

P6

Spare

P7

Status / Fault LED

The firmware configures all TCA6408A pins as outputs during boot.

## Motor Control Logic

###Motor Inputs

#### Motor 1

GPIO

Function

GPIO8

Motor 1 Extend

GPIO9

Motor 1 Retract

#### Motor 2

GPIO

Function

GPIO14

Motor 2 Extend

GPIO13

Motor 2 Retract

### Enable Logic

The motor driver enable signals are always controlled together.

When any motor command is active:

EN1 = HIGH

EN2 = HIGH

When no motor command is active:

EN1 = LOW

EN2 = LOW

This ensures both motor driver channels are enabled and disabled simultaneously.

### Direction Control

#### Motor 1

Input

Output

IN_1A

Extend

IN_1B

Retract

#### Motor 2

Input

Output

IN_2A

Extend

IN_2B

Retract

Outputs are updated continuously by the motor supervisor task.

# Fault Detection

The firmware contains multiple layers of fault detection.

### Motor Driver Fault (SFLAG)

#### Input

GPIO10

#### Behaviour

When SFLAG becomes active:

1.  All TCA outputs immediately go LOW
    
2.  EN1 goes LOW
    
3.  EN2 goes LOW
    
4.  All motor drive outputs go LOW
    
5.  Fault state is latched
    
6.  Fault LED flashes
    
7.  ESP32 automatically restarts
    

Detection methods:

-   GPIO interrupt (fastest)
    
-   Supervisor polling backup
    

This provides rapid fault response even if an interrupt is missed.

### Supply Voltage Protection

The ADC continuously monitors supply voltage.

#### Input

GPIO4

#### Limits

Condition

Action

<10 V

Fault

>48 V

Fault

On fault:

-   Motor outputs disabled
    
-   Fault LED flashes
    
-   System restarts
    
## Fault Indication

### TCA6408A LED

Bit 7 of the TCA6408A is used as the fault indicator.

#### Normal Operation

LED OFF

#### Fault Condition

LED flashes repeatedly

Pattern:

-   ON 100 ms
    
-   OFF 100 ms
    
-   Repeated 20 times
    

After flashing completes:

-   ESP restart occurs

## Heartbeat Indicator

ESP32 GPIO27 drives the onboard heartbeat LED.

Purpose:

-   Visual indication firmware is running
    
-   Visual indication scheduler is operating normally
    

Recommended pattern:

-   ON 750 ms
    
-   OFF 250 ms
    
## Sensor Monitoring

### TMP102 Temperature Sensor

I²C Address: 0x4A

Provides:

-   Board temperature
    
-   Thermal monitoring
    
-   Home Assistant reporting
    
### Supply Voltage

ADC input:

GPIO4

Voltage divider scaling:

44.4444

Provides:

-   Input voltage monitoring
    
-   Fault detection
    
-   Telemetry
    
### Wi-Fi RSSI

Reports wireless signal strength for diagnostics.

### Uptime

Reports controller runtime.

# Startup Sequence

1.  ESP32 boots
    
2.  TCA6408A initialized
    
3.  All outputs forced LOW
    
4.  TCA polarity register configured
    
5.  TCA direction register configured
    
6.  Fault state cleared
    
7.  SFLAG checked
    
8.  Normal operation begins
    

If SFLAG is already active during boot:

-   Fault handler executes immediately
    
-   Motors remain disabled
    
-   LED flashes
    
-   ESP restarts
    
## Safety Features

The firmware implements several safety mechanisms:

#### Immediate Motor Shutdown

Any detected fault immediately writes:

Output Register = 0x00

This disables:

-   EN1
    
-   EN2
    
-   Motor 1 outputs
    
-   Motor 2 outputs
    
#### Fault Latching

Once a fault occurs:

fault_active = true

Motor outputs remain disabled until restart.

#### Automatic Recovery

After fault indication:

esp_restart()

is executed to restore the system to a known state.


## Timing Parameters

Function

Interval

Heartbeat LED

1 second

Motor Supervisor

10 ms

Voltage Update

1 second

TMP102 Update

10 seconds

Wi-Fi RSSI

60 seconds

## Summary

The WREN-C5 firmware provides a robust dual-motor control platform with:

-   Dual motor direction control
    
-   Shared driver enable control
    
-   Immediate fault shutdown
    
-   Voltage protection
    
-   Thermal monitoring
    
-   Fault LED indication
    
-   Automatic recovery
    
-   ESPHome integration
    
-   I²C-based output expansion
    

The design prioritizes safe motor shutdown and automatic recovery while maintaining simple integration with Home Assistant and ESPHome.

## **Open Source**
 
  This test code is OPEN SOURCE and formatted for easier viewing.  Although is is not intended for real world use, it may be freely used, or modified as needed.
  It is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

## **Further Information**

Additional information, and other technical details on this project, maybe found in the related repository pages.

**Repository Folders**

 - **Code** *(Code examples for Arduino  IDE, Raspberry Pi and PlatformIO)*
 -  **Datasheets and Information** *(Component Datasheets, Schematics, Board Layouts, Photos, Technical Documentation)*
 - **Certification** *(Related Repository Project or Part, Certification Information)*

**Repository Tabs**

 - **Wiki** *(Related Repository Wiki pages and Technical User Information)*
 - **Discussions** *(Related Repository User Discussion Forum)*
 - **Issues** *(Related Repository Technical Issues and Fixes)*

***

We value our Customers, Users of our designs and STEM Communities, all over the World . Should you have any other questions, or feedback to share to others, please feel free to:

* Visit the related [Project](https://github.com/DitroniX?tab=repositories) *plus the related* **Discussions** and **Wiki** Pages.  See tab in each separate repository.
* **Project Community Information** can be found at https://www.hackster.io/DitroniX
* [DitroniX.net Website - Contact Us](https://ditronix.net/contact/)
* **Twitter**: [https://twitter.com/DitroniX](https://twitter.com/DitroniX)
* [Supporting the STEM Projects - BuyMeACoffee](https://www.buymeacoffee.com/DitroniX)
*  **LinkedIN**: [https://www.linkedin.com/in/g8puo/](https://www.linkedin.com/in/g8puo/)

***Dave Williams, Maidstone, UK.***

Electronics Engineer | Software Developer | R&D Support | RF Engineering | Product Certification and Testing | STEM Ambassador

## STEM

**Supporting [STEM Learning](https://www.stem.org.uk/)**

Life is one long exciting learning curve, help others by setting the seed to knowledge.

![DitroniX Supporting STEM](https://hackster.imgix.net/uploads/attachments/1606838/stem_ambassador_-_100_volunteer_badge_edxfxlrfbc1_bjdqharfoe1_xbqi2KUcri.png?auto=compress%2Cformat&w=540&fit=max)

