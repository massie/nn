# Breast Cancer Wisconsin (Diagnostic) Data Set 

The [dataset](http://archive.ics.uci.edu/ml/datasets/Breast+Cancer+Wisconsin+%28Diagnostic%29) was preprocessed as follows to create the training, cross-validation, and test data.

```
$ shuf breast-cancer-wisconsin.data.txt >breast-cancer-wisconsin.data.shuffled.txt
$ head -419 breast-cancer-wisconsin.data.shuffled.txt > breast-cancer.train
$ tail -280 breast-cancer-wisconsin.data.shuffled.txt | head -140 > breast-cancer.cv
$ tail -280 breast-cancer-wisconsin.data.shuffled.txt | tail -140 > breast-cancer.test
```

To build, run:

```
$ cmake .
$ make
$ ./train_cv_data
```
The `train_cv_data` app will train the NN using the training set, and then use the trained NN against the cross-validation data.

After running, look at `breast-cancer.net` to see the NN that was trained. This model can be loaded to make predictions for new data. For example,

```
$ ./test_data
False (+): model said   673637 had 82.28% chance of cancer.
False (-): model said  1192325 had 19.62% chance of cancer.
False (-): model said   877943 had 34.26% chance of cancer.
False (+): model said  1231706 had 54.15% chance of cancer.
False (+): model said  1096352 had 70.02% chance of cancer.
False (-): model said  1177399 had  4.38% chance of cancer.
False (-): model said  1202812 had  7.86% chance of cancer.
False (+): model said  1016277 had 95.02% chance of cancer.
```

The `test_data` command loads the model and make predictions on the `breast-cancer.test` data. 

Note: You'll need to modify the `CMakeLists.txt` file, if you install FANN somewhere other than `/usr/local`.
