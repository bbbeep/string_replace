
#include <stdio.h>



int replace(char *fname, char *target) 
{
	int count = 0;
	FILE* file = fopen(fname, "rw");

	char line[1024];

	while(fgets(line, sizeof(line), file)) {
		printf("%s", line);	

	}

	fclose(file);
	return count;
}

