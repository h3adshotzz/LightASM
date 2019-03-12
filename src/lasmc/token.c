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

static char* g_keywords[14] = {"nop", "halt", "mov", "add", "sub"};

int array_contains(char* val, char** arr) {
    int i = 0;
    while (arr[i]) {
        if (strcmp(arr[i], val) == 0) {     // We get a BAD ACCESS if you type something that isn't a command
            return 1;
        }
        i++;
    }
    return 0;
}

Token *token_new(char *val, char type)
{
    Token *tkn = malloc(sizeof(Token));

    tkn->type = type;
    tkn->val = val;

    return tkn;
}

TokenStream *token_stream_new(char *input)
{
    TokenStream *stream = malloc(sizeof(TokenStream));

    stream->position = 0;
    stream->source = input;
    stream->cache = NULL;

    return stream;
}

static char *read_string(TokenStream *stream, int (*reader)(int))
{
    char *str = "";
    int counter = stream->position;

    while (stream->source[counter]) {

        char curr = stream->source[counter];

        if (reader(curr)) {
            str = chrappend(str, curr);
        } else {
            break;
        }

        counter++;
    }

    stream->position = counter;

    return str;
}

Token *token_stream_next(TokenStream *stream)
{
    read_string(stream, &isspace);

    char next_char = stream->source[stream->position];

    if (!next_char) {
        return NULL;
    } else if (next_char == 'R' || next_char == 'r') {

        // Parsing register names
        stream->position++;
        char* str = read_string(stream, &isdigit);
        return token_new(str, TOK_REGISTER);

    } else if (isalpha(next_char)) {

        // Parsing instruction keywords 
        char* str = read_string(stream, &isalpha);

        if (array_contains(str, g_keywords)) {
            return token_new(str, TOK_COMMAND);
        } else {
            return token_new(str, TOK_LABEL);
        }

    } else if (next_char == '#') {

        // Parsing a number
        stream->position++;
        char* str = read_string(stream, &isdigit);
        return token_new(str, TOK_NUMBER);

    } else if (next_char == ',') {

        // Parsing a comma
        stream->position++;
        return token_new(NULL, TOK_COMMA);

    } else if (isdigit(next_char) && stream->source[stream->position++] == 'x') {

        // Parsing a memory address
        char* str = read_string(stream, &isdigit);
        return token_new(str, TOK_MEMORY);

    } else {
        return NULL;
    }
}

void token_dump(Token* tkn)
{
   if (!tkn) {
        debugf("TOKEN: tkn is null");
        return;
    }

    // Switch-case to print the Tokens type
    switch (tkn->type) {
        case TOK_COMMAND:
            debugf("TOKEN: Command: %s", tkn->val);
            break;
        case TOK_NUMBER:
            debugf("TOKEN: Number: %s", tkn->val);
            break;
        case TOK_MEMORY:
            debugf("TOKEN: Memory: %s", tkn->val);
            break;
        case TOK_REGISTER:
            debugf("TOKEN: Register: %s", tkn->val);
            break;
        case TOK_LABEL:
            debugf("TOKEN: Label: %s", tkn->val);
            break;
        case TOK_COMMA:
            debugf("TOKEN: Comma");
            break;
        default:
            debugf("TOKEN: Unknown type");
    }
}