# WREN | ESP32-C5 Recliner Linear Motor Controller | IoT Home Automation
**Supporting STEM Electronic Internet of Things & Home Automation Technology for Smart Energy Monitoring**

[![DitroniX WiKi Pages](https://github.com/DitroniX/WREN-Recliner-Linear-Motor-Controller-IoT-Home-Automation/blob/main/Datasheets%20and%20Information/GitHub%20WiKi.png?raw=true)](https://github.com/DitroniX/WREN-Recliner-Linear-Motor-Controller-IoT-Home-Automation/wiki)

[**For Latest Project Updates - Click Here**](https://github.com/DitroniX/WREN-Recliner-Linear-Motor-Controller-IoT-Home-Automation/blob/main/README.md#updates)

## Welcome to WREN

**WREN**, is a compact, Linear Motor Controller Board which can be easily integrated into IoT Home or Industrial Automation systems, via 2.4 GHz, or 5 GHz Wi-Fi.

The design is in operation around the World and is straight forward to install.

Home or Industrial Automation, IOT control, could be local, or cloud based, to suite the users needs.

The on-board ESP32-C5 enables use of Standard Arduino Code, Platform IO, ESPHome etc.

Full Electronic Control, with Safety Hardware Lockouts (not using Relays).

![WREN Overview](https://github.com/DitroniX/WREN-Recliner-Linear-Motor-Controller-IoT-Home-Automation/blob/main/Datasheets%20and%20Information/WREN%20-%20Overview.png)

### What does WREN Control?

**WREN** controls Linear Motors, which are typically used to raise/lower, Electric Recliners and Beds, or open/close Window Vents on Greenhouses.

Example Linear Motor Kit can be [found here](https://github.com/DitroniX/WREN-Recliner-Linear-Motor-Controller-IoT-Home-Automation/wiki/Linear-Motor-Kit)

## Top Level Features

The **WREN** SDK board:

 - Is designed to easily, and safely, retrofit (plug and play), to industry standard Electric Reclining Chairs.
 - Allows continued use of any existing push buttons, or remote hand controller, through isolated input and outputs.
 - Enables simultaneous electrical control from Smart Home Automation.
 - Includes electronic [Hardware Safety Lockout](https://github.com/DitroniX/WREN-Recliner-Linear-Motor-Controller-IoT-Home-Automation/wiki/Bench-Safety-Circuit-Testing) and Shutdown.
 - Designed for standard 5 Pin DIN connections, typically used for Electric Recliners
 - Although most chairs operate at 24 V DC, **WREN** could be used on systems from 9V to 48V DC.
 - The **WREN** Dual Linear Motors Controller can be internally linked to provide increased single motor current control - heavy duty.
 - RS485 Interface for chaining controllers, such as Home Cinemas.

![WREN Comparison](https://github.com/DitroniX/WREN-Recliner-Linear-Motor-Controller-IoT-Home-Automation/blob/main/Datasheets%20and%20Information/WREN%20Comparison%20Diagram.jpg)
 
### Dual Control

**WREN** provides two independent Linear Motor controllers, all on one board and via one cable.

Depending on how many linear motors are fitted to the Electric Reclining Chair, the dual control option is able to facilitate both options.

## Typical Uses

 **WREN** was primarily designed for Electric Reclining Chairs but not limited to just these.

The standard Electric Reclining Chairs, have a Single Linear Motor, which allows for the expected reclining functions.

### Mobility

More advanced Electric Reclining Chairs, have Dual Linear Motors, often called 'Lift and Recline'.  These are typically used to aid mobility.

This additional Linear Motor maybe used to;

 - Tilt Forward, to aid mobility to get out of the chair
 - Back Rests or Foot Rests to move independently.
 - Massage Options

### Other Uses
 - Can be used to control a range of Linear Motors:
	 - Electric Recliner Chair
	 - Home Cinema Recliner
	 - Electric Recliner Bed
	 - Greenhouse Vent Windows
	 - Solar Panels, Tilting and Sun Tracking
	 - Stage Automation
	 - Animal Flaps
	 - Optical Tracking
	 - Robotics
 - Can be adapted for use on 8 Pin DIN connections, typically used for Electric Beds

## Physical Control

Electric Recliners typically have buttons on the side of the chair.   In addition, some have extension cables which attach a remote hand control, to aid mobility and easy of use.

**WREN** is designed to easily and transparently interface to either option.

When integrated with Home Automation with Voice Control, this could be used to control **WREN**, just like turning on and off lights, or opening and closing curtains.

## Power

Power is taken from the [existing 5 Pin DIN connector](https://github.com/DitroniX/WREN-Recliner-Linear-Motor-Controller-IoT-Home-Automation/wiki/Electric-Recliner-Chair-Connector).  This typically is 24V DC.

**WREN** could be used on systems from 9V to 48V DC.

## Connections

Installation of a **WREN** is normally simply by placing the **WREN** inline with an existing 5 Pin DIN connector, under the chair. for the majority of chairs, this can be mostly 'plug and play' approach.

Example connections are [shown here](https://github.com/DitroniX/WREN-Recliner-Linear-Motor-Controller-IoT-Home-Automation/wiki/WREN-DIN-Connections)

## WREN C5

The latest release of **WREN** includes:

 - ESP32-C5 (2.4 GHz and 5 GHz Wi-Fi)
 - RS485 Interface (Allowing Groups of Chairs to Communicate)
 - USB Type C UART Interface (Easier Code Development and Firmware Flashing)
 - Increased on-board Voltage Power Supply to facilitate up to 52V Linear Motors.

## Origins

Original WREN 12S SDK V2

![Display-Type-B](https://github.com/DitroniX/WREN-Recliner-Linear-Motor-Controller/blob/main/Datasheets%20and%20Information/WREN%2012S%20SDK%20V2%20Component%20Overview.jpg?raw=true)


## Updates


-   26-Apr - WREN C5 Prototyping and Testing
-   26-Mar - WREN C5 Research & Development, Design
-   21-Sep - WREN 12S V2.03 Released
-   21-Jun - WREN 12S (V2) Released
-   21-Apr - WREN 12S (V2) Development and Testing
-   20-May- Harvey's Version Released
-   20-Mar- WREN V1 Released
-   20-Feb - Prototyping and Testing
-   19-Nov  - Preview Design Released
-   19-Oct  - Concept Research & Development



## **Further Information**

Additional information, and other technical details on this project, maybe found in the related repository pages.

**Repository Folders**

 - **Code** *(Code examples for Arduino  IDE and PlatformIO)*
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
Dave Williams | G8PUO | DitroniX 1981-2024 | ditronix.net
