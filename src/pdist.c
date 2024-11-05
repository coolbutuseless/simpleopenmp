
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#ifdef _OPENMP
#include <omp.h>
#endif

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP has_openmp_(void) {
#ifdef _OPENMP
  Rprintf("OpenMP enabled. Num threads = %i\n", omp_get_num_threads());
  return ScalarLogical(1);
#else
  return ScalarLogical(0);
#endif
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// A plain C version
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP pdist_c_(SEXP x_, SEXP y_) {
  
  double *x = REAL(x_);  
  double *y = REAL(y_);  
  
  int N = length(x_);
  if (length(y_) != N) {
    error("'x' and 'y' must be same length");
  }
  
  SEXP res_ = PROTECT(allocVector(REALSXP, N));
  double *res = REAL(res_);
  
  for (int i = 0; i < N; i++) {
    res[i] = sqrt(x[i] * x[i] + y[i] * y[i]);
  }
  
  UNPROTECT(1);
  return res_;
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// An openmp C version
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP pdist_openmp_(SEXP x_, SEXP y_, SEXP nthreads_) {
  
  double *x = REAL(x_);  
  double *y = REAL(y_);  
  
  int N = length(x_);
  if (length(y_) != N) {
    error("'x' and 'y' must be same length");
  }
  
  SEXP res_ = PROTECT(allocVector(REALSXP, N));
  double *res = REAL(res_);
  
#ifdef _OPENMP
  int nthreads = asInteger(nthreads_);
  if (nthreads < 1) nthreads = 1;
  omp_set_num_threads(nthreads);
#pragma omp parallel for
#endif
  for (int i = 0; i < N; i++) {
    res[i] = sqrt(x[i] * x[i] + y[i] * y[i]);
  }
  
  UNPROTECT(1);
  return res_;
}
