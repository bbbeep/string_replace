/**
 * @file replace.c
 * @author David Gray
 * Student ID: 40055149
 * @date 6 Feb 2018
 *
 * This file contains main, and processes the command line arguments.
 */ 
#define SIZE 32
allocated_size = 32

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

void free_fcount_array(){
    	if (fcount_array != NULL) {
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
	
	fcount_array = (struct file_count*)malloc(SIZE*sizeof(struct file_count));
	if(fcount_array == NULL) {
		fprintf(stderr, "Malloc error for fcount_array");
	}
		
	traverse(".", target);

	make_report(target, fcount_array);
	
	free_fcount_array();
	return 0;
}

