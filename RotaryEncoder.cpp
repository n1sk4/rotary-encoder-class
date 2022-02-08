/**
 * @file    RotaryEncoder.cpp
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
 
#include "RotaryEncoder.h"
 
//Default constructor
RotaryEncoder::RotaryEncoder(PinName a, PinName b) : pinA(a), pinB(b),pinSw(NC){
    RotaryEncoder::init(PullDown);
}
 
//Pull mode constructor
RotaryEncoder::RotaryEncoder(PinName a, PinName b, PinMode pullMode)
                            : pinA(a), pinB(b), pinSw(NC){
    RotaryEncoder::init(pullMode);
}
 
//Encoder and switch constructor
RotaryEncoder::RotaryEncoder(PinName a, PinName b, PinName sw)
                            : pinA(a), pinB(b), pinSw(sw){
    pinSw.mode(PullDown);
    RotaryEncoder::init(PullDown);
}
 
//Encoder and switch constructor with pull mode
RotaryEncoder::RotaryEncoder(PinName a, PinName b, PinName sw, 
                            PinMode pullMode): pinA(a), pinB(b), pinSw(sw){
    pinSw.mode(pullMode);
    RotaryEncoder::init(pullMode);
}
 
//Initialize routine
void RotaryEncoder::init(PinMode tPullMode){
    //Setup pin B pull mode
    pinB.mode(tPullMode);
    //Initialize start values
    Value       = 0.0;
    Resolution  = 1.0;
    SetRange(0.0, 100.0); //Range form 0-100
    bLastState = pinB.read();
    //Setup hardware interrupt
    pinA.rise(this, &RotaryEncoder::count);
    pinA.fall(this, &RotaryEncoder::count);
    //Start debounce timer
    debounce.start();
}
 
//Count routine
void RotaryEncoder::count(){
    int bState = pinB.read();
    if(RotaryEncoder::debounce.read_ms() > 10){
        if(bState != bLastState && bState == 1){
            (pinA.read()!=bState)? (Value -= Resolution) : (Value += Resolution);
        }
        
        if(Value<Min) Value = Min;
        if(Value>Max) Value = Max;
        
        RotaryEncoder::debounce.reset();
    }
    bLastState = bState;
}
 
void RotaryEncoder::SetRange(double min, double max){
    Min = min;
    Max = max;
}
