#include "util.h"
#include <string.h>
#include <assert.h>
#include <math.h>
#include <ctype.h>

// This global is unfortunate and necessary since it can't be passed to the callback */
FILE *datafile = NULL;

const char *slice_class_strings[3] = { "N", "IE", "EI" };
const char *stop_codon_strings[3] = { "TAA", "TAG", "TGA" };

#define num_strings(x) (sizeof(x)/sizeof(x[0]))

static const char *nucleotides = "ACTGDNSR";

int intron_exon_feature_boundary(char *dna)
{
	int i;
	const char *target_strings[2] = { "CAGG", "TAGG" };
	for (i = 0; i < num_strings(target_strings); i++) {
		if (strstr(dna, target_strings[i]) != NULL) {
			return 1;
		}
	}
	return 0;
}

int exon_intron_feature_boundary(char *dna)
{
	int i;
	const char *target_strings[4] =
	    { "AAGGTAAGT", "AAGGTGAGT", "CAGGTAAGT", "CAGGTGAGT" };
	for (i = 0; i < num_strings(target_strings); i++) {
		if (strstr(dna, target_strings[i]) != NULL) {
			return 1;
		}
	}
	return 0;
}

int has_stop_codon(char *dna)
{
	int i;
	for (i = 0; i < num_strings(stop_codon_strings); i++) {
		if (strstr(dna, stop_codon_strings[i]) != NULL) {
			return 1;
		}
	}
	return 0;
}

void
data_callback(unsigned int num_total, unsigned int num_input,
	      unsigned int num_output, fann_type * inputs, fann_type * outputs)
{
	char line[512];
	int i, j;
	char *strval;
	char *delim = ",";

	fgets(line, sizeof(line), datafile);
	strval = strtok(line, delim);
	for (i = 0; i < 3; i++) {
		outputs[i] =
		    !memcmp(slice_class_strings[i], strval, strlen(strval));
	}
	/* Skip the sequence identifier */
	strval = strtok(NULL, delim);
	/* Fetch the DNA sequence */
	strval = strtok(NULL, delim);
	/* Skip the leading whitespace */
	while (isspace((unsigned char)*strval))
		strval++;

	i = 0;
	inputs[i++] = exon_intron_feature_boundary(strval);
	inputs[i++] = intron_exon_feature_boundary(strval);
	inputs[i++] = has_stop_codon(strval);

	for (j = 0; j < 60; j++) {
		char *p = strchr(nucleotides, strval[j]);
		assert(p != NULL);
		inputs[i++] = (fann_type) (p - nucleotides);
	}

	/*
	   printf(".... ");
	   for (i = 0; i < num_input; i++) {
	   printf("%3.0f ", inputs[i]);
	   }
	   printf(" ...\n"); */
}

int max_probability_index(fann_type * data)
{
	unsigned int i;
	float max_prob = 0;
	int offset = 0;
	for (i = 0; i < 3; i++) {
		if (data[i] > max_prob) {
			max_prob = data[i];
			offset = i;
		}
	}
	return offset;
}

void report_data_error(struct fann *ann, struct fann_train_data *data)
{
	unsigned int i, misses, total_records;
	fann_type *calc_output;

	total_records = fann_length_train_data(data);
	for (i = 0, misses = 0; i != total_records; i++) {
		int cv_value = max_probability_index(data->output[i]);
		calc_output = fann_run(ann, data->input[i]);
		int cal_value = max_probability_index(calc_output);
		if (cal_value != cv_value) {
			misses++;
		}
	}

	printf("%5.2f accuracy\n",
	       (float)(total_records - misses) / total_records * 100);
}
