
#include <stdio.h>
#include <string.h>


int replace(char *fname, char *target) 
{
	int count = 0;

	FILE* file = fopen(fname, "r");
	//FILE* tmp = fopen("tmp.tmp", "w");

	char line_buf[1024];


	while(fgets(line_buf, sizeof(line_buf), file)) {
		printf("%s", line_buf);	
		char* found;
		if((found = strstr(line_buf, target)))
		{
			int pos = (int)(found - line_buf);
			printf("Found %s at position %d, in the line \n%s\n", target, pos, line_buf);
			count += 1;
		}
			

	}

	fclose(file);
	//fclose(tmp);
	return count;
}

