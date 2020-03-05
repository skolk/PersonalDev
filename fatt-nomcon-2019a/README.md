# fob-all-the-things
access management for maker spaces

Fob all the things (known as FATT) has the goal of of creating an open source package of hardware and software to allow maker spaces and community groups to install access points with minimal hardware and coding knowlege (nothing outside of a terminal command prompt)
***

***
#Directory
-Status
-History
-Resources
-Outline
-BOM
-Version History

# Status
FATT is currently in the process of undergoing a define freeze, Dev kit push, and Software synchronization:

## Current Asks
-Create Hardware version number
-Define Software Scope and Create version with in bounds
-Create Software Package
-Produce 'plug and play' package in as MVP (POC has been established at Nom Com).
-create a working MVP remake

## Where this project is now:
FATT is active in X maker spaces running slightly different frameworks and hardware.

## Where we want to go:



# History
FATT was conceived when maker spaces realized they were continually re-inventing the wheel to sove the same problem; groups would consistently get to the same point; have the same frustrations, and either crash and burn or move on to a proprietary system.

at Nomcon 2019; Ace Monster Toys created a presentation to demonstrate their progress on with FATT and created a working group in slack, landing website page, and several git repos.

***
#Resources

[Ace Monster Toys presentation](https://www.acemonstertoys.org/fatt-at-nomcon/)
[slide presentation](https://docs.google.com/presentation/d/1t7AaRWNNl93JGzS-Eg19WnUrunBbh1UaYufZjOnOvw4/edit#slide=id.p)
[A landing page](https://foballthethings.org/ ) where you can order dev kits
[The 2019 working version for the presentation](https://github.com/acemonstertoys/fatt-nomcon-2019)
[Nom Com Dashboard](https://nomcon.foballthethings.org/)  
[wiki organizing](https://www.makerhappen.org/fatt)
[Join the Slack](https://fatt-slack-auth.herokuapp.com/)
[DanDudes version](https://github.com/DanDude0/MakerAccessControl)
[Milwaukee Maker Space](https://github.com/DanDude0/MilwaukeeMakerspacePiFobReader)

***
# Outline
The FATT framework's design intent is to be a platform to allow different code bases, hardware, and oversight for communities to grant access and track user resources; this is determined by establishing core use cases; divergent points, and convergence points.

For instance it is a goal of FATT to have third party and local database access. (such as AWS vs a local RaspberryPi)

## Hardware:
At the core of FATT is the key fob, a RFID tag that communicates with a RFID reader easily connected to a USB into a Raspberry Pi 3B. The Fob is core to the system, how everything else happens is to support the space ensuring that the system is reliable and secure.

## Software
The local Raspberry pi's job is to interface with the RFID, check if the resource has permissions and then recored the request. The Acess point must store it's database either locally or remotly; and check the database. CUrrently the systme is set up to ping the data base every 100ms to ensure up to date resources.

## Backend
The user database and permissions can either be accessed via ssh on or held remortly in a systme such as AWS, Microsoft Azure, or some thing else. The Goal of this project is to be a good pipe. How that data based system is updated (apercot?)


## Admin interface
Apercot

#Existing BOM for DEV Kit:

| |
| - | - | - | - |
| Part | Quantity | Cost | Url |
Raspberry Pi 3B |	1	| $35.00 |	https://www.amazon.com/Raspberry-Pi-RASPBERRYPI3-MODB-1GB-Model-Motherboard/dp/B01CD5VC92		|

W26 Keypad and Fob Reader	1	$17.00	https://www.ebay.com/itm/253914832726?ViewItem=&item=253914832726		
3.5" Pi Screen	1	$10.70	https://www.aliexpress.com/item/Free-shipping-LCD-module-Pi-TFT-3-5-inch-320-480-Touchscreen-Display-Module-TFT-for/32233522592.html?spm=a2g0s.9042311.0.0.23a64c4dsTdPvz		
Class 10 Micro SD Card	1	$5.00	https://www.amazon.com/gp/product/B013P27MDW/ref=oh_aui_detailpage_o01_s00?ie=UTF8&psc=1		
Custom Circuit Board	1	$1.50	https://easyeda.com/Dan_Dude/Pi-Fob-Reader		
Stackable Pi Header	1	$0.98	https://www.aliexpress.com/item/10pcs-2-54mm-2x20-40pin-Double-Row-Female-stackable-Straight-Header-socket-Strip/32547061274.html?spm=a2g0s.9042311.0.0.23a64c4dsTdPvz		
2 Channel Relay Module	1	$0.92	https://www.aliexpress.com/item/Free-shipping-2pcs-2-Channel-5V-Relay-Module-for-PIC-ARM-DSP-AVR-For-arduino/725491095.html		
DC-DC Converter	1	$0.58	https://www.aliexpress.com/item/Mini-DC-DC-12-24V-To-5V-3A-Step-Down-Power-Supply-Module-Buck-Converter-Adjustable/32770347590.html?spm=a2g0s.9042311.0.0.23a64c4dsTdPvz		
Misc Dupont Connectors	3	$0.40	https://www.aliexpress.com/item/620Pcs-Dupont-Connector-2-54mm-Dupont-Cable-Jumper-Wire-Pin-Header-Housing-Kit-Male-Crimp-Pins/32884911697.html?spm=a2g0s.9042311.0.0.27424c4dITWRS8		
KF2510 2P Connector	1	$0.11	https://www.aliexpress.com/item/50PCS-KF2510-2P-2-54mm-Pin-Header-Terminal-Housing-Connector-Kit-KF2510-2P/32826768676.html?spm=a2g0s.9042311.0.0.23a64c4dsTdPvz		
8V to 14V Wall Wart	1	$0.00	Free (Hack Rack)		
1x6 Pin Header	2	$0.00	Free (Hack Rack)		
1x4 Pin Header	1	$0.00	Free (Hack Rack)		
2.7K Resistors	6	$0.00	Free (Hack Rack)		
10K Resistors	2	$0.00	Free (Hack Rack)		
NPN Transistors (2222A, etc. . .)	6	$0.00	Free (Hack Rack)		



***
