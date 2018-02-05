//traversing directory

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include "traversal.h"
#include "replace.h"

//function to return fname lead by its relative location.
char *proper_filename(char *current, char *fname) {
	//char *s = NULL;

	if(strcmp(current, ".")){	
		//current is not "."		
		char c[sizeof(current) + sizeof(fname) + 2];
		strcpy(c, current);

		strcat(c, "/");
		strcat(c, fname);
		return c;
	} else {
		char d[sizeof(fname) + 1];
		strcpy(d, fname);
		return d;
	}

	/*if(s == NULL){
		fprintf(stderr, "filenaming error");
	}
	
	printf("From current: %s and fname: %s, returning: %s\n", current, fname, s);
	return s;
	*/
}

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
					char recurse_into[sizeof(current)+sizeof(dp->d_name)+2];
					if(strcmp(current, ".")){	
						strcpy(recurse_into, current);
						strcat(recurse_into, "/");
						strcat(recurse_into, dp->d_name);
					} else {
						strcpy(recurse_into, dp->d_name);
					}
					printf("descending into... %s\n", recurse_into);
					traverse(recurse_into);
				}
			} else if ((int)dp->d_type == DT_REG) {
				//printf("reg file: %s/%s\n", current, dp->d_name);
				// found a textfile	
				
				if(strstr(dp->d_name, ".txt")!=NULL) {
					if(strcmp(current, ".")){	
						printf("found %s/%s\n", current, dp->d_name);	
						//add_fname_to_fcount_array(current/dp->d_name);	
					} else {
						printf("found %s\n", dp->d_name);	
						add_fname_to_fcount_array(dp->d_name, 0);
					}	
				}
			} else {
				printf("ignoring unrecognized filetype for file %s", dp->d_name);
			}
		}
	} while (dp != NULL);
	
	closedir(dirp);
	return;
}
