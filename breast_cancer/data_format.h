#ifndef DATA_FORMAT_H_INCLUDED
#define DATA_FORMAT_H_INCLUDED

#include <stdio.h>
#include <fann.h>

// This global is unfortunate and necessary since it can't be passed to the callback */
extern FILE *datafile;

extern void
data_callback(unsigned int num_total, unsigned int num_input,
	      unsigned int num_output, fann_type * inputs, fann_type * outputs);

#endif
