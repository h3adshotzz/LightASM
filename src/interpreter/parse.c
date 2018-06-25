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
    Token* tkn = NULL;
    TokenError* err = NULL;

    while ((tkn = token_stream_next(token_stream, &err))) {     // This token_stream dump should be the command
        
        // Check if the token is of the type TOK_COMMAND
        if (tkn->type == TOK_COMMAND){

            // Set the tkn value to a char* for ease, also create a node.
            char* cmd = tkn->val;
            node* node = malloc(sizeof(node));

            /**
             *  This if-else block will go through each type of command
             *  and build a nodearray accordingly. 
             */
            if (!strcmp(cmd, "MOV")) {
                debugf("Command type MOV");
                
                // Set the node type to NTYPE_MOV
                node->type = NTYPE_MOV;

                // Create a node_op for the two operators. Allocate some memory. 
                node_op* op = malloc(sizeof(node_op));


                // Set the first register as the dest, because we are moving something into it
                Token* tmp = token_stream_next(token_stream, &err);         // This token_stream should be the first operator
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

                // Add to the array
                nodearray_push(rt, node);
                
            } else if (!strcmp(cmd, "SUB")) {
                node->type = NTYPE_SUB;
                debugf("Command type SUB");
            }


        }

    }

    nodearray_dump(rt);

    return rt;

}