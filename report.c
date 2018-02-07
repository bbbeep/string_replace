/**
 * @file report.c
 * @author David Gray
 * Student ID: 40055149
 * @date 6 Feb 2018
 *
 * This file deals with creating the report. It has a comparison function
 * for the file_count structs, and a function make_report to print the report. 
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "replace.h"
#include "report.h"

int compare_count(const void *a, const void *b) {
	struct file_count *fcount_a = (struct file_count *)a;
	struct file_count *fcount_b = (struct file_count *)b;

	return((fcount_b->changes)-(fcount_a->changes));	
}


void make_report(char *target, struct file_count *farray) {

	printf("Target string:  %s\n\n", target);

	char cwd[1024];
	if(getcwd(cwd, sizeof(cwd)) != NULL)
		printf("Search begins in current folder: %s\n\n\n", cwd);
	
	printf("** Search Report **\n\n");

	printf("Updates		File Name\n");
 
	qsort(farray, num_files, sizeof(farray[0]), compare_count);	

	for (int ix = 0;  (ix < num_files);  ix += 1) {
		if(farray[ix].changes == 0) 
			break;
                printf("%d		%s\n", farray[ix].changes, farray[ix].fname + 2);
        }
}	
