clear; close all; clc
addpath("~/octave/nnet-0.1.9");

# Load the full data set
data = csvread("../data/breast-cancer-wisconsin.data.txt");

# If the value in column 11 is 4, mark it malignant
data(:,11) = data(:, 11) == 4;

# Last column is the output data (0 == benign, 1 == malignant)
output = data(:, end);
output = output';

# Input doesn't include the first column which is a 
input = data(:, 2:end-1);
input = input';

[num_rows, num_columns] = size(data);

# Split data into train, cross-validate, and test sets
num_train_sets = floor(num_rows * .6);
num_cv_sets = (num_rows - num_train_sets) / 2;
num_test_sets = num_rows - num_train_sets - num_cv_sets;
cv_input = input(:, 1:num_cv_sets);
cv_output = output(:, 1:num_cv_sets);
input(:, 1:num_cv_sets) = [];
output(:, 1:num_cv_sets) = [];
test_input = input(:, 1:num_test_sets);
test_output = output(:, 1:num_test_sets);
input(:, 1:num_test_sets) = [];
output(:, 1:num_test_sets) = [];
train_input = input(:, 1:num_train_sets);
train_output = output(:, 1:num_train_sets);

# Standardize the inputs
[train_input_n, mean_input, std_input] = prestd(train_input);

# Define the max and min inputs for each row
min_max_elements = min_max(train_input_n);

# Define the network
num_hidden_neurons = 5;
num_output_neurons = 1;

nn = newff(min_max_elements, [num_hidden_neurons num_output_neurons], \
        {"tansig", "purelin"}, "trainlm", "", "mse");
nn.trainParam.epochs = 1000;
nn.trainParam.goal = 0.00001;
nn.IW{1,1}(:) = 1.5;
nn.LW{2,1}(:) = 0.5;
nn.b{1,1}(:) = 1.5;
nn.b{2,1}(:) = 0.5;

saveMLPStruct(nn, "breast-cancer-octave.txt");

VV.P = cv_input;
VV.T = cv_output;
VV.P = trastd(VV.P, mean_input, std_input);

[net] = train(nn, train_input_n, train_output);

[test_input_n] = trastd(test_input, mean_input, std_input);

[sim_out] = sim(net, test_input_n);

malignant = sim_out > 0.5;

malignant == test_output
