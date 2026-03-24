#include <stdio.h>

#define cpu_queue_initalize(cpuid) \
	int cpu_(cpuid) = cpuid;

int main() {
    cpu_queue_initalize(0);
    printf("%d\n", cpu_0);
    return 0;
}