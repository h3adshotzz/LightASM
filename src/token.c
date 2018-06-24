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

#include "token.h"


/**
 * LightASM Keywords
 */
char* g_keywords[] = {"MOV", "SUB"};


/**
 * Function to create a new Token
 */
Token* token_new(char* val, char type) {

    // Malloc's our friend. 
    Token* tol = malloc(sizeof(Token));

    // Assign the token values whatever we gave
    tol->type = type;
    tol->val = val;

    // Return big boi
    return tol;

}


/**
 * Function to create a new TokenStream
 */
TokenStream* token_stream_new(char* input) {

    // Hello Bosssss, can i haz memz? 
    TokenStream* stream = malloc(sizeof(TokenStream));

    // Set posiiton, source and token cache
    stream->position = 0;
    stream->source = input;
    stream->cache = NULL;   // Nothing to cache yet.

    // Return
    return stream;
}


/**
 *  Some complaints about this in token.h...
 */
static char* read_string(TokenStream* stream, int (*reader)(int)) {

    // Result string and counter
    char* str = "";
    int counter = stream->position;

    // Check that we haven't gone past the end of the string
    while (stream->source[counter]) {

        // Get the current char
        char curr = stream->source[counter]; 

        // If the character is acceptable, append. Else, You end up in ze cooler. 
        if (reader(curr)) {
            str = chrappend(str, curr);
        } else {
            break;
        }

        // Advance the counter
        counter++;
    }

    // Store the new position
    stream->position = counter;

    return str;

}

Token* token_stream_next(TokenStream* tknstr, TokenError** err) {

    // Skip spaces, tabs & newlines ext
    read_string(tknstr, &isspace);
  
    // Peek at the next letter
    char next_char = tknstr->source[tknstr->position];

    if (!next_char) {
        return NULL; 
    } else if (next_char == 'R') {
        
        tknstr->position++;
        char* str = read_string(tknstr, &isdigit);
        return token_new(str, TOK_REGISTER);
      
    } else if (isalpha(next_char)) {    // Check wether the char is a command

        // If the char is an alpha, send it to read_token_string.
        char* str = read_string(tknstr, &isalpha);

        if (array_contains(str, g_keywords)) {
            return token_new(str, TOK_COMMAND);       // Return a command token
        } else {
            return token_new(str, TOK_LABEL);         // Return a label token
        }

    } else if (next_char == '#') {      // A number is next

        tknstr->position++;
        char* str = read_string(tknstr, &isdigit);
        return token_new(str, TOK_NUMBER);

    } else if (next_char == ',') {  // if next char is a comma

        tknstr->position++;
        return token_new(NULL, TOK_COMMA);

    } else if (isdigit(next_char)) {

        char* str = read_string(tknstr, &isdigit);
        return token_new(str, TOK_MEMORY);

    } else {
        *err = throw_token_error("Invalid input");
        return NULL;
    }

    // MOV  R5, #22     Moving a number
    // MOV  R2, 231     Moving memory

}

void token_dump (Token* self) {
    if (!self) {
        debugf("TOKEN: self is null");
        return;
    }
    switch (self->type) {
        case TOK_COMMAND:
            debugf("TOKEN: Command: %s", self->val);
            break;
        case TOK_NUMBER:
            debugf("TOKEN: Number: %s", self->val);
            break;
        case TOK_MEMORY:
            debugf("TOKEN: Memory: %s", self->val);
            break;
        case TOK_REGISTER:
            debugf("TOKEN: Register: %s", self->val);
            break;
        case TOK_LABEL:
            debugf("TOKEN: Label: %s", self->val);
            break;
        case TOK_COMMA:
            debugf("TOKEN: Comma");
            break;
        default:
            debugf("TOKEN: Unknown type");
    }
}