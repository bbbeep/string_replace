//traversing directory

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include "traversal.h"
#include "replace.h"


void traverse(char *current) 
{
	//int alloc_size=sizeof(fnames)/sizeof(struct change_count);
	//printf("(from traversal.c) Number of structs allowed in fnames:  %d\n", alloc_size);


	DIR *dirp;
	struct dirent *dp;

	//Error checking and initializing dirp
	if(!(dirp = opendir(current))) {
		fprintf(stderr, "null directory error\n");
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
					// This line isn't problematic right? allocating more space than I may need for this string....	
					char recurse_into[strlen(current)+strlen(dp->d_name)+2];
					sprintf(recurse_into, "%s/%s", current, dp->d_name);
					printf("descending into... %s\n", recurse_into);
					traverse(recurse_into);
				}
			} else if ((int)dp->d_type == DT_REG) {
				//printf("reg file: %s/%s\n", current, dp->d_name);
				// found a textfile	
				
				if(strstr(dp->d_name, ".txt")!=NULL) {
					char file_loc[strlen(current)+strlen(dp->d_name)+2];
					sprintf(file_loc, "%s/%s", current, dp->d_name);
					printf("found %s\n", file_loc);	
					add_fname_to_fcount_array(file_loc, 0);	
				}
			} else {
				printf("ignoring unrecognized filetype for file %s", dp->d_name);
			}
		}
	} while (dp != NULL);
	
	closedir(dirp);
	return;
}
