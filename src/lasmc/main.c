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

#include "consts.h"

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
    printf("Key: %s, Value: %s\n", key, value);
}

char* lower_string(char* s) {
   int c = 0;
   
   while (s[c] != '\0') {
      if (s[c] >= 'A' && s[c] <= 'Z') {
         s[c] = s[c] + 32;
      }
      c++;
   }

   return s;
}

void testing(char* path)
{
    printf("EXPERIMENTAL_MODE\n");

    GHashTable *table = g_hash_table_new(g_str_hash, g_str_equal);

    g_hash_table_insert(table, "hello", "world");
    g_hash_table_insert(table, "hello2", "123");

    g_hash_table_foreach(table, dump_array, NULL);

    char *line;
    size_t len = 0;
    ssize_t nread;

    FILE *file = fopen(path, "r");
    if (file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    while ((nread = getline(&line, &len, file)) != -1) {

        line = lower_string(line);

        printf("Retrieved line of length %zu:\n", nread);
        printf("Line[%d]: %s\n", nread, line);
        
        //
        int num = (int)strtol(line, NULL, 16); 
        printf("0x%X\n", num);


    }

    free(line);
    fclose(file);
    
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