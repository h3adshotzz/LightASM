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
    NOP_IMMEDIATE
} node_op_type;

typedef enum {
    NCOND_NONE,
    NCOND_EQUAL,
    NCOND_NEQUAL,
    NCOND_GREATER,
    NCOND_LESS
} node_condition_type;

/**
 * Register number
 * 
 * Only 4bits are available to store the register number by
 * C doesn't allow us to operate on less than 8bits
 */
typedef char reg;

/////////////

typedef struct {
    reg          dest;         // Register
    node_op_type type;         // Register or immediate
    int          value;        // Regsister, memory address (16 bit) or number to encode
} node_op;

typedef struct {
    node_op op;
    reg     source;            // Second reg
} node_op_on;

///////

typedef struct {
    node_type type;            // Type of node (MOV, ADD...)
    node_condition_type cond;  // Condition for executing this instruction
    union {                    // Use a union to reduce memory usage
        node_op op;            // Holds a register and an operand
        node_op_on op_on;      // Holds two registers and an operand
        char* target;          // Label this instuction targets
    } value;
} node;


////
node* node_new        (node_type            type,
                       node_condition_type  cond);
node* node_new_op     (node_type            type,
                       node_condition_type  cond,
                       node_op              op);
node* node_new_op_on  (node_type            type,
                       node_condition_type  cond,
                       node_op_on           op_on);
node* node_new_target (node_type            type,
                       node_condition_type  cond,
                       char                *target);
void  node_dump       (node                *self);


#endif