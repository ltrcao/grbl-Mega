/*
  imprint_servo.c - imprint servo motor control methods
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

#include "imprint_servo.h"

void imprint_servo_init() 
{
    IMPRINT_SERVO_TCCRA_REGISTER |= IMPRINT_SERVO_TCCRA_INIT_MASK;
    IMPRINT_SERVO_TCCRB_REGISTER |= IMPRINT_SERVO_TCCRB_INIT_MASK;
    IMPRINT_SERVO_ICR_REGISTER = -1; // Set TOP to MAX (0xFFFF)
    IMPRINT_SERVO_DDR |= (1 << IMPRINT_SERVO_BIT);
    imprint_servo_disable();
}

uint8_t imprint_servo_get_state() 
{
    if (IMPRINT_SERVO_OCR_REGISTER == IMPRINT_SERVO_OCR_DISABLE)
        return IMPRINT_SERVO_STATE_DISABLE;
    else if (IMPRINT_SERVO_OCR_REGISTER == IMPRINT_SERVO_OCR_ACTUATE)
        return IMPRINT_SERVO_STATE_ACTUATE;
}

void imprint_servo_disable() 
{
    IMPRINT_SERVO_OCR_REGISTER = IMPRINT_SERVO_OCR_DISABLE;
}

void imprint_servo_set_state(uint8_t state)
{
    if (sys.abort) { return; } // Block during abort

    if (state == IMPRINT_SERVO_STATE_DISABLE)
    {
        imprint_servo_disable();
    }
    else 
    {
        IMPRINT_SERVO_OCR_REGISTER = IMPRINT_SERVO_OCR_ACTUATE;
    }
}

void imprint_servo_sync(uint8_t state) 
{
    if (sys.state == STATE_CHECK_MODE)
    {
        return;
    }
    protocol_buffer_synchronize();
    imprint_servo_set_state(state);
}
