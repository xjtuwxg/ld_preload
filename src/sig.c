#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>
#include <stdio.h>

void handler(int sig)
{
    printf("Error: signal %d:\n", sig);
    printf("I can do whatever I want in here!\n");
    exit(1);
}

void _init(void)
{
    printf("Loading signal handler.\n");
    signal(SIGTRAP, handler);
}
