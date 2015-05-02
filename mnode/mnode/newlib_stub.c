#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <reent.h>

struct _reent* _impure_ptr = NULL;

int __swbuf_r(struct _reent *ptr, register int c, register FILE* fp)
{
	return 0;
}

void __assert_func(const char *file, int line, const char* func, const char *failedexpr)
{
	rt_kprintf("assertion \"%s\" failed: file \"%s\", line %d%s%s\n",
	   failedexpr, file, line,
	   func ? ", function: " : "", func ? func : "");


	abort();
	/* NOTREACHED */
}

int *__errno (void)
{
	return &_REENT->_errno;
}

int __fpclassifyd (double x)
{
	return 0;
}

int __signbitd (double x)
{
	return 0;
}
