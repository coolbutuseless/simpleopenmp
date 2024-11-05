
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
  const struct timespec dur = {.tv_sec = 0, .tv_nsec = 1e8}; // 0.1 seconds
  int N = asInteger(N_);
  
  for (int i = 0; i < N; i++) {
    nanosleep(&dur, NULL);
  }
  
  return R_NilValue;
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// An openmp C version
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP sleep_openmp_(SEXP N_, SEXP nthreads_) {
  
  const struct timespec dur = {.tv_sec = 0, .tv_nsec = 1e8}; // 0.1 seconds
  int N = asInteger(N_);

#ifdef _OPENMP
  int nthreads = asInteger(nthreads_);
  if (nthreads < 1) nthreads = 1;
  omp_set_num_threads(nthreads);
#pragma omp parallel for
#endif
  for (int i = 0; i < N; i++) {
    nanosleep(&dur, NULL);
  }
  
  return R_NilValue;
}
