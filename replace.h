#ifndef REPLACE_H_ 
#define REPLACE_H_

void add_fname_to_fcount_array(char *s, int c);

// A struct to hold a filename (with relative location)
// and a count of changes made by replace() in text.c to each file
struct file_count
{
        int changes;
        char *fname;
};

extern struct file_count *array;

extern int num_files; 
extern int allocated_size;


#endif /* RESULTS_H_ */
