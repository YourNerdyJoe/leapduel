#include "debug.h"
#include <stdio.h>
#include <stdarg.h>

//#define DEBUG_CONSOLE 1

static FILE* f = nullptr;

bool dbgInit(const char* filename)
{
	#ifdef DEBUG_CONSOLE
		f = stdout;
	#else
		f = fopen(filename,"w");
	#endif

	dbgPrint("********** Debug Init **********\n");

	return f != nullptr;
}

void dbgExit()
{
	dbgPrint("********** Debug Exit **********\n");

	#ifndef DEBUG_CONSOLE
		fclose(f);
	#endif

	f = nullptr;
}

void dbgPrint(const char* s, ...)
{
	if(f == nullptr) return;

	va_list ap;
	char buffer[256];

	va_start(ap,s);

	vsprintf(buffer, s, ap);
		
	fprintf(f, buffer);
	fflush(f);

	va_end(ap);
}
