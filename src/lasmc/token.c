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
#include <glib.h>
#include <gio/gio.h>

// Err you realise this is going to go bad?
static const char* g_keywords[14] = {"nop", "halt", "mov", "add", "sub"};

Token *token_new(char *val, char type)
{
    Token *tkn = g_new (Token, 1);

    tkn->type = type;
    tkn->val = val;

    return tkn;
}

TokenStream *token_stream_new(GInputStream *input)
{
    g_return_val_if_fail (G_IS_INPUT_STREAM (input), NULL);

    TokenStream *stream = g_new(TokenStream, 1);

    stream->source = g_data_input_stream_new (input);
    stream->cache = NULL;
    stream->line = NULL;
    stream->curr = NULL;

    return stream;
}

static gboolean
read_line (TokenStream *self)
{
    GError *error = NULL;

    if (self->line)
        g_free (self->line);

    gchar *read = g_data_input_stream_read_line_utf8 (self->source,
                                                      NULL, NULL, &error);

    self->line = g_strconcat (read, "\n", NULL);
    self->curr = self->line;

    g_free (read);

    if (error) {
        g_critical ("Failed to read input: %s", error->message);
        return FALSE;
    }

    if (!self->line)
        return FALSE;

    return TRUE;
}

static gboolean
peek_char (TokenStream *self, gunichar *c)
{
    if ((!self->curr || !g_utf8_get_char (self->curr)) && !read_line (self)) {
        return FALSE;
    }

    if (c)
        *c = g_utf8_get_char (self->curr);

    return TRUE;
}

static gboolean
next_char (TokenStream *self, gunichar *c)
{
    if ((!self->curr || !g_utf8_get_char (self->curr)) && !read_line (self)) {
        return FALSE;
    }
    
    if (!self->curr)
        return FALSE;

    if (c)
        *c = g_utf8_get_char (self->curr);

    self->curr = g_utf8_next_char (self->curr);

    return TRUE;
}

static char *read_string(TokenStream *stream, int (reader)(gunichar))
{
    char *str = NULL;
    gunichar curr;

    while (peek_char (stream, &curr)) {
        if (reader(curr)) {
            int len;
            char *buf = NULL;
            char *tmp = NULL;

            len = g_unichar_to_utf8 (curr, NULL);

            buf = g_malloc (len);
            g_unichar_to_utf8 (curr, buf);
            buf[len] = '\0';

            if (str) {
                tmp = g_strconcat (str, buf, NULL);

                // g_strconcat/g_strdup allocate heap memory
                // we must free the memory when done with it
                // to prevent leaks
                g_free (str);
            } else {
                tmp = g_strdup(buf);
            }

            g_free (buf);

            str = tmp;
        } else {
            break;
        }

        next_char (stream, NULL);
    }

    return str;
}

static gboolean
label (gunichar c)
{
    return c != ':';
}

Token *token_stream_next(TokenStream *stream)
{
    read_string (stream, g_unichar_isspace);

    gunichar next;

    if (!peek_char (stream, &next)) {
        return NULL;
    }

    if (next == 'R' || next == 'r') {

        // Parsing register names
        next_char (stream, NULL);
        char* str = read_string (stream, g_unichar_isdigit);
        return token_new(str, TOK_REGISTER);

    } else if (g_unichar_isalpha(next)) {

        // Parsing instruction keywords 
        char* str = read_string (stream, label);
        char* lower = g_utf8_strdown (str, -1);

        if (g_strv_contains (g_keywords, lower)) {
            return token_new (lower, TOK_COMMAND);
        } else {
            return token_new(str, TOK_LABEL);
        }

    } else if (next == '#') {

        // Parsing a number
        next_char (stream, NULL);
        char* str = read_string (stream, g_unichar_isdigit);
        return token_new(str, TOK_NUMBER);

    } else if (next == ',') {

        // Parsing a comma
        next_char (stream, NULL);
        return token_new(NULL, TOK_COMMA);

    } else if (g_unichar_isdigit (next)) {

        // Parsing a memory address
        char* str = read_string (stream, g_unichar_isdigit);
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