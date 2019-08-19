# Geometric Neural Network
**Geometry Neural Network** is a Neural Network which exploit linear algebra
objects to compute neural network operations. In general with a set of operations
between linear algebra objects any form of the NN can be done. For example
also a Neural Network where each layer is a cube can be done.
This operations are:
- Dot product
- Transpose
- Addition
- Subtraction
- Hadamard product (element to element)
- Multiplication with a scalar
- Apply a function to every element of linear algebra object
- Multiplication with a matrix


## Vector implementation
This is the easiest vector implementation where each layer is composed by vectors
self implemented. The aim of this Neural Network is to recognize hand number digits,
wich means convert a hand written number into a [0,9] val.

## Depenencies

The external libraries needed are:
- **Boost**, used to manage input program options
- **dot** [graphviz]


## Usage

```
$ mkdir build && cd build
```
Will create the build directory
```
$ cmake ..
```
Will create the makefiles and custom targets
```
$ make
```
Will compile the library
```
$ make test
```
Will launch tests for each module
```
$ make install
```
Will install in `${SOURCE_DIRECTORY}/bin` the binaries
```
$ ./vectorNeuralNetwork -h
```
to see usage
### Example
```
$ ./vectorNeuralNetwork -t ../data/mnist_train.csv
```

### Parameters istructions
- ` -s [--save] ` will save the configuration weigths at the end of the computation
- ` -t [--train] arg ` will train the network with \i arg file in csv format
- ` -p [--put-up] arg ` will submit a test set \i arg file in csv format
- ` -w [--weigths] arg ` will load the weights from a file in data format

Multiple options can be concatenated, for example it is possible to load a current weights configuration, then train
the network with a specific train_set file, submit a test_set file and at the end store the end configuration in an other
file:
```
./vectorNeuralNetwork -w ../data/weights1.data -t ../data/train_set.csv -p ../data/test_set.csv -s weights2.data
```

## Input files
For the *Vector Neural Network* used the input present *28x28* neuron input and *10* output.
Below there is an example where the number 8 in *gray-scale* is represented:
```
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 5 31 131 223 161 32 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 8 31 213 242 242 181 251 220 27 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 85 209 217 93 0 0 5 198 254 49 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 62 93 0 100 126 25 142 254 254 49 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 87 245 254 254 254 254 49 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 96 254 254 254 243 42 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 42 242 254 254 179 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 10 195 254 254 231 34 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 78 254 241 213 254 155 10 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 42 194 254 101 19 183 254 134 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 168 254 239 50 0 19 217 233 62 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 67 236 240 80 0 0 0 85 242 234 24 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 26 237 254 204 0 0 0 0 0 172 254 70 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 75 254 239 74 0 0 0 0 0 88 254 189 9 0 0 0 0 0 0 0 0
0 0 0 0 0 0 10 192 254 165 0 0 0 0 0 0 88 254 218 16 0 0 0 0 0 0 0 0
0 0 0 0 0 0 135 254 254 87 0 0 0 0 0 32 214 254 106 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 149 255 220 9 0 0 0 81 107 214 254 215 18 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 149 254 252 81 23 113 204 250 254 254 161 29 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 19 209 254 247 245 254 254 254 161 97 2 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 4 85 130 215 166 39 6 2 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
```
In detail the file format is composed with a number for each row where the first
value is the correct value and then *28x28* values are listed, one for each
neuron input of the *Vector Neural Network*.

To download the dataset you can visit [mnist csv](https://pjreddie.com/projects/mnist-in-csv)
or use `make get_csv` from build directory with cmake configuration.

Enjoy!
