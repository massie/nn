# Molecular Biology (Splice-junction Gene Sequences)

The [dataset](http://archive.ics.uci.edu/ml/datasets/Molecular+Biology+%28Splice-junction+Gene+Sequences%29) was preprocessed as follows to create the training, cross-validation, and test data.

```
$ shuf splice.data.txt > splice.data.shuf.txt
$ head -1914 splice.data.shuf.txt > splice.train
$ tail -1276 splice.data.shuf.txt | head -638 > splice.cv
$ tail -1276 splice.data.shuf.txt | tail -638 > splice.test
```

To build, run:

```
$ cmake .
$ make
$ ./train_cv_data
```
The `train_cv_data` app will train the NN using the training set, and then use the trained NN against the cross-validation data.

After running, look at `splicing.net` to see the NN that was trained. This model can be loaded to make predictions for new data. For example,

```
$ ./test_data
```

The `test_data` command loads the model and make predictions on the `splice.test` data.

Note: You'll need to modify the `CMakeLists.txt` file, if you install FANN somewhere other than `/usr/local`.
