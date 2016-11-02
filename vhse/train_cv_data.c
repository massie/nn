#include <string.h>
#include <ncurses.h>
#include "fann.h"
#include "parallel_fann.h"
#include "precision_recall.h"

int main(int argc, char *argv[])
{
	const unsigned int num_input = 42;
	const unsigned int num_output = 1;
	const unsigned int num_layers = 3;
	const unsigned int num_neurons_hidden = num_input * 2 / 3 + num_output;
	const float desired_error = 0.01f;
	const unsigned int max_epochs = 10000;
	int num_threads = 8;

	struct fann *ann =
	    fann_create_standard(num_layers, num_input, num_neurons_hidden,
				 num_output);
	//fann_print_connections(ann);
	//fann_print_parameters(ann);
	fann_set_training_algorithm(ann, FANN_TRAIN_RPROP);
	fann_set_activation_function_hidden(ann, FANN_SIGMOID_STEPWISE);
	fann_set_activation_function_output(ann, FANN_SIGMOID_STEPWISE);

	struct fann_train_data *train_data =
	    fann_read_train_from_file
	    ("/workspace/notebooks/data/epitope_protein/fann_training.txt");

	fann_set_scaling_params(ann, train_data, 0, 1, 0, 1);
	fann_scale_train(ann, train_data);

	initscr();
	cbreak();

	int i;
	float error = 100.0;
	for (i = 1; error > desired_error && i <= max_epochs; i++) {
		error =
		    fann_train_epoch_quickprop_parallel(ann, train_data,
							num_threads);
		if (i % 10 == 0) {
			mvprintw(0, 0,
				 "Epochs     %8d (max: %8d). Current error: %.10f (desired: %.10f)\n",
				 i, max_epochs, error, desired_error);
			refresh();
		}
	}

	endwin();

	fann_save(ann, "proteasomal_cleavage.net");
	fann_destroy(ann);
	return 0;
}
