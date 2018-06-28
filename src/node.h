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

#include "utils/log.h"
#include "token.h"


/**
 *  The differnet types a node can be,
 *  The differnet types of operation,
 *  and the different type of command
 */
typedef enum {
    NTYPE_LDR,
	NTYPE_STR,
	NTYPE_ADD,
	NTYPE_SUB,
	NTYPE_MOV,
	NTYPE_CMP,
	NTYPE_B,
	NTYPE_AND,
	NTYPE_ORR,
	NTYPE_EOR,
	NTYPE_MVN,
	NTYPE_LSL,
	NTYPE_LSR,
	NTYPE_HALT
} node_type;

typedef enum {
    NOP_REGISTER,
    NOP_LITERAL
} node_op_type;

typedef enum {
    NCMP_NONE,
    NCMP_EQUAL,
    NCMP_NEQUAL,
    NCMP_GREATER,
    NCMP_LESS
} node_cmp_type;


/**
 *  Node values.
 * 
 *  node_mem    -   Used for commands like LDR where memory is moved to registers
 *  node_op     -   Used for commands like MOV where either register or numbers are moved to a register
 *  node_on_on  -   Used for commands like ADD where a register and (number or register) is added and stored to a register.
 *  node_b      -   Used for commands like B where we are branching to a different place
 */
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
    node_cmp_type cond;
} node_b;


/**
 *  Structure of a node type
 * 
 *  node_type type      -   The type of node, for example NTYPE_LDR
 *  void* value         -   The value of the ndoe, for example node_mem
 *  char* test_id       -   Debugging which will be removed soon
 */
typedef struct node {
    node_type type;
    void* value;
    int memory_ref;
} node;


/**
 *  Structure of a nodearray
 * 
 *  node **value        -   The array of nodes.
 *  int elements        -   The amount of elements in the array
 *  int allocated       -   The amount of memory we allocated.
 * 
 */
typedef struct nodearray {
    node **value;
    int elements;
    int allocated;
    int base_address;
} nodearray;


// Nodearray functions
nodearray* nodearray_new();
int nodearray_push(nodearray* array, node* item);
void nodearray_dump(nodearray* array);
void node_dump(node* node);

#endif