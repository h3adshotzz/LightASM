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


// Token functions.
Token* token_new(char* val, char type);
void token_dump (Token* self);

// TokenStream functions.
TokenStream* token_stream_new(char* input);
Token* token_stream_next(TokenStream* tknstr, Error** err);
int token_stream_eof(TokenStream* tok);




#endif