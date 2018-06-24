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

// @zistooshort tried to explain this to me but me no get it :(
// Apparently it defines a type (Reader) which is a pointer to a function which takes char and returns bool.
//typedef bool (*Reader)(char);

// Functions. They are commented in token.c
Token* create_new_token(char* val, char type);
TokenStream* create_new_token_stream(char* input);
Token* next_token(TokenStream* tknstr, TokenError** err);
void token_dump (Token* self);

#endif