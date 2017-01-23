/*
  coolant_control.h - spindle control methods
  Part of Grbl

  Copyright (c) 2012-2016 Sungeun K. Jeon for Gnea Research LLC

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

#ifndef air_pump_control_h
#define air_pump_control_h

#define AIR_PUMP_NO_SYNC     false
#define AIR_PUMP_FORCE_SYNC  true

#define AIR_PUMP_STATE_DISABLE   0  // Must be zero
#define AIR_PUMP_STATE_ENABLE    1


// Initializes air pump control pins.
void air_pump_init();

// Returns current air pump output state. Overrides may alter it from programmed state.
uint8_t air_pump_get_state();

// Immediately disables air pump pins.
void air_pump_stop();

// Sets the air pump pins according to state specified.
void air_pump_set_state(uint8_t mode);

// G-code parser entry-point for setting air pump states. Checks for and executes additional conditions.
void air_pump_sync(uint8_t mode);

#endif
