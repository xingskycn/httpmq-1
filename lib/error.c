#include "head.h"
#include<stdarg.h>
void err_quit(char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vprintf(fmt, ap);
	printf("\n");
	perror("error:");
	exit(-1);
}

void err_sys(char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vprintf(fmt, ap);
	printf("\n");
	perror("error:");
	exit(-2);
}
