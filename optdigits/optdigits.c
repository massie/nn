#include "float.h"
#include "fann.h"
#include "parallel_fann.h"
#include "string.h"
#include "file_callback.h"

int main()
{
	const unsigned int num_input = 64;
	const unsigned int num_output = 10;
	const unsigned int num_layers = 3;
	const unsigned int num_neurons_hidden = 25;
	const float desired_error = (const float) 0.0001;
	const unsigned int max_epochs = 50000;
	const unsigned int epochs_between_reports = 100;
	const unsigned int num_threads = 8;
	unsigned int i;
	float error = FLT_MAX;

	struct fann *ann = fann_create_standard(num_layers, num_input, num_neurons_hidden, num_output);
	fann_print_connections( ann );
	fann_set_activation_function_hidden(ann, FANN_ELLIOT);
	fann_set_activation_function_output(ann, FANN_ELLIOT);

	datafile = fopen("optdigits.train", "r");
	struct fann_train_data *train_data = fann_create_train_from_callback(3823, num_input, num_output, data_callback);
	fclose(datafile);

	fann_print_parameters(ann);
	for(i = 1; i <= max_epochs && error > desired_error; i++)
	{
		error = fann_train_epoch_irpropm_parallel(ann, train_data, num_threads);
		printf("Epochs     %8d. Current error: %.10f\n", i, error);
	}

    datafile = fopen("optdigits.test", "r");
	struct fann_train_data *test_data = fann_create_train_from_callback(1797, num_input, num_output, data_callback);
	fclose(datafile);
	fann_reset_MSE(ann);
	for(i = 0; i < fann_length_train_data(test_data); i++) {
		fann_test(ann, test_data->input[i], test_data->output[i]);
	}
	printf("MSE error on test data: %f\n", fann_get_MSE(ann));

	fann_save(ann, "optdigits.net");
	fann_destroy(ann);
	return 0;
}
