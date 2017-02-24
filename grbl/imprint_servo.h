/*
  imprint_servo.h - imprint servo motor control methods
  Grbl add-on

  Copyright (c) 2017 Paul Dao and Leon Cao

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef imprint_servo_control_h
#define imprint_servo_control_h

#include "grbl.h"

#define IMPRINT_SERVO_NO_SYNC       false
#define IMPRINT_SERVO_FORCE_SYNC    true

#define IMPRINT_SERVO_STATE_DISABLE     0 // Send no pulse to servo motor
#define IMPRINT_SERVO_STATE_ACTUATE     1 // Send servo motor to actuating degrees


// Initializes timer/counter registers and servo output pins.
void imprint_servo_init();

// Returns current imprint servo output state.
uint8_t imprint_servo_get_state();

// Immediately disable imprint servo.
void imprint_servo_disable();

// Sets the imprint servo output according to state specified.
void imprint_servo_set_state(uint8_t mode);

// G-code parser entry-point for setting imprint servo states.
void imprint_servo_sync(uint8_t mode);

#endif
