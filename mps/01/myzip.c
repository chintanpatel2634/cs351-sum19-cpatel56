/* myzip: implementation of a run-length encoding compression utility */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) { 
	if (argc < 2) {
    printf("Usage: %s FILENAME\n", argv[0]);
    exit(1);
  }
	FILE *ftozip;	
	ftozip = fopen(argv[1],"r");//open the file that we are zipping
	if (ftozip == NULL) {//if there is an error opening
		perror("File cannot be opened ");
	}
	char zipfilename[30];
	strcat(zipfilename, argv[1]);
	strcat(zipfilename,".zip");
	FILE *zipfilep = fopen(zipfilename, "a"); //zipfile openned to write
        
	int count = 1;
	while(1){ //incrementing the characters and storing in the zip  file
		if(*ftozip == *(ftozip +1)) {
			count++;
			char countchar[] = (char)count+(*ftozip);
			fputs(countchar, zipfilep);  
			ftozip++;
			continue;
		}
		else {
			count = 1;
			countchar = (char)count + (*ftozip);
			ftozip++;
			if (feop(ftozip){
				break;
			}
			continue;
		}
									
}
				

		
}
	fclose(zipfilename);
	fclose(ftozip);

/*	int i;
	char c;
	i = 5;
	c = 'a';
	fwrite(&i, 4, 1, stdout);
	fwrite(&c, 1, 1, stdout);

	i = 3;
	c = 'b';
	fwrite(&i, 4, 1, stdout);
	fwrite(&c, 1, 1, stdout);
 */  
  return 0;
}

