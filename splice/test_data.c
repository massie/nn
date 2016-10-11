#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "fann.h"
#include "util.h"

#define NUM_INPUTS 60
#define NUM_OUTPUTS 3
#define NUM_RECORDS 638

int main()
{
	unsigned int i, predicted_val, test_val, misses;
	fann_type *calc_out;
	fann_type inputs[NUM_INPUTS];
	fann_type outputs[NUM_OUTPUTS];

	struct fann *ann = fann_create_from_file("splice.net");
	datafile = fopen("data/splice.test", "r");
	for (i = 0, misses = 0; i < NUM_RECORDS; i++) {
		data_callback(NUM_RECORDS, NUM_INPUTS, NUM_OUTPUTS, inputs,
			      outputs);
		test_val = max_probability_index(outputs);
		calc_out = fann_run(ann, inputs);
		predicted_val = max_probability_index(calc_out);
		if (predicted_val != test_val) {
			misses++;
		}
	}
	printf("%5.2f accuracy\n",
	       (float)(NUM_RECORDS - misses) / NUM_RECORDS * 100);
	fann_destroy(ann);
	return 0;
}
