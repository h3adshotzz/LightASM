/**
 * LightASM
 * Copyright (C) 2017, Is This On? 
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

#include <stdio.h>

#define REGISTER_COUNT  12  // Array shit
#define REGISTER_DEFAULT_VAL    -1

typedef enum {
    REGISTER_R0 = 0,
    REGISTER_R1 = 1,
    REGISTER_R2 = 2,
    REGISTER_R3 = 3,
    REGISTER_R4 = 4,
    REGISTER_R5 = 5,
    REGISTER_R6 = 6,
    REGISTER_R7 = 7,
    REGISTER_R8 = 8,
    REGISTER_R9 = 9,
    REGISTER_R10 = 10,
    REGISTER_R11 = 11
} reg_t;

int register_state[REGISTER_COUNT] = {0,1,2,3,4,5,6,7,8,9,10,11};