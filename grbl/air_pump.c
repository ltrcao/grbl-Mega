//Modeled after spindle_control.c and coolant_control.c
//Macros AIR_PUMP_ENABLE_DDR, AIR_PUMP_ENABLE_PORT, and AIR_PUMP_ENABLE_BIT defined in cpu_map.h
//Macros AIR_PUMP_STATE_ENABLE and AIR_PUMP_STATE_DISABLE defined in air_pump.h
//Macro INVERT_AIR_PUMP_ENABLE_PIN defined ...(somewhere)

#include "grbl.h"

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