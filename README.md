# Rotary encoder

About
===========================
This class was created for use with fast prototyping with Mbed platform in mind
and the target microcontroller was NXP LPC1768.
Basic steper rotary encoder with two interrupts.

*Original project: [Rotary encoder class](https://os.mbed.com/users/nikizg/code/RotaryEncoder/)*

Rotary encoder
===========================
This electro-mechanic component is used to sense the rotational movement that is converted into series of pulses.
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

* **DT**  - Pin A  (*Digital input with interrupt*)
* **CLK** - Pin B (*Digital input*)
* **SW**  - Pin SW (*Digital input*)
* **+**   - 3.3V DC
* **GND** - GND


Working principles of an rotary incremental encoder
--------------------------------------------------------------
![](https://ars.els-cdn.com/content/image/3-s2.0-B9780124201651000214-f21-08-9780124201651.jpg)

*The relative phase of the A and B pulses determines whether the encoder is rotating clockwise or counterclockwise. A rising edge on B after a rising edge on A means the encoder is rotating one way, and a rising edge on B after a falling edge on A means the encoder is rotating the opposite direction. A rising edge on B followed by a falling edge on B (with no change in A) means that the encoder has undergone no net motion. The out-of-phase A and B pulse trains are known as quadrature signals.

In addition to determining the rotation direction, the pulses can be counted to determine how far the encoder has rotated. The encoder signals can be “decoded” at 1x, 2x, or 4x resolution, where 1x resolution means that a single count is generated for each full cycle of A and B (e.g., on the rising edge of A), 2x resolution means that two counts are generated for each full cycle (e.g., on the rising and falling edges of A), and 4x means that a count is generated for every rising and falling edge of A and B (four counts per cycle, Figure 21.9). Thus an encoder with “100 lines” or “100 pulses per revolution” can be used to generate up to 400 counts per revolution of the encoder. If the encoder is attached to a motor shaft, and the motor shaft is also attached to a 20:1 speed-reducing gearhead, then the encoder generates 400 × 20 = 8000 counts per revolution of the gearhead output shaft...*

**SOURCE:** [Current Advances in Mechanical Design and Production VII, 2000](https://www.sciencedirect.com/topics/engineering/incremental-encoder) 

Mini project
===========================
Changing the brightness of an integrated LED and posting messages to serial PC connection

Wiring diagram
--------------
****
![](https://os.mbed.com/media/platforms/lpc1768_pinout.png)

Following the microcontroller Mbed LPC1768 diagram and KY-040 incremental encoder 
diagram we can connect the wiring:
 * Pin p5 -> DT
 * Pin p6 -> CLK
 * Pin p7 -> Switch *(optional)*
 * GND -> GND
 
 
Code example
------------
<pre>
#include "RotaryEncoder.h"
 
AnalogOut led(LED1);                        //Integrated LED
//DigitalIn sw(p7);                         //Switch (optional)

RotaryEncoder re(p5, p6);                   // Default
//RotaryEncoder re(p5, p6, PullDown);       // With pull mode specified
//RotaryEncoder re(p5, p6, p7);             // With Switch
//RotaryEncoder re(p5, p6, p7, PullDown);   // Switch + pull mode specified

Serial pc(USBTX, USBRX);                    // Serial PC connection

int main(){
  double value = re.Value;
  pc.printf("\nEncoder program started!");
  while(1){
    if(value!=re.Value){
      led.write(re.Value);
      pc.printf("\nEncoder value is: %2.f", re.Value);
      value = re.Value;
    }
    //if(sw){
    //  value = 0.0;
    //}
    wait_ms(1000);
  }
}
</pre>
