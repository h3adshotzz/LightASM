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


typedef struct ast {
    TokenStream* toks;
} ast;

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

typedef struct node {
    node_type type;
    void* value;
} node;

typedef enum {
    NOP_REGISTER,
    NOP_LITERAL
} node_op_type;

typedef struct {
    int dest;
    int source;
    node_op_type type;
    int value;
} node_op_on;

typedef struct {
    int dest;
    node_op_type type;
    int value;
} node_op;

typedef enum {
    NCMP_NONE,
    NCMP_EQUAL,
    NCMP_NEQUAL,
    NCMP_GREATER,
    NCMP_LESS
} node_cmp_type;

typedef struct {
    char* target;
    node_cmp_type cond;
} node_b;

typedef struct nodearray {
    node **value;
    int elements;
    int allocated;
} nodearray;


// nodearray.c functions
nodearray* nodearray_new();
int nodearray_push(nodearray* array, node* item);

#endif