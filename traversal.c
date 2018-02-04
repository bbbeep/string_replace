//traversing directory

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include "traversal.h"

void traverse(char *current) 
{
	DIR *dirp;
	struct dirent *dp;

	//Error checking and initializing dirp
	if(!(dirp = opendir(current))) {
		fprintf(stderr, "null directory error");
		return; 
	}

	// Iterating through the current directory, one file at a time
	do {
		if ((dp = readdir(dirp)) != NULL) {
			if((int)dp->d_type == DT_DIR) {
				//printf("directory: %s/%s\n", current, dp->d_name);
				//dp is a directory

				//We're going to ignore any directory that starts with a . (like .git, .., ., etc...
				if(dp->d_name[0] != '.'){
					// make a string of the right size
					char recurse_into[sizeof(current)+sizeof(dp->d_name)+2];
				
					strcpy(recurse_into, current);
					strcat(recurse_into, "/");
					strcat(recurse_into, dp->d_name);
			
					printf("descending into... %s\n", recurse_into);
					traverse(recurse_into);
				}
			} else if ((int)dp->d_type == DT_REG) {
				//printf("reg file: %s/%s\n", current, dp->d_name);
				// found a textfile	
				if(strstr(dp->d_name, ".txt")!=NULL)
					printf("found %s/%s\n", current, dp->d_name);	
				
			} else {
				printf("ignoring unrecognized filetype for file %s", dp->d_name);
			}
		}
	} while (dp != NULL);
	
	closedir(dirp);
	return;
}
