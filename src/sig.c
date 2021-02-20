//#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
//#include <dlfcn.h>
#include <stdio.h>

#include "log.h"

void handler(int sig)
{
    log_info("signal %d:\n", sig);
    exit(1);
}

void _init(void)
{
    log_info("Loading signal handler.\n");
    signal(SIGTRAP, handler);
}
