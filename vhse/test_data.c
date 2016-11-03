#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "fann.h"

struct vhse_info {
	char *aa_short_name;
	double vhse_scores[8];
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

int str_to_vhse(char *str, int strlen, double *values, int vallen) {
	int i;
	int offset;
	for (i = 0; i < strlen; i++) {
		char p = str[i];
		if (p >= 97) {
			p -= 32;
		}
		offset = p - 65;
		struct vhse_info *info = vhse + offset;
		printf("%f,%f,%f\n", info->vhse_scores[0], info->vhse_scores[2], info->vhse_scores[4]);
	}
}

int main()
{
	fann_type *calc_out;
	struct fann_train_data *data;
	int i;
	struct fann *ann = fann_create_from_file("proteasomal_cleavage.net");

	double answer[4 * 3];
	str_to_vhse("ARND", 4, answer, sizeof(answer));

	/*
	data = fann_read_train_from_file("/workspace/notebooks/data/epitope_protein/s6_fann.txt");
	fann_scale_train_data(data, 0, 1);

	fann_reset_MSE(ann);
	for (i = 0; i < data->num_data; i++) {
		calc_out = fann_test(ann, data->input[i], data->output[i]);
		printf("Test actual=%f calculated=%f\n", data->output[i][0], calc_out[0]);
	}
	printf("MSE: %f\n", fann_get_MSE(ann));

	fann_destroy_train(data);
	*/
	fann_destroy(ann);
	return 0;
}