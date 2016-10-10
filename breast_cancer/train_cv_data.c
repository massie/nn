#include "fann.h"
#include "parallel_fann.h"
#include "data_format.h"
#include "precision_recall.h"

int main(int argc, char *argv[])
{
	const unsigned int num_input = 9;
	const unsigned int num_output = 1;
	const unsigned int num_layers = 3;
	const unsigned int num_neurons_hidden = (num_input + num_output) / 2;
	const float desired_error = 0.01f;
	const unsigned int max_epochs = 10000;

	struct fann *ann =
	    fann_create_standard(num_layers, num_input, num_neurons_hidden,
				 num_output);
	fann_print_connections(ann);
	fann_set_training_algorithm(ann, FANN_TRAIN_QUICKPROP);
	//fann_set_activation_function_hidden(ann, FANN_ELLIOT);
	//fann_set_activation_function_output(ann, FANN_ELLIOT);

	datafile = fopen("data/breast-cancer.train", "r");
	struct fann_train_data *train_data =
	    fann_create_train_from_callback(419, num_input, num_output,
					    data_callback);
	fclose(datafile);

	fann_train_on_data(ann, train_data, max_epochs, 500, desired_error);

	/* For larger data sets, here's how we could parallelize training...
	   fann_print_parameters(ann);
	   for (i = 1; error > desired_error && i <= max_epochs; i++) {
	   error =
	   fann_train_epoch_quickprop_parallel(ann, train_data,
	   num_threads);
	   if (i % 500 == 0) {
	   printf("Epochs     %8d. Current error: %.10f\n", i,
	   error);
	   }
	   } */

	datafile = fopen("data/breast-cancer.cv", "r");
	struct fann_train_data *cv_data =
	    fann_create_train_from_callback(140, num_input, num_output,
					    data_callback);
	fclose(datafile);

	printf("Running through %d cross-validation values\n",
	       fann_length_train_data(cv_data));
	print_f1_score(ann, cv_data);

	fann_save(ann, "breast-cancer.net");
	fann_destroy(ann);
	return 0;
}
