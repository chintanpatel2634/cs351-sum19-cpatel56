/* mycat: implementation of UNIX cat utility */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

	if (argc < 2) {
		printf("Usage: %s FILE1 FILE2 ...\n", argv [0]);
		exit(1);
}

  FILE *infile = fopen(argv[1], "r");
  if (infile == NULL) {
	perror("Opening file failed");
	exit(2);
 }
 // char c;
 // while (fread(&c, 1, 1, infile) > 0) {
//	printf("%c", c);
//}
 // fread(&c, 1, 1, infile);
 // printf("Read: %c\n",c);

  char buf[80];
  fgets(buf, sizeof(buf), infile);
  printf("%s", buf);

  fclose(infile);
  return 0;
}
