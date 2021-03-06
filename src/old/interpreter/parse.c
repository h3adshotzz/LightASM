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
 *  Checks whether the given Token Stream is of the type
 *  TOK_COMMA. 
 * 
 *  Returns:
 *      int     -   is the token a comma?
 * 
 *  Params:
 *      TokenStream     -   The Token Stream to verify
 *      Error      -   The Token Error currently use.
 * 
 */
int is_comma(TokenStream* tmp, Error** err) {
    Token* tmp2 = token_stream_next(tmp, err);
    if (!tmp2) return 0;
    if (tmp2->type == TOK_COMMA) {
        return 1;
    } 
    return 0;
}


/**
 *  Checks whether the given Token Stream is of the type
 *  TOK_MEMORY
 * 
 *  Returns:
 *      int             -   is the token a memory ref?
 *  
 *  Params:
 *      TokenStream     -   The Token Stream to verify
 *      Error      -   The Token Error currently in use
 * 
 */
int get_memref(TokenStream* tmp, Error** err) {
    Token* tmp2 = token_stream_next(tmp, err);
    if (!tmp2) return 0;
    if (tmp2->type == TOK_MEMORY) {
        return atoi(tmp2->val);
    }
    *err = throw_error("Token not of type TOK_MEMORY");
    return 0;
}


/**
 *  Checks whether the given Token Stream is of the type
 *  TOK_REGISTER
 * 
 *  Returns:
 *      int                     -   is the token a register?
 *  
 *  Params:
 *      TokenStream - tmp       -   The Token Stream to verify
 *      Error - err        -   The Token Error currently in use
 * 
 */
int get_register(TokenStream* tmp, Error** err) {
    Token* tmp2 = token_stream_next(tmp, err);
    if (!tmp2) return 0;
    if (tmp2->type == TOK_REGISTER) {
        return atoi(tmp2->val);
    }
    *err = throw_error("Token not a of type TOK_REGISTER");
    return 0;
}


/**
 *  The logic to parse the LDR command from a Token Stream
 *  to a single node. NULL can be returned if the token
 *  isn't of the correct type, which can then be handled else-
 *  where. 
 * 
 *  Returns:
 *      node                                -   The node built from the Token Stream
 * 
 *  Params:
 *      TokenStream - token_stream          -   The Token Stream currently being used
 *      Token - tmp                         -   A temp Token to store the current TokenStream.
 *      Error - err                    -   The Token Error currently in use.
 * 
 */
node* parse_ldr(TokenStream* token_stream, Token* tmp, Error** err) {
    
    // Create a new node, set the type and then create a node_mem
    node* node = malloc(sizeof(node));
    node->type = NTYPE_LDR;
    node_mem* ndemem = malloc(sizeof(node_mem));

    // Set the first register
    ndemem->reg = get_register(token_stream, err);
    if (*err) return NULL;

    // Handle the first comma
    if (!is_comma(token_stream, err)) return NULL;

    // Set the memory reference
    ndemem->mem = get_memref(token_stream, err);

    // Set the node value
    node->value = ndemem;

    // Return the node
    return node;

}


/**
 *  The logic to parse the STR command from a Token Stream
 *  to a single node. NULL can be returned if the token
 *  isn't of the correct type, which can then be handled else-
 *  where. 
 * 
 *  Returns:
 *      node                                -   The node built from the Token Stream
 * 
 *  Params:
 *      TokenStream - token_stream          -   The Token Stream currently being used
 *      Token - tmp                         -   A temp Token to store the current TokenStream.
 *      Error - err                    -   The Token Error currently in use.
 * 
 */
node* parse_str(TokenStream* token_stream, Token* tmp, Error** err) {

    // Create a new node, set the type and then createa a node_mem
    node* node = malloc(sizeof(node));
    node->type = NTYPE_STR;
    node_mem* ndemem = malloc(sizeof(ndemem));

    // Set the first register
    ndemem->reg = get_register(token_stream, err);
    if (*err) return NULL;

    // Handle the first comma
    if (!is_comma(token_stream, err)) return NULL;

    // Set the memory reference
    ndemem->mem = get_memref(token_stream, err);

    // Set the node value
    node->value = ndemem;

    // Return the node
    return node;

}


/**
 *  The logic to parse the MOV command from a Token Stream
 *  to a single node. NULL can be returned if the token
 *  isn't of the correct type, which can then be handled else-
 *  where. 
 * 
 *  Returns:
 *      node                                -   The node built from the Token Stream
 * 
 *  Params:
 *      TokenStream - token_stream          -   The Token Stream currently being used
 *      Token - tmp                         -   A temp Token to store the current TokenStream.
 *      Error - err                    -   The Token Error currently in use.
 * 
 */
node* parse_mov(TokenStream* token_stream, Token* tmp, Error** err) {
    
    // Create a new node, set the type and then create a node_op
    node *node = malloc(sizeof(node));
    node->type = NTYPE_MOV;
    node_op *op = malloc(sizeof(node_op));

    // Set the first register
    op->dest = get_register(token_stream, err);
    if (*err) return NULL;

    // Handle the first comma
    if (!is_comma(token_stream, err)) return NULL;

    // Check whether we are using a register or a number
    tmp = token_stream_next(token_stream, err);
    if (!tmp) return NULL;
    if (tmp->type == TOK_REGISTER) {

        // Set the type and value of op
        op->type = NOP_REGISTER;
        op->value = atoi(tmp->val);
    } else if (tmp->type == TOK_NUMBER) {

        // Set the type and value op
        op->type = NOP_LITERAL;
        op->value = atoi(tmp->val);
    } else {

        // There was an issue, throw a token error with a message.
        *err = throw_error("Token not of type TOK_REGISTER or TOK_NUMBER");
        return NULL;
    }

    // Set the nodes value 
    node->value = op;

    // Return the node
    return node;
}


/**
 *  The logic to parse the CMP command from a Token Stream
 *  to a single node. NULL can be returned if the token
 *  isn't of the correct type, which can then be handled else-
 *  where. 
 * 
 *  Returns:
 *      node                                -   The node built from the Token Stream
 * 
 *  Params:
 *      TokenStream - token_stream          -   The Token Stream currently being used
 *      Token - tmp                         -   A temp Token to store the current TokenStream.
 *      Error - err                    -   The Token Error currently in use.
 * 
 */
node* parse_cmp(TokenStream* token_stream, Token* tmp, Error** err) {

    // Create a new node, set the type and then create a node_op
    node *node = malloc(sizeof(node));
    node->type = NTYPE_CMP;
    node_op *op = malloc(sizeof(node_op));

    // Set the first register
    op->dest = get_register(token_stream, err);
    if (*err) return NULL;

    // Handle the first comma
    if (!is_comma(token_stream, err)) return NULL;

    // Check whether we are using a register or a number
    tmp = token_stream_next(token_stream, err);
    if (!tmp) return NULL;
    if (tmp->type == TOK_REGISTER) {

        // Set the type and value of op
        op->type = NOP_REGISTER;
        op->value = atoi(tmp->val);
    } else if (tmp->type == TOK_NUMBER) {

        // Set the type and value op
        op->type = NOP_LITERAL;
        op->value = atoi(tmp->val);
    } else {

        // There was an issue, throw a token error with a message.
        *err = throw_error("Token not of type TOK_REGISTER or TOK_NUMBER");
        return NULL;
    }

    // Set the nodes value 
    node->value = op;

    // Return the node
    return node;

}


/**
 *  The logic to parse the ADD command from a Token Stream
 *  to a single node. NULL can be returned if the token
 *  isn't of the correct type, which can then be handled else-
 *  where. 
 * 
 *  Returns:
 *      node                                -   The node built from the Token Stream
 * 
 *  Params:
 *      TokenStream - token_stream          -   The Token Stream currently being used
 *      Token - tmp                         -   A temp Token to store the current TokenStream.
 *      Error - err                    -   The Token Error currently in use.
 * 
 */
node* parse_add(TokenStream* token_stream, Token* tmp, Error** err) {

    // Create a new node, set the type and then create a node_op_on
    node* node = malloc(sizeof(node));
    node_op_on *op_on = malloc(sizeof(node_op_on));
    node->type = NTYPE_ADD;

    // Set the first register.
    op_on->dest = get_register(token_stream, err);
    if (*err) return NULL;

    // Handle the first comma
    if (!is_comma(token_stream, err)) return NULL;

    // Set the seccond register
    op_on->source = get_register(token_stream, err);
    if (*err) return NULL;

    // Handle the seccond comma
    if (!is_comma(token_stream, err)) return NULL;

    // Check whether we are using another register or number
    tmp = token_stream_next(token_stream, err);
    if (!tmp) return NULL;
    if (tmp->type == TOK_REGISTER) {

        // Set the type and value of op_on
        op_on->type = NOP_REGISTER;
        op_on->value = atoi(tmp->val);

    } else if (tmp->type == TOK_NUMBER) {

        // Set the type and value of op_on
        op_on->type = NOP_LITERAL;
        op_on->value = atoi(tmp->val);

    } else {

        // There was an issue, throw a token error with a message.
        *err = throw_error("Token not of type TOK_REGISTER or TOK_NUMBER");
        return NULL;
    }

    // Assign value as op_on.
    node->value = op_on;

    // Return the node.
    return node;

}


/**
 *  The logic to parse the SUB command from a Token Stream
 *  to a single node. NULL can be returned if the token
 *  isn't of the correct type, which can then be handled else-
 *  where. 
 * 
 *  Returns:
 *      node                                -   The node built from the Token Stream
 * 
 *  Params:
 *      TokenStream - token_stream          -   The Token Stream currently being used
 *      Token - tmp                         -   A temp Token to store the current TokenStream.
 *      Error - err                    -   The Token Error currently in use.
 * 
 */
node* parse_sub(TokenStream* token_stream, Token* tmp, Error** err) {

    // Create a new node, set the type and then create a node_op_on
    node* node = malloc(sizeof(node));
    node_op_on *op_on = malloc(sizeof(node_op_on));
    node->type = NTYPE_SUB;

    // Set the first register.
    op_on->dest = get_register(token_stream, err);
    if (*err) return NULL;

    // Handle the first comma
    if (!is_comma(token_stream, err)) return NULL;

    // Set the seccond register
    op_on->source = get_register(token_stream, err);
    if (*err) return NULL;

    // Handle the seccond comma
    if (!is_comma(token_stream, err)) return NULL;

    // Check whether we are using another register or number
    tmp = token_stream_next(token_stream, err);
    if (!tmp) return NULL;
    if (tmp->type == TOK_REGISTER) {

        // Set the type and value of op_on
        op_on->type = NOP_REGISTER;
        op_on->value = atoi(tmp->val);

    } else if (tmp->type == TOK_NUMBER) {

        // Set the type and value of op_on
        op_on->type = NOP_LITERAL;
        op_on->value = atoi(tmp->val);

    } else {

        // There was an issue, throw a token error with a message.
        *err = throw_error("Token not of type TOK_REGISTER or TOK_NUMBER");
        return NULL;
    }

    // Assign value as op_on.
    node->value = op_on;

    // Return the node.
    return node;

}


/**
 *  The logic to parse the AND command from a Token Stream
 *  to a single node. NULL can be returned if the token
 *  isn't of the correct type, which can then be handled else-
 *  where. 
 * 
 *  Returns:
 *      node                                -   The node built from the Token Stream
 * 
 *  Params:
 *      TokenStream - token_stream          -   The Token Stream currently being used
 *      Token - tmp                         -   A temp Token to store the current TokenStream.
 *      Error - err                    -   The Token Error currently in use.
 * 
 */
node* parse_and(TokenStream* token_stream, Token* tmp, Error** err) {

    // Create a new node, set the type and then create a node_op_on
    node* node = malloc(sizeof(node));
    node_op_on *op_on = malloc(sizeof(node_op_on));
    node->type = NTYPE_AND;

    // Set the first register.
    op_on->dest = get_register(token_stream, err);
    if (*err) return NULL;

    // Handle the first comma
    if (!is_comma(token_stream, err)) return NULL;

    // Set the seccond register
    op_on->source = get_register(token_stream, err);
    if (*err) return NULL;

    // Handle the seccond comma
    if (!is_comma(token_stream, err)) return NULL;

    // Check whether we are using another register or number
    tmp = token_stream_next(token_stream, err);
    if (!tmp) return NULL;
    if (tmp->type == TOK_REGISTER) {

        // Set the type and value of op_on
        op_on->type = NOP_REGISTER;
        op_on->value = atoi(tmp->val);

    } else if (tmp->type == TOK_NUMBER) {

        // Set the type and value of op_on
        op_on->type = NOP_LITERAL;
        op_on->value = atoi(tmp->val);

    } else {

        // There was an issue, throw a token error with a message.
        *err = throw_error("Token not of type TOK_REGISTER or TOK_NUMBER");
        return NULL;
    }

    // Assign value as op_on.
    node->value = op_on;

    // Return the node.
    return node;

}


/**
 *  The logic to parse the ORR command from a Token Stream
 *  to a single node. NULL can be returned if the token
 *  isn't of the correct type, which can then be handled else-
 *  where. 
 * 
 *  Returns:
 *      node                                -   The node built from the Token Stream
 * 
 *  Params:
 *      TokenStream - token_stream          -   The Token Stream currently being used
 *      Token - tmp                         -   A temp Token to store the current TokenStream.
 *      Error - err                    -   The Token Error currently in use.
 * 
 */
node* parse_orr(TokenStream* token_stream, Token* tmp, Error** err) {

    // Create a new node, set the type and then create a node_op_on
    node* node = malloc(sizeof(node));
    node_op_on *op_on = malloc(sizeof(node_op_on));
    node->type = NTYPE_ORR;

    // Set the first register.
    op_on->dest = get_register(token_stream, err);
    if (*err) return NULL;

    // Handle the first comma
    if (!is_comma(token_stream, err)) return NULL;

    // Set the seccond register
    op_on->source = get_register(token_stream, err);
    if (*err) return NULL;

    // Handle the seccond comma
    if (!is_comma(token_stream, err)) return NULL;

    // Check whether we are using another register or number
    tmp = token_stream_next(token_stream, err);
    if (!tmp) return NULL;
    if (tmp->type == TOK_REGISTER) {

        // Set the type and value of op_on
        op_on->type = NOP_REGISTER;
        op_on->value = atoi(tmp->val);

    } else if (tmp->type == TOK_NUMBER) {

        // Set the type and value of op_on
        op_on->type = NOP_LITERAL;
        op_on->value = atoi(tmp->val);

    } else {

        // There was an issue, throw a token error with a message.
        *err = throw_error("Token not of type TOK_REGISTER or TOK_NUMBER");
        return NULL;
    }

    // Assign value as op_on.
    node->value = op_on;

    // Return the node.
    return node;

}


/**
 *  The logic to parse the EOR command from a Token Stream
 *  to a single node. NULL can be returned if the token
 *  isn't of the correct type, which can then be handled else-
 *  where. 
 * 
 *  Returns:
 *      node                                -   The node built from the Token Stream
 * 
 *  Params:
 *      TokenStream - token_stream          -   The Token Stream currently being used
 *      Token - tmp                         -   A temp Token to store the current TokenStream.
 *      Error - err                    -   The Token Error currently in use.
 * 
 */
node* parse_eor(TokenStream* token_stream, Token* tmp, Error** err) {

    // Create a new node, set the type and then create a node_op_on
    node* node = malloc(sizeof(node));
    node_op_on *op_on = malloc(sizeof(node_op_on));
    node->type = NTYPE_EOR;

    // Set the first register.
    op_on->dest = get_register(token_stream, err);
    if (*err) return NULL;

    // Handle the first comma
    if (!is_comma(token_stream, err)) return NULL;

    // Set the seccond register
    op_on->source = get_register(token_stream, err);
    if (*err) return NULL;

    // Handle the seccond comma
    if (!is_comma(token_stream, err)) return NULL;

    // Check whether we are using another register or number
    tmp = token_stream_next(token_stream, err);
    if (!tmp) return NULL;
    if (tmp->type == TOK_REGISTER) {

        // Set the type and value of op_on
        op_on->type = NOP_REGISTER;
        op_on->value = atoi(tmp->val);

    } else if (tmp->type == TOK_NUMBER) {

        // Set the type and value of op_on
        op_on->type = NOP_LITERAL;
        op_on->value = atoi(tmp->val);

    } else {

        // There was an issue, throw a token error with a message.
        *err = throw_error("Token not of type TOK_REGISTER or TOK_NUMBER");
        return NULL;
    }

    // Assign value as op_on.
    node->value = op_on;

    // Return the node.
    return node;

}


/**
 *  The logic to parse the MVN command from a Token Stream
 *  to a single node. NULL can be returned if the token
 *  isn't of the correct type, which can then be handled else-
 *  where. 
 * 
 *  Returns:
 *      node                                -   The node built from the Token Stream
 * 
 *  Params:
 *      TokenStream - token_stream          -   The Token Stream currently being used
 *      Token - tmp                         -   A temp Token to store the current TokenStream.
 *      Error - err                    -   The Token Error currently in use.
 * 
 */
node* parse_mvn(TokenStream* token_stream, Token* tmp, Error** err) {
    
    // Create a new node, set the type and then create a node_op
    node *node = malloc(sizeof(node));
    node->type = NTYPE_MVN;
    node_op *op = malloc(sizeof(node_op));

    // Set the first register
    op->dest = get_register(token_stream, err);
    if (*err) return NULL;

    // Handle the first comma
    if (!is_comma(token_stream, err)) return NULL;

    // Check whether we are using a register or a number
    tmp = token_stream_next(token_stream, err);
    if (!tmp) return NULL;
    if (tmp->type == TOK_REGISTER) {

        // Set the type and value of op
        op->type = NOP_REGISTER;
        op->value = atoi(tmp->val);
    } else if (tmp->type == TOK_NUMBER) {

        // Set the type and value op
        op->type = NOP_LITERAL;
        op->value = atoi(tmp->val);
    } else {

        // There was an issue, throw a token error with a message.
        *err = throw_error("Token not of type TOK_REGISTER or TOK_NUMBER");
        return NULL;
    }

    // Set the nodes value 
    node->value = op;

    // Return the node
    return node;

}


/**
 *  The logic to parse the LSL command from a Token Stream
 *  to a single node. NULL can be returned if the token
 *  isn't of the correct type, which can then be handled else-
 *  where. 
 * 
 *  Returns:
 *      node                                -   The node built from the Token Stream
 * 
 *  Params:
 *      TokenStream - token_stream          -   The Token Stream currently being used
 *      Token - tmp                         -   A temp Token to store the current TokenStream.
 *      Error - err                    -   The Token Error currently in use.
 * 
 */
node* parse_lsl(TokenStream* token_stream, Token* tmp, Error** err) {

    // Create a new node, set the type and then create a node_op_on
    node* node = malloc(sizeof(node));
    node_op_on *op_on = malloc(sizeof(node_op_on));
    node->type = NTYPE_LSL;

    // Set the first register.
    op_on->dest = get_register(token_stream, err);
    if (*err) return NULL;

    // Handle the first comma
    if (!is_comma(token_stream, err)) return NULL;

    // Set the seccond register
    op_on->source = get_register(token_stream, err);
    if (*err) return NULL;

    // Handle the seccond comma
    if (!is_comma(token_stream, err)) return NULL;

    // Check whether we are using another register or number
    tmp = token_stream_next(token_stream, err);
    if (!tmp) return NULL;
    if (tmp->type == TOK_REGISTER) {

        // Set the type and value of op_on
        op_on->type = NOP_REGISTER;
        op_on->value = atoi(tmp->val);

    } else if (tmp->type == TOK_NUMBER) {

        // Set the type and value of op_on
        op_on->type = NOP_LITERAL;
        op_on->value = atoi(tmp->val);

    } else {

        // There was an issue, throw a token error with a message.
        *err = throw_error("Token not of type TOK_REGISTER or TOK_NUMBER");
        return NULL;
    }

    // Assign value as op_on.
    node->value = op_on;

    // Return the node.
    return node;

}


/**
 *  The logic to parse the LSR command from a Token Stream
 *  to a single node. NULL can be returned if the token
 *  isn't of the correct type, which can then be handled else-
 *  where. 
 * 
 *  Returns:
 *      node                                -   The node built from the Token Stream
 * 
 *  Params:
 *      TokenStream - token_stream          -   The Token Stream currently being used
 *      Token - tmp                         -   A temp Token to store the current TokenStream.
 *      Error - err                    -   The Token Error currently in use.
 * 
 */
node* parse_lsr(TokenStream* token_stream, Token* tmp, Error** err) {

    // Create a new node, set the type and then create a node_op_on
    node* node = malloc(sizeof(node));
    node_op_on *op_on = malloc(sizeof(node_op_on));
    node->type = NTYPE_LSR;

    // Set the first register.
    op_on->dest = get_register(token_stream, err);
    if (*err) return NULL;

    // Handle the first comma
    if (!is_comma(token_stream, err)) return NULL;

    // Set the seccond register
    op_on->source = get_register(token_stream, err);
    if (*err) return NULL;

    // Handle the seccond comma
    if (!is_comma(token_stream, err)) return NULL;

    // Check whether we are using another register or number
    tmp = token_stream_next(token_stream, err);
    if (!tmp) return NULL;
    if (tmp->type == TOK_REGISTER) {

        // Set the type and value of op_on
        op_on->type = NOP_REGISTER;
        op_on->value = atoi(tmp->val);

    } else if (tmp->type == TOK_NUMBER) {

        // Set the type and value of op_on
        op_on->type = NOP_LITERAL;
        op_on->value = atoi(tmp->val);

    } else {

        // There was an issue, throw a token error with a message.
        *err = throw_error("Token not of type TOK_REGISTER or TOK_NUMBER");
        return NULL;
    }

    // Assign value as op_on.
    node->value = op_on;

    // Return the node.
    return node;

}


/**
 *  The logic to parse the HALT command from a Token Stream
 *  to a single node. 
 * 
 *  Returns:
 *      node                                -   The node built from the Token Stream
 * 
 *  Params:
 *      TokenStream - token_stream          -   The Token Stream currently being used
 *      Token - tmp                         -   A temp Token to store the current TokenStream.
 *      Error - err                    -   The Token Error currently in use.
 * 
 */
node* parse_halt(TokenStream* token_stream, Token* tmp, Error** err) {

    node* node = malloc(sizeof(node));
    node->type = NTYPE_HALT;

    return node;
}


/**
 *  The logic to parse the given Token Stream into a node array
 *  which then can be interpreted.
 * 
 *  Returns:
 *      nodearray                          -    The nodearray built from the Token Stream 
 * 
 *  Params:
 *      TokenStream - token_stream         -    The Token Stream to be parsed to a nodearray
 * 
 */
nodearray* parse(TokenStream* token_stream, Error** err) {

    // Create the node array that we are going to return
    nodearray* rt = nodearray_new();

    // These will be needed later.
    Token* tmp = NULL;

    while ((tmp = token_stream_next(token_stream, err))) {     // This token_stream dump should be the command
        
        // Check if the token is of the type TOK_COMMAND
        if (tmp->type == TOK_COMMAND){

            char* cmd = tmp->val;

            /**
             *  This if-else block will go through each type of command
             *  and build a nodearray accordingly. 
             */
            if (!strcmp(cmd, "LDR")) {
                // Parse MOV and push onto to rt.
                nodearray_push(rt, parse_ldr(token_stream, tmp, err));
            } else if (!strcmp(cmd, "STR")) {
                // Parse STR and push onto rt
                nodearray_push(rt, parse_str(token_stream, tmp, err));
            } else if (!strcmp(cmd, "ADD")) {
                // Parse STR and push onto rt
                nodearray_push(rt, parse_add(token_stream, tmp, err));
            } else if (!strcmp(cmd, "SUB")) {
                // Parse STR and push onto rt
                nodearray_push(rt, parse_sub(token_stream, tmp, err));
            } else if (!strcmp(cmd, "MOV")) {
                // Parse STR and push onto rt
                nodearray_push(rt, parse_mov(token_stream, tmp, err));
            } else if (!strcmp(cmd, "CMP")) {
                // Parse STR and push onto rt
                nodearray_push(rt, parse_cmp(token_stream, tmp, err));
            } else if (!strcmp(cmd, "AND")) {
                // Parse STR and push onto rt
                nodearray_push(rt, parse_and(token_stream, tmp, err));
            } else if (!strcmp(cmd, "CMP")) {
                // Parse STR and push onto rt
                nodearray_push(rt, parse_cmp(token_stream, tmp, err));
            } else if (!strcmp(cmd, "AND")) {
                // Parse STR and push onto rt
                nodearray_push(rt, parse_and(token_stream, tmp, err));
            } else if (!strcmp(cmd, "ORR")) {
                // Parse STR and push onto rt
                nodearray_push(rt, parse_orr(token_stream, tmp, err));
            } else if (!strcmp(cmd, "EOR")) {
                // Parse STR and push onto rt
                nodearray_push(rt, parse_eor(token_stream, tmp, err));
            } else if (!strcmp(cmd, "MVN")) {
                // Parse STR and push onto rt
                nodearray_push(rt, parse_mvn(token_stream, tmp, err));
            } else if (!strcmp(cmd, "LSL")) {
                // Parse STR and push onto rt
                nodearray_push(rt, parse_lsl(token_stream, tmp, err));
            } else if (!strcmp(cmd, "LSR")) {
                // Parse STR and push onto rt
                nodearray_push(rt, parse_lsr(token_stream, tmp, err));
            } else if (!strcmp(cmd, "B")) {
                // Parse STR and push onto rt
                //nodearray_push(rt, parse_b(token_stream, tmp, err));
            } else if (!strcmp(cmd, "HALT")) {
                nodearray_push(rt, parse_halt(token_stream, tmp, err));
            }
        } else {
            *err = throw_error("Unexpected node");
        }

        // If the error is set to something, assume hell has broken loose.
        if (*err) return NULL;

    }

    // If the error is set to something, assume hell has broken loose.
    if (*err) return NULL;

    // Return rt
    return rt;

}