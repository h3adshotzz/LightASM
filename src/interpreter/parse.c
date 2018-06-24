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
 *  Z's DM so i dont have to keep switching window
 * 
 * 
 * Here we have a MOV command, clearly a MOV is a single node

But as the demo is showing it's made up of 4 tokens

The job of parse() is to look at it and say

"if it ain't command or label it's defently wrong"

Then "if it ain't one of these commands something is messed up"

Now "Ohhh okay it's a MOV"

"So i need a Register then a Comma followed by a Number or Memory, anything else is an error"

and then build the node and nodearray_push it


*
 *  node struct reminder
 * 
 *  node_type type
 *  void* value
 * 
 *

 * 
 */
nodearray* parse(TokenStream* token_stream) {

    // Create the node array that we are going to return
    nodearray* rt = nodearray_new();

    Token* tkn = NULL;
    TokenError* err = NULL;

    while ((tkn = token_stream_next(token_stream, &err))) {
        
        if (tkn->type == TOK_COMMAND){

            char* cmd = tkn->val;
            node* node = malloc(sizeof(node));

            if (!strcmp(cmd, "MOV")) {
                node->type = NTYPE_MOV;
                debugf("Command type MOV");
            } else if (!strcmp(cmd, "SUB")) {
                node->type = NTYPE_SUB;
                debugf("Command type SUB");
            }


        }

    }

    return NULL;

}