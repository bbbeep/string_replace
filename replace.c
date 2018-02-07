/**
 * @file replace.c
 * @author David Gray
 * Student ID: 40055149
 * @date 6 Feb 2018
 *
 * This file contains main, and processes the command line arguments.
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "replace.h"
#include "traversal.h"
#include "text.h"
#include "report.h"

//Global counts for the number of files in the array, and the allocated_size:
int num_files = 0;
int allocated_size = 0;

//Initializing global array of file_count structs
struct file_count *fcount_array = NULL;


char *getopt(int argc, char **argv)
{
	if(argc > 1)
	{
		return argv[1];
	} else {
		fprintf(stderr, "No command line arguments provided. Terminating program.\n");
		exit(1);
		return "";
	}
}


// Put a entry into the array of file_count structs.
void add_fname_to_fcount_array(char *s, int c) {
	if(num_files == allocated_size) {
		struct file_count *tmp_fcount_array = realloc(fcount_array, 2*allocated_size*sizeof(struct file_count));
		
		if(tmp_fcount_array == NULL) {
            		fprintf(stderr, "Too many file counter structs, skipping %s", s);
            		return;
		}

		fcount_array = tmp_fcount_array;
		allocated_size *= 2;
	}

	fcount_array[num_files].fname = s;
	fcount_array[num_files].changes = c;
	num_files++;
} 

void free_fcount_array(){
    	if (fcount_array != NULL) {
		//possible bug! Was ix = 1, changed to ix = 0 to get rid of mem leak.
       		for (int ix = 0;  (ix < num_files);  ix += 1) {
            		free(fcount_array[ix].fname);
        	}
        free(fcount_array);
    	}

}

//Main
int main(int argc, char **argv)
{
	char *target = getopt(argc, argv);
	
	allocated_size = 32;
	
	fcount_array = (struct file_count*)malloc(allocated_size*sizeof(struct file_count));

	traverse(".", target);

	make_report(target, fcount_array);
	
	free_fcount_array();
	return 0;
}

