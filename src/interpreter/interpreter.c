/**
 * LightASM
 * Copyright (C) 2018, Is This On? 
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
*/

#include "interpreter.h"

/**
 *  BEGIN REGISTER PROTOTYPING
 * 
 */
static int register_state[REGISTER_COUNT] = {0,1,2,3,4,5,6,7,8,9,10,11};

int get_reg_state(reg_t reg) {
    if (reg >= 0 && reg <= 11) {
        return register_state[reg];
    } else {
        return REGISTER_DEFAULT_VAL;
    }
}

void set_new_reg_state(reg_t reg, int new_state) {
    register_state[reg] = new_state;
}

void reset_regs() {
    for (int i = 0; i < REGISTER_COUNT; i++) {
        register_state[i] = -1;
    }
}

void display_regs() {

    for (int i = 0; i < REGISTER_COUNT; i++) {
        printf("R%d: %d\n", i, get_reg_state(i));
    }

}
/**
 *  End register prototyping
 */


/**
 *  Start the interpreter
 * 
 *  Returns:
 *      void
 * 
 *  Params:
 *      TokenStream* tok_stream     -   The TokenStream to interpret.
 * 
 */
void start_interpreter(TokenStream* tok_stream) {
    
    // Parse the tok_stream to a nodearray.
    nodearray* test = parse(tok_stream);

}