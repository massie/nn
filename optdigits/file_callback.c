#include "fann.h"
#include "string.h"

FILE *datafile = NULL;

void data_callback( unsigned int num_total, unsigned int num_input, unsigned int num_output, fann_type *inputs, fann_type *outputs) {
	char line[512];
	int i;
	char *strval;
	float fval;
	char *delim = ",";
	fgets(line, sizeof(line), datafile);
	for(i = 0; i < num_input; i++) {
		if (i == 0) {
	       strval = strtok(line, delim);
		} else {
		   strval = strtok(NULL, delim);
		}
		fval = strtof(strval, NULL);
		//fprintf(stderr, "%f|", fval);
		inputs[i] = (fann_type) fval;
	}
	strval = strtok(NULL, delim);
	fval = strtof(strval, NULL);
	//fprintf(stderr, "====%f\n\n", fval);
	outputs[0] = fval / 10;
}
