/**
 * @file    RotaryEncoder.h
 * @brief   Rotary encoder with one interrupt and one digital input
 * @author  Nikša Zupčić
 * @version 1.0
 *
 * Copyright (c) 2022
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
#ifndef ROTARY_ENCODER_H
#define ROTARY_ENCODER_H
 
#include "mbed.h"
 
/** Incremental rotary encoder with a push button
 *
 * Can be used as only an incremental rotary encoder, with/without a pushbutton
 * and the PinMode can be set if needed.
 *
 * Example:
 * @code
 * #include "RotaryEncoder.h"
 *
 * RotaryEncoder re(p5, p6);                   // Default
 * //RotaryEncoder re(p5, p6, PullDown);       // With pull mode specified
 * //RotaryEncoder re(p5, p6, p7);             // With Switch
 * //RotaryEncoder re(p5, p6, p7, PullDown);   // Switch + pull mode specified
 *
 * Serial pc(USBTX, USBRX);                    // Serial PC connection
 *
 * int main(){
 *  double value = re.Value;
 *  pc.printf("\nEncoder program started!");
 *  while(1){
 *      if(value!=re.Value){
 *          pc.printf("\nEncoder value is: %2.f", re.Value);
 *          value = re.Value;
 *      }
 *      wait_ms(1000);
 *  }
 * }
 * @endcode
 */
 
/**
 *  @class RotaryEncoder
 *  @brief Rotary encoder with one interrupt and one digital input
 */  
 
class RotaryEncoder{
    public:
    /** Create an Incremental Rotary Encoder, connected to the specified DT and CLK pins
     *  @param a  - Data transmition (DT) pin
     *  @param b  - Clock (CLK) pin
     *  @param sw - Switch (SW) pin
     *  @note PullMode can be added on the end of the constructor, 
     */
        RotaryEncoder(PinName a, PinName b, PinName sw, PinMode pullMode);
        RotaryEncoder(PinName a, PinName b, PinMode pullMode);
        RotaryEncoder(PinName a, PinName b, PinName sw);
        RotaryEncoder(PinName a, PinName b);
        
        /** This global class variable stores the current value  
         */
        double      Value;
        
        /** This global class variable is used to set the resolution with which 
         *  the value is incremented, e.g., Value+=Resolution 
         */
        float       Resolution;
        
        /** Sets the range in which the global variable Value is limited
         *  @param min - minimal value
         *  @param max - maximal value   
         */
        void        SetRange(double min, double max);
    private:
        void        init(PinMode tPullMode);
        void        count();
        int         bLastState;
        InterruptIn pinA;
        DigitalIn   pinB;
        DigitalIn   pinSw;
        Timer       debounce;
        double      Min, Max;
};
 
#endif
