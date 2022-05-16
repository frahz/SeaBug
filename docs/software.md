# Software

This document file will be describing the each part of the source code in [src/main.cpp](/src/main.cpp).

## Source Code

### Libraries

First, we start with the included libraries for this project.

```cpp
#include <Arduino.h>
#include <Servo.h>
#include <avr/sleep.h>
#include "LowPower.h"
```

We start with `Arduino.h`, which is a necessary library that includes all the useful functions/types that come with the Arduino platform.

Then, we have `Servo.h`, which allows the board to control multiple servo motors.

Last, we have `avr/sleep.h` and `LowPower.h`, which are the libraries that allow us to put the microcontroller to sleep and turn off other parts of the board(like the ADC or the BOD).

### Defines

Now we go ahead and define the pins for each of the components used.

```cpp
#define button 3
#define led1 5
```

We set `button` to pin `3`, which is the pin that wakes up the microcontroller from deep sleep. Then `led1` is set to pin `5`, which is primarily used for debug purposes so that we can tell whether our interrupt worked correctly.

```cpp
Servo motor_1;
Servo motor_2;
const int init_pos = 0;
const int final_pos = 90;
```

Here, we define both Servo objects, `motor_1` and `motor_2`, which are the ones that control the position of our servo motors. We set the initial position of the servo motors to `0` with `const int init_pos = 0`. Then, we have `const int final_pos = 90`, which has the position to which we rotate the servo motors that opens up the buoy container.

### Setup

This is the function where we initialize all our pins(input/output), which looks as follows.

```cpp
void setup()
{
...
}
```

We'll first go over the pin modes and then initialization of the servo motors.

```cpp
pinMode(led1, OUTPUT);
pinMode(button, INPUT_PULLUP);
```

We start by setting the `pinMode` for `led1` and `button`, we set `led1` to `OUTPUT` and we set the `button` to `INPUT_PULLUP`, meaning that we have an input pin that is effectively inverted, where `HIGH` means the button is off, and `LOW` means that the sensor is on.

```cpp
motor_1.write(init_pos);
motor_1.attach(9);

motor_2.write(init_pos);
motor_2.attach(10);
```

We set both `motor_1` and `motor_2` to their initial position and attach their corresponding pins, pin `9` for `motor_1` and pin `10` for `motor_2`.

```cpp
digitalWrite(led1, HIGH);
```

The last line within the `setup` function just initializes `led1` to a `HIGH` state, meaning that it the LED will be turned on during startup.

### Loop

For the `loop` function there's not much to go over.

```cpp
void loop()
{
    delay(2000);
    go_sleep();
}
```

we put a `delay` of `2` seconds before calling the `go_sleep()` function.

### `go_sleep` function

This function is the one that attaches an interrupt to pin `3` that calls the function `wake_up()` and puts the microcontroller to sleep forever.

```cpp
void go_sleep()
{
    attachInterrupt(1, wake_up, LOW); // attach interrupt to pin d3
    digitalWrite(led1, LOW);          // turn led off
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
    digitalWrite(led1, HIGH); // turn led on
}
```

We first start with:

```cpp
attachInterrupt(1, wake_up, LOW);
```

Which attaches an interrupt to the pin with the corresponding interrupt number `1`, in our case that interrupt number corresponds to pin `3` in our microcontroller. Then we pass a function as the second parameter, for us that function is `wake_up()`. Finally, the last parameter that we pass to the function is `LOW`, which is the mode that defines when the interrupt will trigger, in our case the interrupt is triggered whenever the pin is `LOW`. More information regarding this function can be found [here](https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/).

Then `digitalWrite(led1, LOW);`, which is used to turn off the LED, which notifies us that the microcontroller has gone to sleep.

```cpp
LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
```

This function puts the microcontroller into a power down state, which the lowest current consumption state. This is meant to together with an external pin interrupt to wake up. `SLEEP_FOREVER` as the first parameter means that we the microcontroller is asleep and won't be woken up by the Watchdog Timer. The second and third parameters `ADC_OFF` and `BOD_OFF` turn off the ADC module and the Brown Out Detector (BOD).

```cpp
digitalWrite(led1, HIGH);
```

This last line will run after the microcontroller wakes up, which then turns on the LED.

### `wake_up` function

This function executes the code after the microcontroller wakes up.

```cpp
void wake_up()
{
    motor_1.write(final_pos);
    motor_2.write(final_pos);

    sleep_disable();

    detachInterrupt(1);
}
```

We move both `motor_1` and `motor_2` to their final position, then use the `sleep_disable()` function to disable the sleep mode, and detach the interrupt from pin `3`. This is done to prevent and endless loop situation.
