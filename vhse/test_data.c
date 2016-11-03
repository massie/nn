#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "fann.h"

struct vhse_info {
	char *aa_short_name;
	float vhse_scores[8];
};

struct vhse_info vhse[] = {
	{.aa_short_name = "Ala", .vhse_scores = {0.15,-1.11,-1.35,-0.92,0.02,-0.91,0.36,-0.48}},
	{.aa_short_name = NULL},
	{.aa_short_name = "Cys", .vhse_scores = {0.18,-1.67,-0.46,-0.21,0.0,1.2,-1.61,-0.19}},
	{.aa_short_name = "Asp", .vhse_scores = {-1.15,0.67,-0.41,-0.01,-2.68,1.31,0.03,0.56}},
	{.aa_short_name = "Glu", .vhse_scores = {-1.18,0.4,0.1,0.36,-2.16,-0.17,0.91,0.02}},
	{.aa_short_name = "Phe", .vhse_scores = {1.52,0.61,0.96,-0.16,0.25,0.28,-1.33,-0.2}},
	{.aa_short_name = "Gly", .vhse_scores = {-0.2,-1.53,-2.63,2.28,-0.53,-1.18,2.01,-1.34}},
	{.aa_short_name = "His", .vhse_scores = {-0.43,-0.25,0.37,0.19,0.51,1.28,0.93,0.65}},
	{.aa_short_name = "Ile", .vhse_scores = {1.27,-0.14,0.3,-1.8,0.3,-1.61,-0.16,-0.13}},
	{.aa_short_name = NULL},
	{.aa_short_name = "Lys", .vhse_scores = {-1.17,0.7,0.7,0.8,1.64,0.67,1.63,0.13}},
	{.aa_short_name = "Leu", .vhse_scores = {1.36,0.07,0.26,-0.8,0.22,-1.37,0.08,-0.62}},
	{.aa_short_name = "Met", .vhse_scores = {1.01,-0.53,0.43,0.0,0.23,0.1,-0.86,-0.68}},
	{.aa_short_name = "Asn", .vhse_scores = {-0.99,0.0,-0.37,0.69,-0.55,0.85,0.73,-0.8}},
	{.aa_short_name = NULL},
	{.aa_short_name = "Pro", .vhse_scores = {0.22,-0.17,-0.5,0.05,-0.01,-1.34,-0.19,3.56}},
	{.aa_short_name = "Gln", .vhse_scores = {-0.96,0.12,0.18,0.16,0.09,0.42,-0.2,-0.41}},
	{.aa_short_name = "Arg", .vhse_scores = {-1.47,1.45,1.24,1.27,1.55,1.47,1.3,0.83}},
	{.aa_short_name = "Ser", .vhse_scores = {-0.67,-0.86,-1.07,-0.41,-0.32,0.27,-0.64,0.11}},
	{.aa_short_name = "Thr", .vhse_scores = {-0.34,-0.51,-0.55,-1.06,0.01,-0.01,-0.79,0.39}},
	{.aa_short_name = NULL},
	{.aa_short_name = "Val", .vhse_scores = {0.76,-0.92,0.17,-1.91,0.22,-1.4,-0.24,-0.03}},
	{.aa_short_name = "Trp", .vhse_scores = {1.5,2.06,1.79,0.75,0.75,-0.13,-1.06,-0.85}},
	{.aa_short_name = NULL},
	{.aa_short_name = "Tyr", .vhse_scores = {0.61,1.6,1.17,0.73,0.53,0.25,-0.96,-0.52}},
	{.aa_short_name = NULL}
};

void str_to_vhse(char *str, int slen, float *values, int vallen) {
	int i, j;
	for (i = 0, j = 0; i < slen; i++) {
		char p = str[i];
		if (isspace(p)) {
			continue;
		}
		struct vhse_info *info;
		assert(p >= 'A' & p <= 'z');
		if (p >= 'A') {
			info = vhse + p - 'A';
		} else {
			info = vhse + p - 'a';
		}
		values[j++] = info->vhse_scores[0];
		values[j++] = info->vhse_scores[1];
		values[j++] = info->vhse_scores[2];
	}
}

int main()
{
	struct fann *ann = fann_create_from_file("proteasomal_cleavage.net");

	char *line = NULL;
	size_t size;
	int expected_line_length = 28;
	int values_len = expected_line_length * 3;
	float values[values_len]; 

	while(getline(&line, &size, stdin) != -1) {

		str_to_vhse(line, strlen(line), values, values_len);
#ifdef ECHO_INPUT
		printf(">");
		for (i = 0; i < values_len; i++) {
			if (i) {
				printf(",");
			}
			printf("%f", values[i]);
		}
		printf("\n");
#endif
		fann_scale_input(ann, values);
		fann_type *output = fann_run(ann, values);
		printf("%f\n", output[0]);
	}
	fann_destroy(ann);
	return 0;
}
