#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "replace.h"
#include "traversal.h"

#define INIT_FILE_ARRAY_SIZE 100


//Global counts for the number of files in the array, and the allocated_size:
int num_of_files = 0;
int allocated_size = INIT_FILE_ARRAY_SIZE;

int main(int argc, char **argv)
{
	//Global array of change_count structs:
	struct file_count *array = malloc(100*sizeof(struct file_count));

	char *foo = getopt(argc, argv);

	printf("Target String: %s\n", foo);


	int alloc_size=sizeof(*array)/sizeof(struct file_count);
	printf("Number of structs allowed in array: %d\n", alloc_size);
	
	traverse(".");
	return 0;
}


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
