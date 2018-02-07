/**
 * @file traversal.c
 * @author David Gray
 * Student ID: 40055149
 * @date 6 Feb 2018
 *
 * This file contains function traverse() which recurses through child directories,
 * and calls the replace() function with the target string, when it finds a .txt file.
 */


#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "traversal.h"
#include "replace.h"
#include "text.h"
#include "report.h"

void traverse(char *current, char *target) 
{
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
				// Ignoring hidden directories.
				if(dp->d_name[0] != '.'){
					char recurse_into[strlen(current)+strlen(dp->d_name)+2];
					sprintf(recurse_into, "%s/%s", current, dp->d_name);
					// recursive call
					traverse(recurse_into, target);
				}

			} else if ((int)dp->d_type == DT_REG) {
				if(!(strcmp(&(dp->d_name[strlen(dp->d_name) - 4]), ".txt"))) {
					//Found a .txt file, add to fcount array.
					char *file_loc = malloc(strlen(current)+strlen(dp->d_name)+2);
					if(file_loc == NULL) {
						fprintf(stderr, "Malloc error\n");
					}
					sprintf(file_loc, "%s/%s", current, dp->d_name);
					
					//Call to replace() which returns count of replacements.
					int count = replace(file_loc, target);
					add_fname_to_fcount_array(file_loc, count);	
				}
			} else {
				printf("ignoring unrecognized filetype for file %s", dp->d_name);
			}
		}
	} while (dp != NULL);
	
	closedir(dirp);
	return;
}
