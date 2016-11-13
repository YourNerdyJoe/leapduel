#ifndef _DEBUG_H_
#define _DEBUG_H_

#define DBG_ERROR "[ERROR!] "
#define DBG_WARNING "[WARNING] "

bool dbgInit(const char* filename);
void dbgExit();

void dbgPrint(const char* s, ...);

#endif
