#include "fann.h"
#include "parallel_fann.h"
#include "util.h"

int main(int argc, char *argv[])
{
	const unsigned int num_neurons_hidden =
	    NUM_INPUTS * 2 / 3 + NUM_OUTPUTS;
	const unsigned int num_layers = 3;
	const float desired_error = 0.001f;
	const unsigned int max_epochs = 100000;

	struct fann *ann =
	    fann_create_standard(num_layers, NUM_INPUTS, num_neurons_hidden,
				 NUM_OUTPUTS);
	fann_set_training_algorithm(ann, FANN_TRAIN_QUICKPROP);

	datafile = fopen("data/splice.train", "r");
	struct fann_train_data *train_data =
	    fann_create_train_from_callback(1914, NUM_INPUTS, NUM_OUTPUTS,
					    data_callback);
	fclose(datafile);

	fann_train_on_data(ann, train_data, max_epochs, 500, desired_error);

	datafile = fopen("data/splice.cv", "r");
	struct fann_train_data *cv_data =
	    fann_create_train_from_callback(638, NUM_INPUTS, NUM_OUTPUTS,
					    data_callback);
	fclose(datafile);

	printf("Running through %d cross-validation values\n",
	       fann_length_train_data(cv_data));
	report_data_error(ann, cv_data);

	fann_save(ann, "splice.net");
	fann_destroy(ann);
	return 0;
}
