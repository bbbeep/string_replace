#include <stdio.h>
#include <stdlib.h>
#include "replace.h"
#include <string.h>
//should contain main()

int main(int argc, char **argv)
{
	printf("argv: %s\n\n",argv[0]);	
	char *foo = getopt(argc, argv);

	printf("\n %d \n",foo);	
	
	return 0;
}


char *getopt(int argc, char **argv)
{
	printf("argc: %d", argc);	
	if(argc > 1)
	{
		return 0;	
		//return argv[1];
	} else {
		return 1;	
		fprintf(0, "No command line arguments provided");
		// return "";
	}
}
