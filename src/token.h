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

#ifndef TOKEN_H
#define TOKEN_H

#include <stdlib.h>
#include <ctype.h>

#include "string.h"
#include "array_contains.h"
#include "utils/error.h"

/*
    Token Types

    MOV R1, #42

    Tokens for this?

    MOV         R2           ,         #42
    TOK_COMMAND TOK_REGISTER TOK_COMMA TOK_NUMBER

*/
#define TOK_COMMAND     '0'
#define TOK_NUMBER      '1'
#define TOK_MEMORY      '2'
#define TOK_REGISTER    '3'
#define TOK_LABEL       '4'
#define TOK_COMMA       '5'

typedef struct {
    char* val;      // String contents of token
    char type;      // Token type
} Token;

typedef struct { 
    size_t position;    // To determain where in the string (source) we are
    char* source;       // The users input, what we are token...ing
    Token* cache;       // Token cache
} TokenStream;


// Where each cmd is in the g_keywords array.
#define MOV_KW_POS      0
#define SUB_KW_POS      1
#define ADD_KW_POS      2
#define STR_KW_POS      3
#define LDR_KW_POS      4
#define CMP_KW_POS      5
#define B_KW_POS        6
#define AND_KW_POS      7
#define ORR_KW_POS      8
#define EOR_KW_POS      9
#define MVN_KW_POS      10
#define LSL_KW_POS      11
#define LSR_KW_POS      12
#define HALT_KW_POS     13

#define KW_SIZE         14

/**
 * LightASM Keywords
 */
extern char* g_keywords[KW_SIZE];

// @zistooshort tried to explain this to me but me no get it :(
// Apparently it defines a type (Reader) which is a pointer to a function which takes char and returns bool.
//typedef bool (*Reader)(char);

// Functions. They are commented in token.c

Token* token_new(char* val, char type);
void token_dump (Token* self);

TokenStream* token_stream_new(char* input);
Token* token_stream_next(TokenStream* tknstr, TokenError** err);
int token_stream_eof(TokenStream* tok);

#endif