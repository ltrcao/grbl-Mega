/*
  track_ball_control.h - Track ball control methods
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

#ifndef track_ball_control_h
#define track_ball_control_h

#include "grbl.h"

#define TRACK_BALL_NO_SYNC     false
#define TRACK_BALL_FORCE_SYNC  true

#define TRACK_BALL_STATE_DISABLE   0  // Must be zero
#define TRACK_BALL_STATE_ENABLE    1


// Initializes air pump control pins.
void track_ball_init();

// Returns current air pump output state. Overrides may alter it from programmed state.
uint8_t track_ball_get_state();

// Immediately disables air pump pins.
void track_ball_stop();

// Sets the air pump pins according to state specified.
void track_ball_set_state(uint8_t mode);

// G-code parser entry-point for setting air pump states. Checks for and executes additional conditions.
void track_ball_sync(uint8_t mode);

#endif
