#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "replace.h"
#include "traversal.h"


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
		fprintf(stderr, "No command line arguments provided\n");
		return "";
	}
}

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


//Main
int main(int argc, char **argv)
{
	allocated_size = 32;
	fcount_array = (struct file_count*)malloc(allocated_size*sizeof(struct file_count));
	int alloc_size=sizeof(fcount_array)/sizeof(struct file_count);
	printf("Number of structs allowed in array: %d\n", alloc_size);

	char *foo = getopt(argc, argv);
	printf("Target String: %s\n", foo);

	traverse(".");


	printf("first element of fcount_array: %s\n", fcount_array[0].fname);

	return 0;
}

