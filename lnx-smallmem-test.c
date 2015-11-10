#include <stdio.h>
#include <stdlib.h>

#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#define SMALLMEM_BASE ((1 << 30) | (1 << 15))
#define SMALLMEM_SIZE 64

int main(void)
{
	int fd;
	volatile int *smallmem;
	int i;

	fd = open("/dev/mem", O_RDWR);
	if (fd < 0) {
		perror("open");
		return -1;
	}

	smallmem = (volatile int *) mmap(
			NULL, SMALLMEM_SIZE,
			PROT_READ | PROT_WRITE, MAP_SHARED,
			fd, SMALLMEM_BASE);
	if (smallmem == MAP_FAILED) {
		perror("mmap");
		return -1;
	}

	for (i = 0; i < SMALLMEM_SIZE / sizeof(int); i++) {
		smallmem[i] = i * 3;
		if (smallmem[i] != i * 3) {
			fprintf(stderr, "error at %d\n", i);
			return -1;
		}
	}

	munmap((void *) smallmem, SMALLMEM_SIZE);
	close(fd);

	return 0;
}
