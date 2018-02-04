#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "replace.h"
#include "traversal.h"


//should contain main()

int main(int argc, char **argv)
{
	char *foo = getopt(argc, argv);

	printf("Target String: %s\n", foo);

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
