#include "float.h"
#include "fann.h"
#include "parallel_fann.h"
#include "string.h"

// This global is unfortunate and necessary since it can't be passed to the callback */
static FILE *datafile = NULL;

static int probability_output_to_int(fann_type * output, int num_output)
{
	float probability = 0.0;
	int val = 0;
	unsigned int i;
	for (i = 0; i < num_output; i++) {
		//printf("%d=%f ", i, output[i]);
		if (output[i] > probability) {
			val = i;
			probability = output[i];
		}
	}
	//printf("\n");
	return val;
}

static void
data_callback(unsigned int num_total, unsigned int num_input,
	      unsigned int num_output, fann_type * inputs, fann_type * outputs)
{
	char line[512];
	int i;
	char *strval;
	long val;
	char *delim = ",";
	fgets(line, sizeof(line), datafile);
	for (i = 0; i < num_input; i++) {
		if (i == 0) {
			strval = strtok(line, delim);
		} else {
			strval = strtok(NULL, delim);
		}
		val = strtol(strval, NULL, 0);
		// fprintf(stderr, "%d|", val);
		inputs[i] = (fann_type) val;
	}
	strval = strtok(NULL, delim);
	val = strtol(strval, NULL, 0);
	memset(outputs, 0, sizeof(*outputs));
	outputs[val] = 1.0f;
}

int main(int argc, char *argv[])
{
	const unsigned int num_input = 64;
	const unsigned int num_output = 10;
	const unsigned int num_layers = 3;
	const unsigned int num_neurons_hidden = 37;
	const float desired_error = 0.00001f;
	//const unsigned int max_epochs = 5000000;
	const unsigned int num_threads = 8;
	unsigned int i;
	unsigned int missed_tests;
	float error = FLT_MAX;
	fann_type *calc_out;

	struct fann *ann =
	    fann_create_standard(num_layers, num_input, num_neurons_hidden,
				 num_output);
	//fann_set_learning_rate(ann, 0.3);
	fann_set_training_algorithm(ann, FANN_TRAIN_RPROP);
	//fann_set_training_algorithm(ann, FANN_TRAIN_INCREMENTAL);
	fann_set_activation_steepness_hidden(ann, 0.05);
	fann_set_activation_steepness_output(ann, 0.05);
	fann_print_connections(ann);
	fann_set_activation_function_hidden(ann, FANN_ELLIOT);
	fann_set_activation_function_output(ann, FANN_ELLIOT);

	datafile = fopen("optdigits.train", "r");
	struct fann_train_data *train_data =
	    fann_create_train_from_callback(3823, num_input, num_output,
					    data_callback);
	fclose(datafile);

	//fann_print_parameters(ann);
	// i <= max_epochs
	for (i = 1; error > desired_error; i++) {
		error =
		    fann_train_epoch_irpropm_parallel(ann, train_data,
						      num_threads);
		if (i % 500 == 0) {
			printf("Epochs     %8d. Current error: %.10f\n", i,
			       error);
		}
	}

	datafile = fopen("optdigits.test", "r");
	struct fann_train_data *test_data =
	    fann_create_train_from_callback(1797, num_input, num_output,
					    data_callback);
	fclose(datafile);

	printf("Running through %d test values\n",
	       fann_length_train_data(test_data));
	missed_tests = 0;
	for (i = 0; i != fann_length_train_data(test_data); i++) {
		calc_out = fann_run(ann, test_data->input[i]);
		int calc_value =
		    probability_output_to_int(calc_out, num_output);
		int test_value =
		    probability_output_to_int(test_data->output[i], num_output);
		if (calc_value != test_value) {
			missed_tests++;
			printf("NN calculated %d, should be %d\n", calc_value,
			       test_value);
		}
	}
	printf("NN miscalculated %d of %d values in test set (%f %% error)\n",
	       missed_tests, fann_length_train_data(test_data),
	       (float)missed_tests / fann_length_train_data(test_data) * 100);

	fann_save(ann, "optdigits.net");
	fann_destroy(ann);
	return 0;
}
