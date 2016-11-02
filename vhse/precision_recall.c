#include "precision_recall.h"

void print_f1_score(struct fann *ann, struct fann_train_data *data)
{
	unsigned int i;
	unsigned int true_positives = 0;
	unsigned int true_negatives = 0;
	unsigned int false_positives = 0;
	unsigned int false_negatives = 0;
	float precision, recall;

	for (i = 0; i != fann_length_train_data(data); i++) {
		int cv_value = data->output[i][0];
		float cancer_probability = fann_run(ann, data->input[i])[0];
		/* If the chance of cancer is 0.5, we define the tumor as malignant */
		int calc_value = cancer_probability >= 0.5 ? 1 : 0;
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
}
