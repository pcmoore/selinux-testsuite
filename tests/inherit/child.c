#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	char buf[255];
	ssize_t bytes;
	int fd, ret;
	struct stat sb;

	if (argc != 2) {
		fprintf(stderr, "usage:  %s fd\n", argv[0]);
		exit(-1);
	}

	fd = atoi(argv[1]);

	ret = fstat(fd, &sb);
	if (ret < 0) {
		perror("fstat");
		exit(2);
	}
	if (sb.st_rdev == 0x103 /* /dev/null */) {
		fprintf(stderr, "%s:  null device\n", argv[0]);
		exit(1);
	}

	strcpy(buf, "hello world!\n");
	bytes = write(fd, buf, strlen(buf));
	if (bytes < 0) {
		perror("write");
		exit(1);
	}
	exit(0);
}
