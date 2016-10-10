# Neural Networks

This is a repo for experimenting with neural networks.

From the [UC Irvine Machine Learning Repository](http://archive.ics.uci.edu/ml/index.html):

* [Breast Cancer Wisconsin (Diagnostic)](breast_cancer/README.md)
* [Optical Recognition of Handwritten Digits](optdigits/README.md)

## Installing FANN

The [Fast Neural Artificial Network Library (FANN)](http://leenissen.dk/fann/wp/) "is a free open source neural network library, which implements multilayer artificial neural networks in C with support for both fully connected and sparsely connected networks."

While there is a Brew package for FANN, it is not multi-threaded so you should build the library yourself.

You'll need to make sure you have an up-to-date gcc compiler, with openmp support. This can easily be done using `brew`.

```
$ brew install gcc49 --without-multilib
```

Once you have gcc installed, you install FANN by running, e.g.

```
$ CC=gcc-4.9 CXX=g++-4.9 cmake .
$ make
$ make install
```

This tells cmake to use your specific gcc compiler. You should see output the includes the following:

```
-- Try OpenMP C flag = [-fopenmp]
-- Performing Test OpenMP_FLAG_DETECTED
-- Performing Test OpenMP_FLAG_DETECTED - Success
-- Try OpenMP CXX flag = [-fopenmp]
-- Performing Test OpenMP_FLAG_DETECTED
-- Performing Test OpenMP_FLAG_DETECTED - Success
```

