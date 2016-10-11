#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include <stdio.h>
#include <fann.h>

// This global is unfortunate and necessary since it can't be passed to the callback */
extern FILE *datafile;

extern void
data_callback(unsigned int num_total, unsigned int num_input,
	      unsigned int num_output, fann_type * inputs, fann_type * outputs);

extern void report_data_error(struct fann *ann, struct fann_train_data *data);

extern int max_probability_index(fann_type * data);

#endif
