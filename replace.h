#ifndef REPLACE_H_ 
#define REPLACE_H_

char *getopt(int argc, char **argv);

// A struct to hold a filename (with relative location)
// and a count of changes made by replace() in text.c to each file
struct file_count
{
        int changes;
        char *fname;
};

extern struct file_count *array;

extern int num_of_files; 
extern int allocated_size;


#endif /* RESULTS_H_ */
