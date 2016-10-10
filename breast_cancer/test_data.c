#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "floatfann.h"

#define NUM_INPUTS 9
#define BENIGN 2
#define MALIGNANT 4

int main()
{
	fann_type *calc_out;
	fann_type inputs[NUM_INPUTS];
	struct fann *ann = fann_create_from_file("breast-cancer.net");
	FILE *fp = fopen("data/breast-cancer.test", "r");
	char line[512];
	int i, predicted_val;
	char *strval, *id;
	long val;
	char *delim = ",";
	while (fgets(line, sizeof(line), fp) != NULL) {
		/* Skip the ID */
		id = strtok(line, delim);
		/* Fetch the inputs */
		for (i = 0; i < NUM_INPUTS; i++) {
			strval = strtok(NULL, delim);
			val = strtol(strval, NULL, 0);
			//fprintf(stderr, "%d|", val);
			inputs[i] = (fann_type) val;
		}
		/* Fetch the outputs */
		strval = strtok(NULL, delim);
		val = strtol(strval, NULL, 0);
		calc_out = fann_run(ann, inputs);
		predicted_val = *calc_out >= 0.5 ? MALIGNANT : BENIGN;
		if (predicted_val != val) {
			if (val == MALIGNANT) {
				printf("False (-): ");
			} else {
				printf("False (+): ");
			}
			printf
			    ("model said %8s had %5.02f%% chance of cancer.\n",
			     id, *calc_out * 100);
		}
	}

	fann_destroy(ann);
	return 0;
}
