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

#include "node.h"

GPtrArray* node_ptrarray_new()
{
    return g_ptr_array_new();
}

void node_ptrarray_push(GPtrArray* arr, node* node)
{
    g_ptr_array_add(arr, (gpointer) node);
}

/**
 * Node for an instruction that has no associated values
 * 
 * i.e. HALT
 */
node* node_new (node_type type, node_condition_type cond)
{
    node* node = malloc(sizeof(node));

    node->type = type;
    node->cond = cond;

    return node;
}

/**
 * Node that holds a register and an operand
 * 
 * i.e. MOV, STR
 */
node *
node_new_op (node_type type, node_condition_type cond, node_op op)
{
    node* node = malloc(sizeof(node));

    node->type = type;
    node->cond = cond;
    node->value.op = op;

    return node;
}

/**
 * Node that holds two registers and an operand
 * 
 * Largly used for arithmetic, i.e. ADD, SUB
 */
node *
node_new_op_on (node_type type, node_condition_type cond, node_op_on op_on)
{
    node* node = malloc(sizeof(node));

    node->type = type;
    node->cond = cond;
    node->value.op_on = op_on;

    return node;
}

/**
 * Node that targets a label
 * 
 * i.e. B
 */
node *
node_new_target (node_type type, node_condition_type cond, char* target)
{
    node* node = malloc(sizeof(node));

    node->type = type;
    node->cond = cond;
    node->value.target = g_strdup (target);

    return node;
}

void
node_dump (node *self)
{
    g_print ("NODE: %i[%i]\n", self->type, self->cond);
}