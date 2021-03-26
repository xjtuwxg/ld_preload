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

	/* Print arg as ucontext_t. */
	log_info("signal #%d. rip: 0x%llx (%d)", sig,
		 context->uc_mcontext.gregs[REG_RIP], ++sig_cnt);
	/* Print some data of siginfo_t, nothing much interesting. */
	log_info("si_addr: %p, si_fd: %d, si_pid %u", si->si_addr, si->si_fd,
		 si->si_pid);

	/* Modify RIP here (we advance the rip by 2 -- skip two int3 instrs) */
#if 1
	context->uc_mcontext.gregs[REG_RIP] = context->uc_mcontext.gregs[REG_RIP]
		+ 0x02;
#endif
	/* We don't want the program to exit, so comment this out. */
	//exit(1);
}

void _init(void)
{
	struct sigaction sa;
	struct sigaction old_sa;

	/* struct sigaction {
	 *  void     (*sa_handler)(int);
	 *  void     (*sa_sigaction)(int, siginfo_t *, void *);
	 *  sigset_t   sa_mask;
	 *  int        sa_flags;
	 *  void     (*sa_restorer)(void);
	 * };
	 * https://man7.org/linux/man-pages/man2/sigaction.2.html */
	sa.sa_sigaction = &handler;
	sa.sa_flags = SA_SIGINFO; /* Use sa_sigaction instead of sa_handler. */
	sigaction(SIGTRAP, &sa, &old_sa);

	/* The sa_restorer is obsolete and should not be used. */
	/* sa_handler specifies the action to be associated with signum and may
	 * be SIG_DFL for the default action, SIG_IGN to ignore this signal, or
	 * a pointer to a signal handling function. */

	/* Nothing much interesting in the old_sa. */
	log_info("signal #%d: The old sa_restorer addr: %p\n"
		"		old sa_handler addr: %p", SIGTRAP,
		old_sa.sa_restorer, old_sa.sa_handler);

	/* Both sigaction() and signal() can be used to change
	 * the disposition of a signal. sigaction() is more portable. */
	//signal(SIGTRAP, handler);

	log_info("Signal handler loaded ...");
}
