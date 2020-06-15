# Genome sequence pattern matching

Our project is a solution for scientists in genetics to perform string pattern matching while searching for genes in genomes in the fastest possible way. We have implemented the OpenCL Kernel using modified Parallel Failureless Aho-Corasick algorithm.


Benchmarks were taken from Python sequential Aho-Corasick algorithm that you can find [here] (https://github.com/abusix/ahocorapy).

### Usage

The OpenCL Kernel implementation can be found in package /opencl.

You need to have an OpenCL installed, to make it: search for an SDK on your GPU's Company official web site.
To check whether OpenCL is correctly installed on your system run:
```
clinfo
```
To build the OpenCL program: clone the repository and run:
```
cd opencl
mkdir build
cd build
cmake ..
make
```
markers.csv -- a file of test patterns can be found [here] ()
pseudoxxx.fasta -- a file of test genomes can be found [here] ()

## Authors

[Hryts](https://github.com/Hryts), [ch0c01ate](https://github.com/ch0c01ate), [yankur](https://github.com/yankur)

## Presentations

- [**Presentation I**](https://docs.google.com/presentation/d/1yow5fSretDchJyX4T9DEEepWt9ZJUv94rC0p-LcquX0/edit#slide=id.g732a92fea1_0_5)
- [**Presentation II**](https://docs.google.com/presentation/d/1yow5fSretDchJyX4T9DEEepWt9ZJUv94rC0p-LcquX0/edit#slide=id.g732a92fea1_3_4)
- [**Presentation III**](https://docs.google.com/presentation/d/1-T6YDYSQbuGx_kSZbkI5jjgQxk5Gub2-RKH1w_ordxo/edit?usp=sharing)

