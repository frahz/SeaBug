#include <Arduino.h>
#include <Servo.h>
#include <avr/sleep.h>
#include "LowPower.h"

#define button 3
#define led1 5

// Servo motors for opening the buoy containers
Servo motor_1;
Servo motor_2;
int pos = 90;

void wakeUp();
void go_sleep();

void setup()
{
    // Serial.begin(9600);
    pinMode(led1, OUTPUT);
    pinMode(button, INPUT_PULLUP);

    motor_1.write(0);
    motor_1.attach(9);

    motor_2.write(0);
    motor_2.attach(10);

    digitalWrite(led1, HIGH);
}

void loop()
{
    delay(2000);
    go_sleep();
}

void go_sleep()
{
    attachInterrupt(1, wakeUp, LOW); // attach interrupt to pin d3
    digitalWrite(led1, LOW);         // turn led off
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
    // Serial.println("Woke up!"); // execute after interrupt
    digitalWrite(led1, HIGH); // turn led on
}
void wakeUp()
{
    // tell servo to go to position in variable 'pos'
    motor_1.write(pos);
    motor_2.write(pos);

    sleep_disable(); // disable sleep mode

    detachInterrupt(1); // removes the interrupt from pin d3
}