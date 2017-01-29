/*
  air_pump.c - vacuum/air pump control methods
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
//Macros AIR_PUMP_ENABLE_DDR, AIR_PUMP_ENABLE_PORT, and AIR_PUMP_ENABLE_BIT defined in cpu_map.h
//Macros AIR_PUMP_STATE_ENABLE and AIR_PUMP_STATE_DISABLE defined in air_pump.h
//Macro INVERT_AIR_PUMP_ENABLE_PIN can be defined in grbl/defaults.h. 
//      Currently defaulted to being undefined (i.e. do not invert enable pin)

#include "grbl.h"
#include "air_pump.h"

void air_pump_init()
{
	AIR_PUMP_ENABLE_DDR |= (1 << AIR_PUMP_ENABLE_BIT); //Configure as output pin
	air_pump_stop();
}

uint8_t air_pump_get_state()
{
	#ifdef INVERT_AIR_PUMP_ENABLE_PIN
		if (bit_isfalse(AIR_PUMP_ENABLE_PORT, (1 << AIR_PUMP_ENABLE_BIT))){
	#else
		if (bit_istrue(AIR_PUMP_ENABLE_PORT, (1 << AIR_PUMP_ENABLE_BIT))){
	#endif
			return AIR_PUMP_STATE_ENABLE;
	}
	return AIR_PUMP_STATE_DISABLE;
}

void air_pump_stop()
{
	#ifdef INVERT_AIR_PUMP_ENABLE_PIN
		AIR_PUMP_ENABLE_PORT |= (1 << AIR_PUMP_ENABLE_BIT);
	#else
		AIR_PUMP_ENABLE_PORT &= ~(1 << AIR_PUMP_ENABLE_BIT);
	#endif
}

void air_pump_set_state(uint8_t state)
{
	if (sys.abort) { return; } //Block during abort
	
	if (state == AIR_PUMP_DISABLE)
	{
		air_pump_stop();
	}
	
	#ifdef INVERT_AIR_PUMP_ENABLE_PIN
		AIR_PUMP_ENABLE_PORT &= ~(1 << AIR_PUMP_ENABLE_BIT);
	#else
		AIR_PUMP_ENABLE_PORT |= (1 << AIR_PUMP_ENABLE_BIT);
	#endif
}

void air_pump_sync(uint8_t state)
{
	if (sys.state == STATE_CHECK_MODE)
	{
		return;
	}
	protocol_buffer_synchronize();
	air_pump_set_state(state);
}
