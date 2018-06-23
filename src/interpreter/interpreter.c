/**
 * LightASM
 * Copyright (C) 2017, Is This On? 
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

int main(int argc, char* argv[]) {
    
    TokenStream* tok_stream = create_new_token_stream("MOV R2, #22");
    TokenError* err = NULL;
    Token* tkn = NULL;

    //node_type *n_type = NULL;
    //node_op_type *n_op_type = NULL;

    while ((tkn = next_token(tok_stream, &err))) {
        token_dump(tkn);

        char type = tkn->type;

        if (type == TOK_COMMAND) {

            debugf("Token is a command");
            //n_type = NTYPE_MOV;

        } else if (type == TOK_REGISTER) {

            debugf("Token is a register");
            //n_op_type = NOP_REGISTER;

        } else if (type == TOK_NUMBER) {

            debugf("Token is a number");
            //n_op_type = NOP_LITERAL;

        } else if (type == TOK_MEMORY) {

            debugf("Token is a memory");

        } else if (type == TOK_COMMA) {

            debugf("Token is a comma");

        } else if (type == TOK_LABEL) {

            debugf("Token is a label");

        } else {
            errorf("Error, Token type unknown. Exiting...");
            exit(0);
        }

    }

    return 0;
}