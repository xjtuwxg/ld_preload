#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define __USE_GNU
#include <signal.h>
#include <ucontext.h>

#include "log.h"

void handler(int sig, siginfo_t *si, void* arg)
{
	ucontext_t *context = (ucontext_t *)arg;
	static int sig_cnt = 0;

	log_info("signal #%d. rip: 0x%llx (%d)", sig,
		 context->uc_mcontext.gregs[REG_RIP], ++sig_cnt);

	// Modify RIP here (we advance the rip by 2 -- skip two int3 instrs):
#if 0
	context->uc_mcontext.gregs[REG_RIP] = context->uc_mcontext.gregs[REG_RIP]
		+ 0x02;
#endif
	//exit(1);
}

void _init(void)
{
	struct sigaction sa;

	sa.sa_sigaction = &handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGTRAP, &sa, NULL);

	//signal(SIGTRAP, handler);

	log_info("Signal handler loaded ...");
}
