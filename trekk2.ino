/* trekk2.ino - Source code for XMC 4700.
 * Copyright (C) 2020 Daniel Stuart <daniel.stuart@pucpr.edu.br>
 * 
 * This file is part of Trekking Project.
 * 
 * Trekking Project is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 * 
 * Trekking Project is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Trekking Project.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <Servo.h>

#define PWM_MOTOR 6
#define DIR_MOTOR 7

#define STEERING 5

#define ENCODER 2
#define TPR 60

#define DEBUG 1

Servo steering;

volatile uint32_t ticks = 0;

void setup() {
  analogWriteResolution(16);
  
  //buttons
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);

  //leds
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  //Steering
  pinMode(STEERING, OUTPUT);
  steering.attach(STEERING);

  //Motor
  pinMode(PWM_MOTOR, OUTPUT);
  pinMode(DIR_MOTOR, OUTPUT);
  setAnalogWriteFrequency(PWM_MOTOR, 2000);
  analogWrite(PWM_MOTOR, 0);
  digitalWrite(DIR_MOTOR, 0);

#if DEBUG
  Serial.begin(115200);
#endif

  //encoder
  pinMode(ENCODER, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ENCODER), tickIncrement, CHANGE);
  

  while (true) {
    if (!digitalRead(BUTTON1)) {
      digitalWrite(LED1, HIGH);
      runLoop();
    }
    if (!digitalRead(BUTTON2)) {
      digitalWrite(LED2, HIGH);
      setLoop();
    }

    delay(1);
  }
  
}

void loop() {

}

void setLoop() {
  while (true) {

    delay(1);
  }
}

void runLoop() {
  while (true) {
#if DEBUG
    Serial.println(ticks/TPR);
    delay(100);
#endif
    delay(1);
  }
}

void tickIncrement() {
  ticks++;
}