/*
 * File      : main.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2015, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published 
 *  by the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-05-02     Bernard      First version
 */

#include <dfs_posix.h>

#include <stdlib.h>
#include <string.h>

#include <mujs.h>

int printf(const char* fmt, ...);

static const char *require_js =
	"function require(name) {\n"
	"var cache = require.cache;\n"
	"if (name in cache) return cache[name];\n"
	"var exports = {};\n"
	"cache[name] = exports;\n"
	"Function('exports', read(name+'.js'))(exports);\n"
	"return exports;\n"
	"}\n"
	"require.cache = Object.create(null);\n"
;

static void jsB_gc(js_State *J)
{
	int report = js_toboolean(J, 1);
	js_gc(J, report);
	js_pushundefined(J);
}

static void jsB_print(js_State *J)
{
	unsigned int i, top = js_gettop(J);
	for (i = 1; i < top; ++i) {
		const char *s = js_tostring(J, i);
		if (i > 1) printf(" ");
		printf(s);
	}
	printf("\n");
	js_pushundefined(J);
}

static void jsB_load(js_State *J)
{
	const char *filename = js_tostring(J, 1);
	int rv = js_dofile(J, filename);
	js_pushboolean(J, !rv);
}

static void jsB_write(js_State *J)
{
	unsigned int i, top = js_gettop(J);
	for (i = 1; i < top; ++i) {
		const char *s = js_tostring(J, i);
		if (i > 1) putchar(' ');
		puts(s);
	}
	js_pushundefined(J);
}

void usage(void)
{
	printf("mnode - js framework for MCU\n");
	printf("mnode js_file\n");

	return;
}

int main(int argc, char** argv)
{
	int fd;
	js_State *J;
	char *str;

	if (argc != 2)
	{
		usage();

		return 0;
	}

	J = js_newstate(NULL, NULL, JS_STRICT);

	js_newcfunction(J, jsB_gc, "gc", 0);
	js_setglobal(J, "gc");

	js_newcfunction(J, jsB_load, "load", 1);
	js_setglobal(J, "load");

	js_newcfunction(J, jsB_print, "print", 1);
	js_setglobal(J, "print");

	js_newcfunction(J, jsB_write, "write", 0);
	js_setglobal(J, "write");

	js_dostring(J, require_js, 0);

	fd = open(argv[1], O_RDONLY, 0);
	if (fd >= 0)
	{
		int length;
		
		length = lseek(fd, 0, SEEK_END);
		// printf("js script length=%d\n", length);
		lseek(fd, 0, SEEK_SET);

		if (length <= 0) 
		{
			js_freestate(J);
			close(fd);
			return -1;
		}

		str = (char*) malloc (length + 1);
		if (str == NULL)
		{
			js_freestate(J);
			close(fd);
			return -1;
		}

		memset(str, 0, length + 1);
		read(fd, str, length);
		close(fd);
		str[length] = '\0';

		// printf("js script: \n%s\n", str);

		js_dostring(J, str, 1);
		free(str);
	}

	js_freestate(J);

	return 0;
}
