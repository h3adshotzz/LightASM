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

#ifndef NODE_H
#define NODE_H

#include <glib.h>

typedef enum {
    NTYPE_ADD,
    NTYPE_SUB,
    NTYPE_MOV,
    NTYPE_NOP,
    NTYPE_HALT
} node_type;

typedef enum {
    NOP_REGISTER,
    NOP_LITERAL
} node_op_type;

typedef enum {
    NCOND_NONE,
    NCOND_EQUAL,
    NCOND_NEQUAL,
    NCOND_GREATER,
    NCOND_LESS
} node_condition_type;


/////////////

typedef struct {
    int reg;
    int mem;
} node_mem;

typedef struct {
    int dest;
    node_op_type type;
    int value;
} node_op;

typedef struct {
    int dest;               // First reg
    int source;             // Seccond reg
    node_op_type type;      // Num or reg
    int value;              // Number?

} node_op_on;

typedef struct {
    char* target;
    node_condition_type cond;
} node_b;


///////

typedef struct {
    node_type type;
    /*union value {
        node_op op;
        node_op_on op_on;
        node_b b;
    } value;
    //int mem_ref;*/
    gpointer* val;
} node;


////
node* node_new(node_type type, gpointer* value);



#endif