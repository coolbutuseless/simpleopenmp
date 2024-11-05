
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

#ifdef _OPENMP
#include <omp.h>
#endif

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// A plain C version
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP sleep_c_(SEXP N_) {
  
  
  int N = asInteger(N_);
  for (int i = 0; i < N; i++) {
    sleep(1);
  }
  
  return R_NilValue;
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// An openmp C version
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP sleep_openmp_(SEXP N_, SEXP nthreads_) {
  
  int N = asInteger(N_);

#ifdef _OPENMP
  int nthreads = asInteger(nthreads_);
  if (nthreads < 1) nthreads = 1;
  omp_set_num_threads(nthreads);
#pragma omp parallel for
#endif
  for (int i = 0; i < N; i++) {
    sleep(1);
  }
  
  return R_NilValue;
}
