/**
 * @file replace.h
 * @author David Gray
 * Student ID: 40055149
 * @date 6 Feb 2018
 *
 * Header file for replace.c
 * Declares the struct file_count used for saving filenames during traversal, 
 * and recording the number of changes made to each file.
 */ 


#ifndef REPLACE_H_ 
#define REPLACE_H_

// A struct to hold a filename (with relative location)
// and a count of changes made by replace() in text.c to each file
struct file_count
{
        int changes;
        char *fname;
};


extern struct file_count *fcount_array;

extern int num_files; 
extern int allocated_size;


#endif /* RESULTS_H_ */
