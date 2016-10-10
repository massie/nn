#include "data_format.h"
#include <string.h>
#include <assert.h>

// This global is unfortunate and necessary since it can't be passed to the callback */
FILE *datafile = NULL;

/**
   1. Sample code number            id number
   2. Clump Thickness               1 - 10
   3. Uniformity of Cell Size       1 - 10
   4. Uniformity of Cell Shape      1 - 10
   5. Marginal Adhesion             1 - 10
   6. Single Epithelial Cell Size   1 - 10
   7. Bare Nuclei                   1 - 10
   8. Bland Chromatin               1 - 10
   9. Normal Nucleoli               1 - 10
  10. Mitoses                       1 - 10
  11. Class:                        (2 for benign, 4 for malignant)
**/

void
data_callback(unsigned int num_total, unsigned int num_input,
	      unsigned int num_output, fann_type * inputs, fann_type * outputs)
{
	char line[512];
	int i;
	char *strval;
	long val;
	char *delim = ",";
	fgets(line, sizeof(line), datafile);
	/* Skip the ID */
	strval = strtok(line, delim);
	for (i = 0; i < num_input; i++) {
		strval = strtok(NULL, delim);
		val = strtol(strval, NULL, 0);
		//fprintf(stderr, "%d|", val);
		inputs[i] = (fann_type) val;
	}
	strval = strtok(NULL, delim);
	val = strtol(strval, NULL, 0);
	assert(val == 2 || val == 4);
	// O = benign, 1 = malignant
	outputs[0] = val == 2 ? 0 : 1;
}
