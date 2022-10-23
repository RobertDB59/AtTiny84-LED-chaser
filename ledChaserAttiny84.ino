/*        LED chaser for taillight bike, e-bike, scooter...

   This program creates a running light which is more visible than a steady ON light.
   A stock taillight had a PIC controller that started on the push of a button on the back of the taillight.
   Since mine is switched from the handlebar this was not an option for my use.
   It contained five different patterns, all leds steady on, all leds flashing, leds chasing
   from left to right, leds chasing from right to left and a sort of chasing, left and right half simulaneously,
   in "optical" circels.
   I needed only one pattern, so I re-created the last pattern.
   Since it does not do anything else but blinking some leds I did not bother to write the code without delays.


       Attiny84 pin connect      original PIC pin connect
              --_--                      --_--
       VCC  o|     |o  GND        D7   o|     |o  D5
       D7   o|     |o  D5         D8   o|     |o  D4
       D8   o|     |o  D4         D9   o|     |o  D3
            o|     |o  D3         VCC  o|     |o  GND
       D9   o|     |o  D2         D6   o|     |o  D2
       D6   o|     |o  D1         D10  o|     |o  D1
       D10  o|     |o  D11             o|     |o  D11
              -----                      -----

               LED layout taillight
            D4  D3  D2  D1  D6  D9  D8
        D5                              D7
          D11                        D10

   LICENCE
   Copyright October 2022 Robert de Beer

   Licensed under the Apache License, Version 2.0 ( the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at:

     http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

   For an AtTiny84:
      program uses 1090 ( 13%) bytes program storage space
      variables use  35 (  6%) bytes of dynamic memory
*/

int pinArray[] = {6, 7, 8, 9, 10, 5, 6, 3, 2, 1, 0, 4}; // array that holds the port numbers
int stepNumber = 0;

unsigned long stepInterval = 70;


void setup() {
  for(stepNumber = 0; stepNumber < 12; stepNumber++) {
    pinMode(pinArray[stepNumber], OUTPUT);
    digitalWrite(pinArray[stepNumber], 1);              // the anode of the LED is connected to VCC
                                                        // this is to turn all leds OFF
  }

  delay(5 * stepInterval);

  for(stepNumber = 0; stepNumber < 6; stepNumber++) {   // all leds on from center to edge
    digitalWrite(pinArray[stepNumber], 0);
    digitalWrite(pinArray[stepNumber + 6], 0);
    delay(stepInterval);
  }

  delay(5 * stepInterval);

  for(stepNumber = 0; stepNumber < 6; stepNumber++) {   // all leds off from center to edge
    digitalWrite(pinArray[stepNumber], 1);
    digitalWrite(pinArray[stepNumber + 6], 1);
    delay(stepInterval);
  }

  delay(10 * stepInterval);
}


void loop() {
  for(stepNumber = 0; stepNumber < 6; stepNumber++) {   // the pattern to run all the time
    digitalWrite(pinArray[stepNumber], 0);
    digitalWrite(pinArray[stepNumber + 6], 0);
    delay(stepInterval);
    digitalWrite(pinArray[stepNumber], 1);
    digitalWrite(pinArray[stepNumber + 6], 1);
    delay(stepInterval);
  }
}
