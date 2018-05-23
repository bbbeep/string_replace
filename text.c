/**
 * @file text.c
 * @author David Gray
 * Student ID: 40055149
 * @date 6 Feb 2018
 *
 * This file has function replace() which takes a filename and a target string, and
 * finds the string anywhere it may occur in the file, and replaces it with all caps.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "text.h"

//Internal functions for changing a string to upper or lowercase
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

//Main function for finding and replacing the target in a file
int replace(char *fname, char *target) 
{
	int count = 0;

	FILE* file_in = fopen(fname, "r");
	FILE* file_out = fopen(fname, "r+");

	char line_buf[4096];
	
	// These are used to do a case-insenstive search	
	char line_lower[4096];
	char target_lower[strlen(target)+1];
	strcpy(target_lower, target);
	s_to_lower(target_lower);
	//Used for replacement in line_buf	
	char target_upper[strlen(target)+1];
	strcpy(target_upper, target);
	s_to_upper(target_upper);

	//Iterating through line by line
	while(fgets(line_buf, sizeof(line_buf), file_in)) {
		char* next_targ;
		
		strcpy(line_lower, line_buf);
		s_to_lower(line_lower);

		next_targ= strstr(line_lower, target_lower);
		while((next_targ != NULL))
		{
			int pos = (int)(next_targ - line_lower);
			
		
			if(strncmp(&(line_buf[pos]), target_upper, strlen(target_upper))){
				//a not fully capitalized target has been found
				
				//Replace the target at pos with uppercase.	
				memcpy(&(line_buf[pos]), target_upper, strlen(target_upper));
				count += 1;
			}

			char *search_after = next_targ + strlen(target_lower);
			next_targ= strstr(search_after, target_lower);
		}	
		//printf("%s",....) or sprintf() is also allowed!
		fputs(line_buf, file_out);
	}
	//remember to fclose()
	fclose(file_in);
	fclose(file_out);
	return count;
}

