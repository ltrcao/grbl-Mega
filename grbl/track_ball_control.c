/*
  track_ball_control.c - Track ball control methods
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

//Modeled after spindle_control.c and coolant_control.c
//Macros TRACK_BALL_ENABLE_DDR, TRACK_BALL_ENABLE_PORT, and TRACK_PUMP_ENABLE_BIT defined in cpu_map.h
//Macros TRACK_BALL_STATE_ENABLE and TRACK_BALL_STATE_DISABLE defined in air_pump.h
//Macro INVERT_TRACK_BALL_ENABLE_PIN can be defined in grbl/config.h. 
//      Currently defaulted to being undefined (i.e. do not invert enable pin)

#include "grbl.h"
#include "track_ball_control.h"

void track_ball_init()
{
	TRACK_BALL_ENABLE_DDR |= (1 << TRACK_BALL_ENABLE_BIT); //Configure as output pin
	track_ball_stop();
}

uint8_t track_ball_get_state()
{
	#ifdef INVERT_TRACK_BALL_ENABLE_PIN
		if (bit_isfalse(TRACK_BALL_ENABLE_PORT, (1 << TRACK_BALL_ENABLE_BIT))){
	#else
		if (bit_istrue(TRACK_BALL_ENABLE_PORT, (1 << TRACK_BALL_ENABLE_BIT))){
	#endif
			return TRACK_BALL_STATE_ENABLE;
	}
	return TRACK_BALL_STATE_DISABLE;
}

void track_ball_stop()
{
	#ifdef INVERT_TRACK_BALL_ENABLE_PIN
		TRACK_BALL_ENABLE_PORT |= (1 << TRACK_BALL_ENABLE_BIT);
	#else
		TRACK_BALL_ENABLE_PORT &= ~(1 << TRACK_BALL_ENABLE_BIT);
	#endif
}

void track_ball_set_state(uint8_t state)
{
	if (sys.abort) { return; } //Block during abort
	
	if (state == TRACK_BALL_DISABLE)
	{
		track_ball_stop();
	}
	else
	{
		#ifdef INVERT_TRACK_BALL_ENABLE_PIN
			TRACK_BALL_ENABLE_PORT &= ~(1 << TRACK_BALL_ENABLE_BIT);
		#else
			TRACK_BALL_ENABLE_PORT |= (1 << TRACK_BALL_ENABLE_BIT);
		#endif
	}
}

void track_ball_sync(uint8_t state)
{
	if (sys.state == STATE_CHECK_MODE)
	{
		return;
	}
	protocol_buffer_synchronize();
	track_ball_set_state(state);
}
