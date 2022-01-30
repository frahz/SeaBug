#include <Arduino.h>
#include <avr/sleep.h>

#define button 3
#define led1 5

void wakeUp();
void go_sleep();

void setup()
{
    Serial.begin(9600);
    pinMode(led1, OUTPUT);
    pinMode(button, INPUT);

    digitalWrite(led1, HIGH);
}

void loop()
{
    delay(500);

    // go_sleep();
}

void go_sleep()
{
    sleep_enable();                      // enable sleep
    attachInterrupt(1, wakeUp, LOW);     // attach interrupt to pin d3
    set_sleep_mode(SLEEP_MODE_PWR_DOWN); // set sleep mode to full sleep
    digitalWrite(led1, LOW);             // turn led off
    delay(1000);                         // wait second before going to sleep
    sleep_cpu();                         // activate sleep mode
    Serial.println("Woke up!");          // execute after interrupt
    digitalWrite(led1, HIGH);            // turn led on
}
void wakeUp()
{
    Serial.println("Interrupt activated");
    sleep_disable();    // disable sleep mode
    detachInterrupt(1); // removes the interrupt from pin d3
}