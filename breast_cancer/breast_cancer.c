#include <float.h>
#include "fann.h"
#include "parallel_fann.h"
#include "data_format.h"

int main(int argc, char *argv[])
{
	const unsigned int num_input = 9;
	const unsigned int num_output = 1;
	const unsigned int num_layers = 3;
	const unsigned int num_neurons_hidden = (num_input + num_output) / 2;
	const float desired_error = 0.00001f;
	const unsigned int max_epochs = 100000;
	const unsigned int num_threads = 8;
	unsigned int i;
	unsigned int true_positives, true_negatives, false_negatives,
	    false_positives;
	float precision, recall;
	float error = FLT_MAX;
	fann_type *calc_value;

	struct fann *ann =
	    fann_create_standard(num_layers, num_input, num_neurons_hidden,
				 num_output);
	//fann_set_learning_rate(ann, 0.3);
	fann_set_training_algorithm(ann, FANN_TRAIN_RPROP);
	//fann_set_training_algorithm(ann, FANN_TRAIN_BATCH);
	//fann_set_activation_steepness_hidden(ann, 0.25);
	//fann_set_activation_steepness_output(ann, 0.25);
	fann_print_connections(ann);
	fann_set_activation_function_hidden(ann, FANN_ELLIOT);
	fann_set_activation_function_output(ann, FANN_ELLIOT);

	datafile = fopen("data/breast-cancer.train", "r");
	struct fann_train_data *train_data =
	    fann_create_train_from_callback(419, num_input, num_output,
					    data_callback);
	fclose(datafile);

	//fann_print_parameters(ann);
	for (i = 1; error > desired_error && i <= max_epochs; i++) {
		error =
		    fann_train_epoch_irpropm_parallel(ann, train_data,
						      num_threads);
		if (i % 500 == 0) {
			printf("Epochs     %8d. Current error: %.10f\n", i,
			       error);
		}
	}

	datafile = fopen("data/breast-cancer.cv", "r");
	struct fann_train_data *cv_data =
	    fann_create_train_from_callback(140, num_input, num_output,
					    data_callback);
	fclose(datafile);

	printf("Running through %d cross-validation values\n",
	       fann_length_train_data(cv_data));
	true_positives = 0;
	true_negatives = 0;
	false_positives = 0;
	false_negatives = 0;
	for (i = 0; i != fann_length_train_data(cv_data); i++) {
		int cv_value = cv_data->output[i][0];
		float cancer_probability = fann_run(ann, cv_data->input[i])[0];
		int calc_value = cancer_probability < 0.5 ? 0 : 1;
		if (calc_value) {
			if (cv_value) {
				true_positives++;
			} else {
				false_positives++;
			}
		} else {
			if (cv_value) {
				false_negatives++;
			} else {
				true_negatives++;
			}
		}
	}
	printf
	    ("True positives: %d, true negatives: %d, false positives: %d, false negatives: %d\n",
	     true_positives, true_negatives, false_positives, false_negatives);
	precision = (float)true_positives / (true_positives + false_positives);
	recall = (float)true_positives / (true_positives + false_negatives);
	printf("Precision: %f, recall: %f, F1 score: %f\n", precision, recall,
	       (2 * precision * recall) / (precision + recall));

	fann_save(ann, "breast-cancer.net");
	fann_destroy(ann);
	return 0;
}
