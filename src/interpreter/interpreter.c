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

int get_reg_state(reg_t reg, RuntimeError** err) {
    if (reg >= 0 && reg <= 11) {
        return register_state[reg];
    } else {
        *err = throw_runtime_error("Bad Register");
        return 0;
    }
}

void set_new_reg_state(reg_t reg, int new_state, RuntimeError** err) {
    if (reg >= 0 && reg <= 11) {
        register_state[reg] = new_state;
    } else {
        *err = throw_runtime_error("Bad Register");
    }
}

void reset_regs() {
    for (int i = 0; i < REGISTER_COUNT; i++) {
        register_state[i] = 0;
    }
}

void display_regs() {

    RuntimeError *err = NULL;
    for (int i = 0; i < REGISTER_COUNT; i++) {
        printf("R%d: %d\n", i, get_reg_state(i, &err));
        if (err) rt_error_print(err);
    }

}
/**
 *  End register prototyping
 */


int interpet_operand(node_op_type t, int value, RuntimeError** err) {
    if (t == NOP_LITERAL) {
        return value;
    } else {
        return get_reg_state(value, err);
    }
}

interpreter_result_t interpet_arithmetic(node* node, RuntimeError** err) {
    // ADD R2, R4, #234
    // ADD R2, R4, R5

    node_op_on* opon = (node_op_on *)node->value;

    int a = get_reg_state(opon->source, err);

    if (*err) {
        return FAILTURE;
    }

    int b = interpet_operand(opon->type, opon->value, err);

    if (*err) {
        return FAILTURE;
    }

    if (node->type == NTYPE_ADD) {
        set_new_reg_state(opon->dest, a + b, err);
    } else {
        set_new_reg_state(opon->dest, a - b, err);
    }

    if (*err) {
        return FAILTURE;
    }

    return SUCCESS;

}


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
void start_interpreter(TokenStream* tok_stream, RuntimeError** err) {

    // Parse the tok_stream to a nodearray.
    nodearray* nodes = parse(tok_stream);

    uint64_t ln_pos = 0;

    while (nodes->value[ln_pos]) {

        node* curr_node = nodes->value[ln_pos];

        switch(curr_node->type) {
            case NTYPE_HALT:
                return;
            case NTYPE_ADD:
            case NTYPE_SUB:
                interpet_arithmetic(curr_node, err);
                break;
        }

        ln_pos++;

        if (*err) return;

        display_regs();
        
    }

    *err = throw_runtime_error("Unexpected end of nodes");



}