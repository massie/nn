#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "fann.h"
#include "util.h"

int main()
{
	unsigned int i, predicted_val, test_val, misses;
	fann_type *calc_out;
	fann_type inputs[NUM_INPUTS];
	fann_type outputs[NUM_OUTPUTS];

	struct fann *ann = fann_create_from_file("splice.net");
	datafile = fopen("data/splice.test", "r");
	for (i = 0, misses = 0; i < NUM_TEST_RECORDS; i++) {
		data_callback(NUM_TEST_RECORDS, NUM_INPUTS, NUM_OUTPUTS, inputs,
			      outputs);
		test_val = max_probability_index(outputs);
		calc_out = fann_run(ann, inputs);
		predicted_val = max_probability_index(calc_out);
		if (predicted_val != test_val) {
			misses++;
		}
	}
	printf("%5.2f accuracy\n",
	       (float)(NUM_TEST_RECORDS - misses) / NUM_TEST_RECORDS * 100);
	fann_destroy(ann);
	return 0;
}
