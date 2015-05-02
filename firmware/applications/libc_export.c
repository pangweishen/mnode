#include <rtthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <setjmp.h>

#pragma import(__use_no_semihosting_swi)

/* memory routines */
RTM_EXPORT(malloc);
RTM_EXPORT(free);
RTM_EXPORT(realloc);

RTM_EXPORT(memcmp);
RTM_EXPORT(memcpy);
RTM_EXPORT(memset);
RTM_EXPORT(strcat);
RTM_EXPORT(strchr);
RTM_EXPORT(strcmp);
RTM_EXPORT(strcpy);
RTM_EXPORT(strlen);
RTM_EXPORT(strncmp);
RTM_EXPORT(strstr);
RTM_EXPORT(strtol);

/* time routines */
time_t time (time_t* timer)
{
    return 0;
}
RTM_EXPORT(time);
RTM_EXPORT(localtime);
RTM_EXPORT(gmtime);
RTM_EXPORT(mktime);

/* jmp routines */
RTM_EXPORT(longjmp);
RTM_EXPORT(setjmp);

/* IO routines */
RTM_EXPORT(printf);
RTM_EXPORT(putchar);
RTM_EXPORT(puts);
RTM_EXPORT(snprintf);
RTM_EXPORT(sprintf);
RTM_EXPORT(vfprintf);
RTM_EXPORT(vsnprintf);
RTM_EXPORT(fclose);
RTM_EXPORT(fopen);
RTM_EXPORT(fprintf);
RTM_EXPORT(fputc);
RTM_EXPORT(fputs);
RTM_EXPORT(fgets);
RTM_EXPORT(fread);
RTM_EXPORT(fseek);
RTM_EXPORT(ftell);
RTM_EXPORT(fwrite);

/* misc routines */
RTM_EXPORT(rand);
RTM_EXPORT(abort);
RTM_EXPORT(atoi);
RTM_EXPORT(exit);
