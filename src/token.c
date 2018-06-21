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
char* readString(TokenStream* stream, int (*reader)(int)) {

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


/**
 *  Check whether given 'x' is a keyword
 */
int is_keyword(char* x) {
    return array_contains(x, keywords);
}

Token* nextToken(TokenStream* tknstr, TknError** err) {

    // Peek at the next letter
    char next_char = tknstr->source[tknstr->position];
    
    // check is char is a register
    if (!next_char) {
        return NULL;
    } else if (next_char == 'R') {
         
        tknstr->position++;
        char* str = readString(tknstr, &isdigit);
        return createToken(str, TOK_REGISTER);

    } else if (isalpha(next_char)) {    // Check wether the char is a command

        // If the char is an alpha, send it to readString.
        char* str = readString(tknstr, &isalpha);

        if (is_keyword(str)) {
            return createToken(str, TOK_COMMAND);       // Return a command token
        } else {
            return createToken(str, TOK_LABEL);         // Return a label token
        }

    } else if (next_char == '#') {      // A number is next

        tknstr->position++;
        char* str = readString(tknstr, &isdigit);
        return createToken(str, TOK_NUMBER);

    } else if (next_char == ',') {  // if next char is a comma

        tknstr->position++;
        return createToken(NULL, TOK_COMMA);

    } else if (isdigit(next_char)) {

        char* str = readString(tknstr, &isdigit);
        return createToken(str, TOK_MEMORY);

    } else {
        *err = throw_token_error("Invalid input");
        return NULL;
    }

    // MOV  R5, #22     Moving a number
    // MOV  R2, 231     Moving memory

}