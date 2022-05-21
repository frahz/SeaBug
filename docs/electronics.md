# Electronics

This document file will be going over the electronics circuits used within this project.

## Theory

The ultrasonic sensors that were used for this project were the [Maxbotix MB7076](https://www.maxbotix.com/documents/XL-MaxSonar-WR_Datasheet.pdf). The transmitter doesn't need much setup, while the receiver needs pin 4 pulled down (meaning connected to ground).

![](/assets/sensor_output.png)

In the above image, we can see the signal that we have to analyze.

## Receiver Circuit

For the receiver, we needed to build a circuit that can amplify the signal, convert the signal from AC to DC, and use a voltage regulator to restrict the voltage around 5V.

Therefore, we first run the signal through a differentiator so that any constant signal is 0V, then we have a two-stage amplifier, with the first amplifier having a gain of 23.9 and the second amplifier having a gain of 31.9 for a total gain of 762.4. After we using a diode rectifier to convert the signal to from AC to DC and then run it through a voltage regulator that limits the max voltage to 5, and last we connect the output of the voltage regulator to the gate of a MOSFET so that it can act as a switch to work with the microcontroller.

In the `assets` folder there is a file called `receiver.fzz` that has the circuit schematics, which can be edited with [Fritzing](https://fritzing.org/).

![](/assets/circuit.png)

Above, we see the circuit schematic which shows the basic layout of the receiver circuit.

![](/assets/circuit_irl.jpg)

The above picture shows the circuit in our testing environment. We connect the output of the MOSFET to pin 3 of the microcontroller, which will then wake up the microcontroller when a signal is received and activate both servo motors.

## Transmitter Circuit

For the transmitter, we just need a battery to power up the sensor. It means that we connect the positive end of the battery to V+ on the MB7076 sensor and connect the negative end of the battery to GND on the MB7076 Sensor.
