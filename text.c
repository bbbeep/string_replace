
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "text.h"

void s_to_lower(char *s)
{
	for(int i=0; i<strlen(s); i++){
		s[i]=tolower(s[i]);	
	}
}


void s_to_upper(char *s)
{
	for(int i=0; i<strlen(s); i++){
		s[i]=toupper(s[i]);	
	}
}

int replace(char *fname, char *target) 
{
	int count = 0;

	FILE* file = fopen(fname, "r+");
	FILE* tmp = fopen(fname, "r+");

	char line_buf[1024];
	char line_lower[1024];

	char target_lower[strlen(target)+1];
	strcpy(target_lower, target);
	s_to_lower(target_lower);
	
	char target_upper[strlen(target)+1];
	strcpy(target_upper, target);
	s_to_upper(target_upper);
	

	while(fgets(line_buf, sizeof(line_buf), file)) {
		char* next_targ;
		
		strcpy(line_lower, line_buf);
		s_to_lower(line_lower);

		next_targ= strstr(line_lower, target_lower);
		while((next_targ != NULL))
		{
			int pos = (int)(next_targ - line_lower);
			
			printf("Found %s at position %d, in the line \n%s", target, pos, line_buf);
			
			memcpy(&(line_buf[pos]), target_upper, strlen(target_upper));
			
			printf("Replaced %s at position %d, in the line \n%s\n", target, pos, line_buf);

			char *search_after = next_targ + strlen(target_lower);
			//shouldn't increment count if the word was already uppercase...
			count += 1;
			
			next_targ= strstr(search_after, target_lower);
		}	
		fputs(line_buf, tmp);
	}

	fclose(file);
	fclose(tmp);
	return count;
}

