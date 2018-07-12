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
 *  All 12 registers represented as integers.
 * 
 */
static int register_state[REGISTER_COUNT] = {0,1,2,3,4,5,6,7,8,9,10,11};


/**
 *  Get the current step of a register.
 * 
 *  Returns:
 *      int     -   Register State
 * 
 *  Params:
 *      reg_t reg           -   The register we want 
 * 
 */
int get_reg_state(reg_t reg, RuntimeError** err) {
    if (reg >= 0 && reg <= 11) {
        return register_state[reg];
    } else {
        *err = throw_runtime_error("Bad Register");
        return 0;
    }
}


/**
 *  Set the new state of a given register
 * 
 *  Returns:
 *      void
 * 
 *  Params:
 *      reg_t reg       -   Register to modify
 *      int new_state   -   New state of the register
 * 
 */
void set_new_reg_state(reg_t reg, int new_state, RuntimeError** err) {
    if (reg >= 0 && reg <= 11) {
        register_state[reg] = new_state;
    } else {
        *err = throw_runtime_error("Bad Register");
    }
}


/**
 *  Reset all the registers to 0
 * 
 */
void reset_regs() {
    for (int i = 0; i < REGISTER_COUNT; i++) {
        register_state[i] = 0;
    }
}


/**
 *  Display the contents of all the registers in a
 *      formatted way.
 *
 */
void display_regs() {

    RuntimeError *err = NULL;
    for (int i = 0; i < REGISTER_COUNT; i++) {
        printf("R%d: %d\n", i, get_reg_state(i, &err));
        if (err) rt_error_print(err);
    }

}


/**
 *  Interpret the operand.
 * 
 *  Returns:
 *      int     -   Value of the operand
 * 
 *  Params:
 *      node_op_type t      -   The node operand type
 *      int value           -   Operand value
 * 
 */
int interpret_operand(node_op_type t, int value, RuntimeError** err) {
    if (t == NOP_LITERAL) {
        return value;
    } else {
        return get_reg_state(value, err);
    }
}


/**
 *  Interpret the arithmetic commands.
 * 
 *  Returns:
 *      interpreter_result_t        -   The result of the interpretation
 * 
 *  Params:
 *      node node   -   The node to interpret
 * 
 */
interpreter_result_t interpret_arithmetic(node* node, RuntimeError** err) {
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
 *  Interpret the memory commands.
 * 
 *  Returns:
 *      interpreter_result_t        -   The result of the interpretation
 * 
 *  Params:
 *      node node           -   The node to interpret
 *      address_space_t     -   User data address space
 * 
 */
interpreter_result_t interpret_memory(node* node, address_space_t* usr_space, RuntimeError** err) {
    // LDR R2, 234
    // STR R1, 234

    node_mem* mem = (node_mem *)node->value;

    if (*err) return FAILTURE;

    if (node->type == NTYPE_LDR) {

        int a = address_space_get_ref(usr_space, mem->mem);
        if (*err) return FAILTURE;

        printlnf("Got contents of memref %d as %d", mem->mem, a);
        set_new_reg_state(mem->reg, a, err);
        if (*err) return FAILTURE;

    } else if (node->type == NTYPE_STR) {

        int b = get_reg_state(mem->reg, err);
        if (*err) return FAILTURE;

        printlnf("Got reg state of R%d as %d. Setting memref %d", mem->reg, b, mem->mem);
        address_space_set_ref(usr_space, mem->mem, b);
        

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
void start_interpreter(TokenStream* tok_stream, address_space_t* usr_space, address_space_t* node_space, RuntimeError** err) {

    // Parse the tok_stream to a nodearray.
    nodearray* nodes = parse(tok_stream, err);
    if (*err) return;

    uint64_t ln_pos = 0;

    while (nodes->value[ln_pos]) {

        node* curr_node = nodes->value[ln_pos];

        address_space_push(node_space, curr_node);

        switch(curr_node->type) {
            case NTYPE_HALT:
                return;
            case NTYPE_ADD:
            case NTYPE_SUB:
                interpret_arithmetic(curr_node, err);
                break;
            case NTYPE_LDR:
            case NTYPE_STR:
                interpret_memory(curr_node, usr_space, err);
        }

        ln_pos++;

        if (*err) return;

        //nodearray_dump(nodes);
        display_regs();
        
    }

    *err = throw_runtime_error("Unexpected end of nodes");

}