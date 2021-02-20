#include <stdio.h>
#include <unistd.h>

int main()
{
	printf("pid: %d\nBefore int3...\n", getpid());
	asm("int3");
	printf("After int3...");

	return 0;
}
