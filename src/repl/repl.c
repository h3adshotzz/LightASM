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

#include "repl.h"

void
my_wait(size_t secs)
{
	#ifdef _WIN32
		Sleep(1000 * secs);
	#else
		sleep(secs);
	#endif
}

void print_progress(size_t count, size_t max) {
	size_t i = 0;

    printf("\rProgress: [");
	for (; i < max; ++i) {
        printf("%c", i < count ? '#' : ' ');
	}
    printf("]");
	fflush(stdout);
}

#define NUM_SECS 10

void print_registers() {


}

void _repl_test() {

    /*size_t num_secs = 1, max_secs = NUM_SECS;
	printf("%s\n", "");
	print_progress(0, max_secs);
	for (; num_secs <= max_secs; ++num_secs)
	{
		my_wait(1);
		print_progress(num_secs, max_secs);
	}*/

	
	printf("\r   0  MOV R1, #23\n=>  1  ADD R0, R1, R2");
	fflush(stdout);

	my_wait(1);
	
	printf("\r   1  ADD R0, R1, R2\n=>  2  STR R0, 4");
	fflush(stdout);

}