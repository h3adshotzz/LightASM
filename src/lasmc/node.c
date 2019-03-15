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

void node_dump(node* node)
{

}

GPtrArray* node_ptrarray_new()
{
    return g_ptr_array_new();
}

void node_ptrarray_push(GPtrArray* arr, node* node)
{
    g_ptr_array_add(arr, (gpointer) node);
}

node* node_new(node_type type, gpointer* value)
{
    node* node = malloc(sizeof(node));

    node->type = type;
    node->val = value;

    return node;
}