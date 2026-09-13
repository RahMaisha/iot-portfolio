# IoT Projects

Embedded and networking projects built on Arduino and the ESP8266 (NodeMCU), covering sensors, serial communication, mesh networking, and a comparison of IoT application protocols. Coursework for CSE 406 at East West University.

## Projects

### [Water level detection](./lab-01-02-water-level-sensor)
Analogue water sensor read on an Arduino, with calibrated thresholds driving three indicator LEDs for low, medium and high water level.

### [UART communication between two NodeMCUs](./lab-03-uart-communication)
Two ESP8266 boards exchanging data over a UART serial link, one acting as master and one as slave. The [stress-test](./lab-03-uart-communication/stress-test) folder pushes the link harder and captures the serial output for analysis.

### [Mesh networking with painlessMesh](./lab-04-mesh-networking)
A self-organising mesh of ESP8266 nodes using the painlessMesh library, where devices talk directly to each other without a central router. Built up across four tasks: printing node IDs, base broadcast, targeted sending, and a serial-driven target.

### [Comparing HTTP, CoAP and MQTT](./lab-05-protocol-comparison)
A CoAP server running on the ESP8266 with a Python client, used to compare the behaviour of HTTP, CoAP and MQTT for constrained devices.

## Hardware

Arduino Uno, NodeMCU ESP8266 boards, and an analogue water level sensor.

## Layout

Each folder holds the sketches for one project. Files ending in `.ino` are Arduino sketches; `.txt` files are captured serial or terminal output from the runs.
