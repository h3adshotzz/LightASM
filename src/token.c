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

#include "token.h"


/**
 * LightASM Keywords
 */
char* keywords[] = {"MOV", "SUB"};


/**
 * Function to create a new Token
 */
Token* createToken(char* val, char type) {

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
TokenStream* createTokenStream(char* input) {

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
char* readString(TokenStream* stream, int (*reader)(char)) {

    // Result string and counter
    char* str = "";
    int counter = stream->position;

    // Check that we haven't gone past the end of the string
    while (stream->source[counter]) {

        // Get the current char
        char curr = stream->source[counter]; 
    
        // Advance the counter
        counter++;

        // If the character is acceptable, append. Else, You end up in ze cooler. 
        if (reader(curr)) {
            str = chrappend(str, curr);
        } else {
            break;
        }

    }

    // Store the new position
    stream->position = counter;

    return str;

}


/**
 *  Check whether given 'x' is a keyword
 */
int is_keyword(char* x) {
    return array_contains(x, keywords);
}

Token* nextToken(TokenStream* tknstr, Err** err) {

    char next_char = tknstr->source[tknstr->position];
    
    if (isalpha(next_char)) {
       //readString();
    }

}