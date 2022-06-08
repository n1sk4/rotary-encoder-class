# Rotary encoder

About
===========================
Basic steper rotary encoder with two interrupts.

*Original project: [Rotary encoder class](https://os.mbed.com/users/nikizg/code/RotaryEncoder/)*

Rotary encoder
===========================
This electronic component is used to sense the rotational movement that is converted into series of pulses.
There are two types of rotary encoders: Absolute and incremental. Absolute knows at which perticular angle 
it's set and the incremental can only add or subcract it's value that must be stored somewhere.
The class is based on an incremental type of rotary encoder that uses three pins for rotary movement and one for the switch.

Most of manufacturers have similar concept of incremental encoders, but this ReadMe file will focus on [KY-040 
datasheet from Handson Technology](http://www.handsontec.com/dataspecs/switches/Rotary%20Encoder.pdf)

Basic data:
- Operation voltage: 3.3V-5V DC
- Pulses per 360° rotation: 20
- Built in push button

KY-040 encoder form Handson Technology
--------------------------------------
![](https://os.mbed.com/media/uploads/nikizg/ky-40.png)

This image shows the pulses behavior of an incremental encoder
--------------------------------------------------------------
![](http://www.industrial-electronics.com/DAQ/images/10_110.jpg)

Code example
===========================
<pre>
  `#include "RotaryEncoder.h"`
 
  `RotaryEncoder re(p5, p6);                   // Default`
  `//RotaryEncoder re(p5, p6, PullDown);       // With pull mode specified`
  `//RotaryEncoder re(p5, p6, p7);             // With Switch`
  `//RotaryEncoder re(p5, p6, p7, PullDown);   // Switch + pull mode specified`
 
  `Serial pc(USBTX, USBRX);                    // Serial PC connection`
 
  `int main(){`
   `double value = re.Value;`
   `pc.printf("\nEncoder program started!");`
   `while(1){`
       `if(value!=re.Value){`
           `pc.printf("\nEncoder value is: %2.f", re.Value);`
           `value = re.Value;`
       `}`
       `wait_ms(1000);`
   `}`
  `}`
  </pre>
