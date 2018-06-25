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

#include "parse.h"


node* parse_ldr(TokenStream* token_stream, Token* tmp) {
    
    // Create this for when things go wrong.   
    TokenError* err;

    // Create a new node
    node *node = malloc(sizeof(node));

    debugf("Command type LDR");

    // Set the node type and create a node_mem
    node->type = NTYPE_LDR;
    node_mem* ndemem = malloc(sizeof(node_mem));

    // Set the register.
    tmp = token_stream_next(token_stream, &err);
    ndemem->reg = atoi(tmp->val);

    // Make sure the next token is a comma
    if (token_stream_next(token_stream, &err)->type == TOK_COMMA) {
        
        // Set the memory reference
        tmp = token_stream_next(token_stream, &err);
        ndemem->mem = atoi(tmp->val);
    } else {
        // The token after the first operator wasn't a comma, so there was
        // an error. Again these will be handled better in the future.
        errorf("Unrecognised Token. Aborting...");
        exit(0);
    }

    // Set the node value
    node->value = ndemem;

    return node;
}


node* parse_mov(TokenStream* token_stream, Token* tmp) {
    
    // Create this for when things go wrong
    TokenError* err;

    // Set the tkn value to a char* for ease, also create a node.
    node* node = malloc(sizeof(node));

    debugf("Command type MOV");

    // Set the node type to NTYPE_MOV
    node->type = NTYPE_MOV;

    // Create a node_op for the two operators. Allocate some memory. 
    node_op* op = malloc(sizeof(node_op));


    // Set the first register as the dest, because we are moving something into it
    tmp = token_stream_next(token_stream, &err);         // This token_stream should be the first operator
    op->dest = atoi(tmp->val);    // char* to int issue here


    // Make sure that the next token is a comma
    if (token_stream_next(token_stream, &err)->type == TOK_COMMA) {

        // check what type the seccond operator is.
        tmp = token_stream_next(token_stream, &err);
        if (tmp->type == TOK_REGISTER) {

            // Set type and value accordingly
            op->type = NOP_REGISTER;
            op->value = atoi(tmp->val);

        } else if (tmp->type == TOK_NUMBER) {

            // Set type and value accordingly
            op->type = NOP_LITERAL;
            op->value = atoi(tmp->val);

        } else {

            // We didn't get a register or number, so we abort. 
            // Syntax errors will be handled better in the future.
            errorf("Unrecognised Token Value. Aborting...");
            exit(0);
        }
    } else {
                    
        // The token after the first operator wasn't a comma, so there was
        // an error. Again these will be handled better in the future.
        errorf("Unrecognised Token. Aborting...");
        exit(0);
    }

    node->value = op;

    return node;
}


/**
 * 
 *  The purpose of this is to take a token stream, convert
 *  each token into a node, then return them all as a nodearray.
 * 
 */
nodearray* parse(TokenStream* token_stream) {

    // Create the node array that we are going to return
    nodearray* rt = nodearray_new();

    // These will be needed later.
    Token* tmp = NULL;
    TokenError* err = NULL;

    while ((tmp = token_stream_next(token_stream, &err))) {     // This token_stream dump should be the command
        
        // Check if the token is of the type TOK_COMMAND
        if (tmp->type == TOK_COMMAND){

            char* cmd = tmp->val;

            /**
             *  This if-else block will go through each type of command
             *  and build a nodearray accordingly. 
             */
            if (!strcmp(cmd, "MOV")) {
                
                // Parse MOV and push onto to rt.
                nodearray_push(rt, parse_mov(token_stream, tmp));
                
            } else if (!strcmp(cmd, "LDR")) {

                // Prase LDR and push onto rt
                nodearray_push(rt, parse_ldr(token_stream, tmp));

            }


        }

    }

    nodearray_dump(rt);

    return rt;

}