#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdint.h>
#include <stdio.h>

int main(void)
{
	volatile uint64_t *scrs;
	int fd;

	fd = open("/dev/scr", O_RDONLY);
	scrs = (volatile uint64_t *) mmap(NULL, 4096, PROT_READ, MAP_PRIVATE, fd, 0);
	if (scrs == MAP_FAILED) {
		fprintf(stderr, "could not mmap SCR\n");
		return -1;
	}

	printf("ncores: %lu\n", scrs[0]);
	printf("mem size: %lu MB\n", scrs[1]);

	return 0;
}
