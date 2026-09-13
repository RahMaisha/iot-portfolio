# IoT Projects

Embedded and networking projects built on Arduino and the ESP8266 (NodeMCU), covering sensors, serial communication, mesh networking, and a comparison of IoT application protocols. Coursework for CSE 406 at East West University.

## Projects

### [Water level detection](./lab-01-02-water-level-sensor)
Analogue water sensor read on an Arduino, with calibrated thresholds driving three indicator LEDs for low, medium and high water level.

`Arduino` `analogue sensor`

### [UART communication between two NodeMCUs](./lab-03-uart-communication)
Two ESP8266 boards exchanging data over a UART serial link, one acting as master and one as slave. The [stress-test](./lab-03-uart-communication/stress-test) folder pushes the link harder and captures the serial output for analysis.

`ESP8266` `UART` `serial`

### [Mesh networking with painlessMesh](./lab-04-mesh-networking)
A self-organising mesh of ESP8266 nodes using the painlessMesh library, where devices talk directly to each other without a central router. Built up across four tasks: printing node IDs, base broadcast, targeted sending, and a serial-driven target.

`ESP8266` `painlessMesh` `mesh networking`

### [Comparing HTTP, CoAP and MQTT](./lab-05-protocol-comparison)
A CoAP server running on the ESP8266 with a Python client, used to compare the behaviour of HTTP, CoAP and MQTT for constrained devices.

`ESP8266` `CoAP` `MQTT` `Python`

## Hardware

Arduino Uno, NodeMCU ESP8266 boards, and an analogue water level sensor.

## Layout

Each folder holds the sketches for one project. Files ending in `.ino` are Arduino sketches; `.txt` files are captured serial or terminal output from the runs.
# IoT Projects Portfolio 
 
A collection of Internet of Things projects exploring various sensors, communication protocols, and embedded systems. 
 
## Projects 
 
### [Water Level Detection](./IOT-Water-Level-Detection) 
IoT system for monitoring and detecting water levels using sensors. 
 
### [Basic Water Sensor with Arduino](./IOT_WaterSensor_with_Arduinu_Basic) 
Fundamental water sensing implementation using Arduino. 
 
### [NodeMCU UART Communication](./Communication-between-two-NodeMCU-ESP8266-using-UART-interface) 
Implementing UART interface communication between two ESP8266 NodeMCU devices. 
 
### [CSE 406 Lab 3](./CSE_406_LAB03) 
Academic lab work focusing on IoT concepts and implementations. 
 
### [Mesh Networking with NodeMCU](./Mesh-Networking-with-NodeMCU-ESP8266-and-painlessMesh) 
Creating mesh networks using ESP8266 and painlessMesh library. 
 
### [IoT Protocol Comparison](./Comparing-HTTP-CoAP-and-MQTT-Protocols-with-ESP8266) 
Comparative study of HTTP, CoAP, and MQTT protocols using ESP8266. 
