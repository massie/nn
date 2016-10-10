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
$ ./breast_cancer
```
This program will train the NN using the training set, and then use the trained NN against the cross-validation data.

After running, look at `breast-cancer.net` to see the NN that was trained.

Note: You'll need to modify the `CMakeLists.txt` file, if you install FANN somewhere other than `/usr/local`.



[Dataset used](https://archive.ics.uci.edu/ml/datasets/Optical+Recognition+of+Handwritten+Digits)
