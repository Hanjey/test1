#!/bin/bash
gcc dgemm_test.c -o dgemm -I /opt/intel/mkl/include  -lmkl_rt -L/opt/intel/mkl/lib/intel64 -L/opt/intel/lib/intel64
