/**
 * LightASM Compiler
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

#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include <gio/gio.h>

#include "token.h"
#include "parser.h"
#include "consts.h"
#include "node.h"

static gboolean version = false;
static gboolean debug = false;

static GOptionEntry entries[] =
{
  { "version", 'v', 0, G_OPTION_ARG_NONE, &version, "Show version info", NULL },
  { "debug", 0, 0, G_OPTION_ARG_NONE, &debug, "Be debug", NULL },
  { NULL }
};

void show_version()
{
    printf("LightASM Compiler %d.%d [%d]\n\n", LIGHT_ASM_MAJOR_VERSION, LIGHT_ASM_MINOR_VERSION, LIGHT_ASM_BUILD);
}

void dump_array(gpointer key, gpointer value, gpointer data) 
{
    printf("Key: %s, Value: %s\n", (char *) key, (char *) value);
}

void testing(char* path)
{
    printf("EXPERIMENTAL_MODE\n");


    // memory testing
    GHashTable *table = g_hash_table_new(g_str_hash, g_str_equal);

    g_hash_table_insert(table, "hello", "world");
    g_hash_table_insert(table, "hello2", "123");

    g_hash_table_foreach(table, dump_array, NULL);

    GFile *file = g_file_new_for_commandline_arg (path);
    
    GError *error = NULL;
    GFileInputStream *input = g_file_read (file, NULL, &error);

    if (error) {
        g_critical ("%s", error->message);
        exit(EXIT_FAILURE);
    }

    TokenStream *stream = token_stream_new (G_INPUT_STREAM (input));
    Token* tmp = NULL;

    //
    GPtrArray* ptr = g_ptr_array_new();

    GPtrArray* nodes = parse (stream, table);
    for (int i = 0; i < nodes->len; i++) {
        node_dump ((node*) g_ptr_array_index (nodes, i));
    }

    while ((tmp = token_stream_next(stream))) {
        g_ptr_array_add(ptr, (gpointer) tmp);
    }

    printf("Size: %d\n", ptr->len);

    // print the array.
    for (int i = 0; i < ptr->len; i++) {
        token_dump((Token*) g_ptr_array_index(ptr, i));
    }


    /// other testing
    GPtrArray *testing = g_ptr_array_new();
    for (int i = 0; i < 10; i++) {
        char* str = "Hello";
        g_ptr_array_add(testing, str);
    }

    for (int i = 0; i < testing->len; i++) {
        printf("Val %d: %s\n", i, (char *) g_ptr_array_index(testing, i));
    }
}

int main(int argc, char** argv)
{
    GError *error = NULL;
    GOptionContext *context;

    context = g_option_context_new("- LightASM Compiler.");
    g_option_context_add_main_entries(context, entries, NULL);

    if (!g_option_context_parse(context, &argc, &argv, &error)) {
        g_critical("option parsing failed: %s\n", error->message);
        exit (1);
    }

    if (version) {
        show_version();
    }

    // 
    testing(argv[1]);
    

    return 0;
}