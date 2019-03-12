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

char *lower_string(char *s)
{
    int c = 0;

    while (s[c] != '\0') {
        if (s[c] >= 'A' && s[c] <= 'Z') {
            s[c] = s[c] + 32;
        }
        c++;
    }

    return s;
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

    } else if (isalpha(next_char)) {

        // Parsing instruction keywords 

    } else if (next_char == '#') {

        // Parsing a number

    } else if (next_char == ',') {

        // Parsing a comma

    } else if (isdigit(next_char) && stream->source[stream->position++] == 'x') {

        // Parsing a memory address

    } else {
        return NULL;
    }
}

void token_dump(Token* tkn)
{
    // Sort this out.
}